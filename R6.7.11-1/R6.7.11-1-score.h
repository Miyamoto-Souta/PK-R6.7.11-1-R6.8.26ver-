#ifndef _SCORE_H_ //���̃}�N����`������Ă��Ȃ������ꍇ ��1�s�ڂɕK���������Ɓ�

#define _SCORE_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"

//�}�N����`
#define SCORE_WIDTH (35) //�X�R�A1�����̃|���S���̕�
#define SCORE_HEIGHT (70) //�X�R�A1�����̃|���S���̍���

//�v���g�^�C�v�錾
void InitScore(void); //�X�R�A�̏���������
void UninitScore(void); //�X�R�A�̏I������
void UpdateScore(void); //�X�R�A�̍X�V����
void DrawScore(void); //�X�R�A�̕`�揈��
void SetScore(int nScore); //�X�R�A�̐ݒ菈��
void AddScore(int nValue); //�X�R�A�̉��Z����

#endif //���ŉ��s�ɕK���������Ɓ�