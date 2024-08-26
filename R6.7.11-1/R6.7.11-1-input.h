#ifndef _INPUT_H_ //���̃}�N����`������Ă��Ȃ������ꍇ ��1�s�ڂɕK���������Ɓ�

#define _INPUT_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include "R6.7.11-1-main.h"

//�L�[�̎��(16�S�ē���邱��!!)
typedef enum
{
	JOYKEY_UP = 0, //�\���L�[(��)
	JOYKEY_DOWN, //�\���L�[(��)
	JOYKEY_LEFT, //�\���L�[(��)
	JOYKEY_RIGHT, //�\���L�[(�E)
	JOYKEY_START, //START�{�^��
	JOYKEY_SELECT, //SELECT�{�^��
	JOYKEY_L3, //L3�{�^��(L�X�e�B�b�N��������)
	JOYKEY_R3, //R3�{�^��(R�X�e�B�b�N��������)
	JOYKEY_L1, //L1�{�^��
	JOYKEY_R1, //R1�{�^��
	JOYKEY_L2, //L2�{�^��(���݂͏o���Ȃ�)
	JOYKEY_R2, //R2�{�^��(���݂͏o���Ȃ�)
	JOYKEY_A, //A�{�^��
	JOYKEY_B, //B�{�^��
	JOYKEY_X, //X�{�^��
	JOYKEY_Y, //Y�{�^��
	JOYKEY_MAX
}JOYKEY;

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd); //�L�[�{�[�h���͂̏���������
void UninitKeyboard(void); //�L�[�{�[�h���͂̏I������
void UpdateKeyboard(void); //�L�[�{�[�h���͂̍X�V����
HRESULT InitJoypad(void); //�W���C�p�b�h���͂̏���������
void UninitJoypad(void); //�W���C�p�b�h���͂̏I������
void UpdateJoypad(void); //�W���C�p�b�h���͂̍X�V����
bool GetKeyboardPress(int nKey); //�L�[�{�[�h���͂̃v���X�����擾���鏈��
bool GetKeyboardTrigger(int nKey); //�L�[�{�[�h���͂̃v���X���(�����ꂽ�u��)���擾���鏈��
bool GetKeyboardRepeat(int nKey); //�L�[�{�[�h���͂̃v���X���(������)���擾���鏈��
bool GetKeyboardRelease(int nKey); //�L�[�{�[�h���͂̃v���X���(���ꂽ�u��)���擾���鏈��
bool GetJoypadPress(JOYKEY nKey); //�W���C�p�b�h���͂̃v���X�����擾���鏈��
/*bool GetJoypadTrigger(JOYKEY nKey); //�W���C�p�b�h���͂̃v���X���(�����ꂽ�u��)���擾���鏈��
bool GetJoypadRepeat(JOYKEY nKey); //�W���C�p�b�h���͂̃v���X���(������)���擾���鏈��
bool GetJoypadRelease(JOYKEY nKey); //�W���C�p�b�h���͂̃v���X���(���ꂽ�u��)���擾���鏈��*/

#endif //���ŉ��s�ɕK���������Ɓ�