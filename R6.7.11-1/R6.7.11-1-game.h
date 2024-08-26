#ifndef _GAME_H_ //���̃}�N����`������Ă��Ȃ������ꍇ ��1�s�ڂɕK���������Ɓ�

#define _GAME_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0, //�������Ă��Ȃ����
	GAMESTATE_NOMAL, //�ʏ���(�Q�[���i�s��)
	GAMESTATE_END, //�I�����
	GAMESTATE_MAX
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void); //�Q�[����ʂ̏���������
void UninitGame(void); //�Q�[����ʂ̏I������
void UpdateGame(void); //�Q�[����ʂ̍X�V����
void DrawGame(void); //�Q�[����ʂ̕`�揈��
void SetGameState(GAMESTATE state); //�Q�[����Ԃ̐ݒ菈��
GAMESTATE GetGameState(void); //�Q�[����Ԃ̎擾����

#endif //���ŉ��s�ɕK���������Ɓ�