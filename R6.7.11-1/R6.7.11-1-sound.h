//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 高宮祐翔
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "R6.7.11-1-main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************

//BGM,SEを追加したい場合はここの列挙を増やす

typedef enum
{
	SOUND_LABEL_TITLE_BGM = 0,
	SOUND_LABEL_GAME_BGM,
	SOUND_LABEL_SE,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
