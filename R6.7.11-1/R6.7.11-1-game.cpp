#include "R6.7.11-1-game.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
#include "R6.7.11-1-input.h" //����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-background.h"
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-player2.h"
#include "R6.7.11-1-enemy1.h"
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-sound.h"
#include "R6.7.11-1-score.h"
#include "R6.7.11-1-effect.h"

//�O���[�o���ϐ��錾
GAMESTATE g_GameState = GAMESTATE_NONE; //�Q�[���̏��
int g_nCounterGameState = 0; //��ԊǗ��J�E���^�[
Enemy* pEnemy1; //�G�̏��ւ̃|�C���^

//�Q�[����ʂ̏���������=======================================================
void InitGame(void)
{
	//�e�I�u�W�F�N�g�̏���������-----------------------------------------------
	InitPlayer1(); //�v���C���[1�̏����������̊֐����Ăяo��
	InitPlayer2(); //�v���C���[2�̏����������̊֐����Ăяo��
	InitBackground(); //�w�i�̏����������̊֐����Ăяo��
	InitBullet(); //�V���b�g�e�̏����������̊֐����Ăяo��
	InitExplosion(); //�V���b�g�e�����̏���������
	InitEnemy1(); //�G1�̏����������̊֐����Ăяo��
	InitEffect(); //�G�t�F�N�g�̏����������̊֐����Ăяo��
	SetEnemy1(pEnemy1->pos, g_aEnemy1[nCountEnemy1].nType); //�G1�̐ݒ菈���̊֐����Ăяo�� �ʒu, ���
	SetEnemy1(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0); //�G1�̐ݒ菈���̊֐����Ăяo�� �ʒu, ���
	SetEnemy1(D3DXVECTOR3(100.0f, 100.0f, 100.0f), 1); //�G1�̐ݒ菈���̊֐����Ăяo�� �ʒu, ���
	InitScore(); //�X�R�A�̏����������̊֐����Ăяo��

	GAMESTATE g_GameState = GAMESTATE_NOMAL; //�Q�[���̏�Ԃ�ʏ��Ԃɐݒ�
	int g_nCounterGameState = 0;

	//�T�E���h���Đ�����
	PlaySound(SOUND_LABEL_GAME_BGM); //SOUND_LABEL_BGM�Ɏw�肵�������t�@�C�����Đ�����
	PlaySound(SOUND_LABEL_SE); //SOUND_LABEL_SE�Ɏw�肵�������t�@�C�����Đ�����
}

//�Q�[����ʂ̍X�V����=========================================================
void UpdateGame(void)
{
	int nEnemyTotal = EnemyTotal(); //���݂̓G�̑����������o�����߂̕ϐ�

	//�e�I�u�W�F�N�g�̍X�V����-------------------------------------------------
	UpdatePlayer1(); //�v���C���[1�̍X�V�����̊֐����Ăяo��
	UpdatePlayer2(); //�v���C���[2�̍X�V�����̊֐����Ăяo��
	UpdateBackground(); //�w�i�̍X�V�����̊֐����Ăяo��
	UpdateBullet(); //�V���b�g�e�̍X�V�����̊֐����Ăяo��
	UpdateExplosion(); //�V���b�g�e�����̍X�V�����̊֐����Ăяo��
	UpdateEnemy1(); //�G1�̍X�V�����̊֐����Ăяo��
	UpdateScore(); //�X�R�A�̍X�V�����̊֐����Ăяo��
	UpdateEffect(); //�G�t�F�N�g�̍X�V�����̊֐����Ăяo��

	switch (g_GameState)
	{
	case GAMESTATE_NOMAL: //�ʏ���
		break;

	case GAMESTATE_END: //�I�����
		g_nCounterGameState++; //��ԊǗ��J�E���^�[�̒l��(��F���Ƃ�)�C���N�������g(�J�E���g�A�b�v)����

		if (g_nCounterGameState >= 60) //
		{
			g_GameState = GAMESTATE_NONE; //�������Ă��Ȃ���Ԃɐݒ�

			//���(���[�h)�̐ݒ�
			SetMode(MODE_RESULT); //
		}

		break;
	}

	//��ʑJ�ڂ̏�����ݒ肷��
	if (GetKeyboardTrigger(DIK_RETURN) == true) //����(ENTER�L�[)�������ꂽ�ꍇ
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs����)
		SetMode(MODE_GAME);
	}

	if (nEnemyTotal <= 0) //�G�̑�����0�ȉ��ɂȂ����ꍇ
	{
		//���[�h�ݒ�(���U���g��ʂɈڍs����) �������ɒu���̂͐������Ȃ�!!
		SetMode(MODE_RESULT);
	}

}

//�Q�[����ʂ̕`�揈��=========================================================
void DrawGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��-----------------------------------------------
	// (��ԉ��̍s�ɂ�����̂���ԑO�ɕ`�悳���)
	DrawBackground(); //�w�i�̍X�V�����̊֐����Ăяo��
	DrawPlayer2(); //�v���C���[2�̕`�揈���̊֐����Ăяo��
	DrawBullet(); //�V���b�g�e�̕`�揈���̊֐����Ăяo��
	DrawEnemy1(); //�G1�̕`�揈���̊֐����Ăяo��
	DrawEffect(); //�G�t�F�N�g�̕`�揈���̊֐����Ăяo��
	DrawExplosion(); //�V���b�g�e�����̕`�揈���̊֐����Ăяo��
	DrawPlayer1(); //�v���C���[1�̕`�揈���̊֐����Ăяo��
	DrawScore(); //�X�R�A�̕`�揈���̊֐����Ăяo��
}

//�Q�[����ʂ̏I������=========================================================
void UninitGame(void)
{
	//�T�E���h���~����
	StopSound();

	//�e�I�u�W�F�N�g�̏I������-----------------------------------------------
	UninitPlayer1(); //�v���C���[1�̏I�������̊֐����Ăяo��
	UninitPlayer2(); //�v���C���[2�̏I�������̊֐����Ăяo��
	UninitEnemy1(); //�G1�̏I�������̊֐����Ăяo��
	UninitBackground(); //�w�i�̏I�������̊֐����Ăяo��
	UninitBullet(); //�V���b�g�e�����̏I�������̊֐����Ăяo��
	UninitExplosion(); //�V���b�g�e�����̏I�������̊֐����Ăяo��
	UninitScore(); //�X�R�A�̏I�������̊֐����Ăяo��
	UninitEffect(); //�G�t�F�N�g�̏I�������̊֐����Ăяo��
}

//�Q�[����Ԃ̐ݒ菈��=========================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state; //

	g_nCounterGameState = 0;
}

//�Q�[����Ԃ̎擾����=========================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}