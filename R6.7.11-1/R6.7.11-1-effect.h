#ifndef _EFFECT_H_ //���̃}�N����`������Ă��Ȃ������ꍇ��1�s�ڂɕK���������Ɓ�

#define _EFFECT_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"

//�}�N����`
//#define BULLET_WIDTH (150) //�V���b�g�e�̕�
//#define BULLET_HEIGHT (200) //�V���b�g�e�̍���
#define MAX_LIFE (150) //�G�t�F�N�g�����ł���܂ł̎���

//�V���b�g�e�\���̂̒�`
//typedef struct
//{
//	D3DXVECTOR3 pos; //�ʒu
//	D3DXVECTOR3 move; //�ړ���
//	int nLife; //�e�����ł���܂ł̎���
//	BULLETTYPE type; //�e�̎��(�e�����@�̃V���b�g,�G�̍U���̂ǂ���Ȃ̂��𔻕ʏo����悤�ɂ���)
//	bool bUse; //�g�p���Ă��邩�ǂ���
//} Bullet;

//�e�̎��
//typedef enum
//{
//	BULLETTYPE_PLAYER1 = 0, //�v���C���[1�̒e
//	BULLETTYPE_ENEMY, //�G�̒e
//	BULLETTYPE_MAX
//} BULLETTYPE;

//�v���g�^�C�v�錾
void InitEffect(void); //�G�t�F�N�g�̏���������
void UninitEffect(void); //�G�t�F�N�g�̏I������
void UpdateEffect(void); //�G�t�F�N�g�̍X�V����
void DrawEffect(void); //�G�t�F�N�g�̕`�揈��
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife); //�G�t�F�N�g�̐ݒ菈��
//pos�c�ʒu col�c���_�J���[ fRadius�c�G�t�F�N�g�̔��a(�傫��) nLife�c�G�t�F�N�g�����ł���܂ł̎���

#endif //���ŉ��s�ɕK���������Ɓ�