#ifndef _RESULT_H_ //���̃}�N����`������Ă��Ȃ������ꍇ ��1�s�ڂɕK���������Ɓ�

#define _RESULT_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"

//�}�N����`
#define RESULT_WIDTH (1280) //���U���g�̕�
#define RESULT_HEIGHT (720) //���U���g�̍���

//�v���g�^�C�v�錾
void InitResult(void); //���U���g��ʂ̏���������
void UninitResult(void); //���U���g��ʂ̏I������
void UpdateResult(void); //���U���g��ʂ̍X�V����
void DrawResult(void); //���U���g��ʂ̕`�揈��

#endif //���ŉ��s�ɕK���������Ɓ�