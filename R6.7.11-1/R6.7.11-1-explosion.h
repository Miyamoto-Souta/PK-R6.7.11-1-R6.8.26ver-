#ifndef _EXPLOSION_H_ //���̃}�N����`������Ă��Ȃ������ꍇ��1�s�ڂɕK���������Ɓ�

#define _EXPLOSION_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"

//�}�N����`
#define BULLET_WIDTH (150) //�V���b�g�e�����̕�
#define BULLET_HEIGHT (200) //�V���b�g�e�����̍���

//�v���g�^�C�v�錾
void InitExplosion(void); //�V���b�g�e�����̏���������
void UninitExplosion(void); //�V���b�g�e�����̏I������
void UpdateExplosion(void); //�V���b�g�e�����̍X�V����
void DrawExplosion(void); //�V���b�g�e�����̕`�揈��
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col); //�V���b�g�e�����̐ݒ菈�� pos�c�����ʒu col�c�F���w�肷��
													 //�����͂��̏ꂩ�瓮���Ȃ����߁Amove(�ړ���)�ł͂Ȃ������col��p����

#endif //���ŉ��s�ɕK���������Ɓ�