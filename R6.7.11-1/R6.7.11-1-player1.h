#ifndef _PLAYER1_H_ //���̃}�N����`������Ă��Ȃ������ꍇ��1�s�ڂɕK���������Ɓ�

#define _PLAYER1_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include <math.h>

//�}�N����`
#define PLAYER1_WIDTH (150) //�v���C���[1�̕�
#define PLAYER1_HEIGHT (200) //�v���C���[1�̍���

//�v���C���[1�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 movebullet; //�V���b�g�̈ړ���
	D3DXVECTOR3 rot; //����
	PLAYER1STATE state; //�v���C���[1�̏��
	int nCounterState; //��ԊǗ��J�E���^�[
	int nLife; //�v���C���[1�̗̑�
	bool bDisp; //�v���C���[1��\�����邩�\�����Ȃ���
	float Length; //�Ίp���̒���(�g��k���p)
	float Angle; //�Ίp���̊p�x(��]�p)
	int movedirection; //�ړ�����
} Player1;

//�v���C���[1�̏��
typedef enum
{
	PLAYER1STATE_APPEAR = 0, //�o�����(�_��)
	PLAYER1STATE_NORMAL, //�ʏ���
	PLAYER1STATE_DAMAGE, //�_���[�W���
	PLAYER1STATE_DEATH, //���S���
	PLAYER1STATE_INVINCIBLE, //���G���
	PLAYER1STATE_MAX
}PLAYER1STATE;

//�v���g�^�C�v�錾
void InitPlayer1(void); //�v���C���[1�̏���������
void UninitPlayer1(void); //�v���C���[1�̏I������
void UpdatePlayer1(void); //�v���C���[1�̍X�V����
void DrawPlayer1(void); //�v���C���[1�̕`�揈��
Player1* GetPlayer1(void); //�v���C���[1���擾���鏈��
void HitPlayer1(int nDamage); //�v���C���[1�̔�e����

//�O���[�o���ϐ��錾

#endif //���ŉ��s�ɕK���������Ɓ�