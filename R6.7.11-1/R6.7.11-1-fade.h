#ifndef _FADE_H_ //���̃}�N����`������Ă��Ȃ������ꍇ ��1�s�ڂɕK���������Ɓ�

#define _FADE_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"

//�}�N����`
#define FADE_WIDTH (1280) //�^�C�g���̕�
#define FADE_HEIGHT (720) //�^�C�g���̍���

//�Q�[���̏��
typedef enum
{
	FADE_NONE = 0, //�������Ă��Ȃ����(�^����)
	FADE_IN, //�t�F�[�h�C�����(�����x�����X�ɏグ�Ă���)
	FADE_OUT, //�t�F�[�h�A�E�g���(�����x�����X�ɉ����Ă���)
	FADE_MAX
}FADE;

//�v���g�^�C�v�錾
void InitFade(MODE ModeNext); //�t�F�[�h��ʂ̏���������
void UninitFade(void); //�t�F�[�h��ʂ̏I������
void UpdateFade(void); //�t�F�[�h��ʂ̍X�V����
void DrawFade(void); //�t�F�[�h��ʂ̕`�揈��
void SetGameState(MODE ModeNext); //�t�F�[�h��Ԃ̐ݒ菈��
FADE GetFade(void); //�t�F�[�h��Ԃ̎擾����

#endif //���ŉ��s�ɕK���������Ɓ�