#ifndef _TITLE_H_ //���̃}�N����`������Ă��Ȃ������ꍇ ��1�s�ڂɕK���������Ɓ�

#define _TITLE_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"
#include "R6.7.11-1-sound.h"

//�}�N����`
#define TITLE_WIDTH (1280) //�^�C�g���̕�
#define TITLE_HEIGHT (720) //�^�C�g���̍���

//�v���g�^�C�v�錾
void InitTitle(void); //�^�C�g����ʂ̏���������
void UninitTitle(void); //�^�C�g����ʂ̏I������
void UpdateTitle(void); //�^�C�g����ʂ̍X�V����
void DrawTitle(void); //�^�C�g����ʂ̕`�揈��

#endif //���ŉ��s�ɕK���������Ɓ�