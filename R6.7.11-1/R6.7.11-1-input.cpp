#include "R6.7.11-1-input.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
							 // ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������

//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̎�ނ̍ő吔

//�O���[�o���ϐ��錾
LPDIRECTINPUT8 g_pInput = NULL; //DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̃v���X���(�o�C�g�^)
BYTE g_aOldKeyState[NUM_KEY_MAX]; //1�O�̃L�[�{�[�h�̃v���X���(�o�C�g�^)
XINPUT_STATE g_joykeyState; //�W���C�p�b�h�̃v���X���

//�L�[�{�[�h�̏���������=======================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���

	//�L�[�{�[�h��  �Ɏ��s�����ꍇ�̏���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
											 IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̍쐬

	//�L�[�{�[�h��  �Ɏ��s�����ꍇ�̏���
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l������
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//�W���C�p�b�h�̏���������=======================================================
HRESULT InitJoypad(void)
{
	//�������̃N���A���s��
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));

	//XInput�̃X�e�[�g��ݒ�(�L����)����
	XInputEnable(true);

	return S_OK;
}
//�L�[�{�[�h�̍X�V����=========================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̓��͏��
	int nCountKey;

	//1�O�̃L�[���͏���ۑ�����
	for (nCountKey = 0; nCountKey < NUM_KEY_MAX; nCountKey++)
	{
		g_aOldKeyState[nCountKey] = g_aKeyState[nCountKey];
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCountKey = 0; nCountKey < NUM_KEY_MAX; nCountKey++)
		{
			g_aKeyState[nCountKey] = aKeyState[nCountKey]; //�L�[�{�[�h�̃v���X����ۑ�����
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//�W���C�p�b�h�̍X�V����=========================================================
void UpdateJoypad(void)
{
	//�W���C�p�b�h�̓��͏��
	XINPUT_STATE joykeyState;

	//�W���C�p�b�h�̏�Ԃ��擾����
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joykeyState = joykeyState; //�W���C�p�b�h�̃v���X����ۑ�
	}
}

//�L�[�{�[�h���͂̃v���X�����擾���鏈��=====================================
bool GetKeyboardPress(int nKey)
{
	//�u������ ? A: B;�v�̌`��3�����Z�q
	//  ���̏ꍇ�A���������^(true)�ł����A��Ԃ��A�U(false)�ł����B��Ԃ��B
	return(g_aKeyState[nKey] & 0x80) ? true: false;

}

//�L�[�{�[�h���͂̃v���X���(�����ꂽ�u��)���擾���鏈��=======================
bool GetKeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//�L�[�{�[�h���͂̃v���X���(������)���擾���鏈��=============================
bool GetKeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;

}

//�L�[�{�[�h���͂̃v���X���(���ꂽ�u��)���擾���鏈��=========================
bool GetKeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;

}

//�W���C�p�b�h���͂̃v���X�����擾���鏈��===================================
bool GetJoypadPress(JOYKEY nKey)
{
	return (g_joykeyState.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

/*//�W���C�p�b�h���͂̃v���X���(�����ꂽ�u��)���擾���鏈��=====================
bool GetJoypadTrigger(JOYKEY nKey)
{
	
}

//�W���C�p�b�h���͂̃v���X���(������)���擾���鏈��===========================
bool GetJoypadRepeat(JOYKEY nKey)
{

}

//�W���C�p�b�h���͂̃v���X���(���ꂽ�u��)���擾���鏈��=======================
bool GetJoypadRelease(JOYKEY nKey)
{

}*/

//�L�[�{�[�h�̏I������=========================================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�����������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//�W���C�p�b�h�̏I������=========================================================
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g��ݒ�(������)����
	XInputEnable(false);
}