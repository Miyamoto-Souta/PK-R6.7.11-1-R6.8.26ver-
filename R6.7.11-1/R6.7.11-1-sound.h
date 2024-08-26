//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���{�S��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "R6.7.11-1-main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************

//BGM,SE��ǉ��������ꍇ�͂����̗񋓂𑝂₷

typedef enum
{
	SOUND_LABEL_TITLE_BGM = 0,
	SOUND_LABEL_GAME_BGM,
	SOUND_LABEL_SE,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
