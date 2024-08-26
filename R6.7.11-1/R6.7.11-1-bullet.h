#ifndef _BULLET_H_ //���̃}�N����`������Ă��Ȃ������ꍇ��1�s�ڂɕK���������Ɓ�

#define _BULLET_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"

//�}�N����`
#define BULLET_WIDTH (150) //�V���b�g�e�̕�
#define BULLET_HEIGHT (200) //�V���b�g�e�̍���
#define MAX_LIFE (150) //�V���b�g�e�����ł���܂ł̎���

//�V���b�g�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 move; //�ړ���
	int nLife; //�e�����ł���܂ł̎���
	BULLETTYPE type; //�e�̎��(�e�����@�̃V���b�g,�G�̍U���̂ǂ���Ȃ̂��𔻕ʏo����悤�ɂ���)
	bool bUse; //�g�p���Ă��邩�ǂ���
} Bullet;

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER1 = 0, //�v���C���[1�̒e
	BULLETTYPE_ENEMY, //�G�̒e
	BULLETTYPE_MAX
} BULLETTYPE;

//�v���g�^�C�v�錾
void InitBullet(void); //�V���b�g�e�̏���������
void UninitBullet(void); //�V���b�g�e�̏I������
void UpdateBullet(void); //�V���b�g�e�̍X�V����
void DrawBullet(void); //�V���b�g�e�̕`�揈��
Bullet* GetBullet(void); //�e���擾���鏈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type); //�V���b�g�e�̐ݒ菈��
//pos�c���ˈʒu move�c�ړ��� nLife�c�e�����ł���܂ł̎��� type�c�e�̎��

#endif //���ŉ��s�ɕK���������Ɓ�