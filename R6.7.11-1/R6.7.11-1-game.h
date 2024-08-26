#ifndef _GAME_H_ //このマクロ定義がされていなかった場合 ※1行目に必ず書くこと※

#define _GAME_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE = 0, //何もしていない状態
	GAMESTATE_NOMAL, //通常状態(ゲーム進行中)
	GAMESTATE_END, //終了状態
	GAMESTATE_MAX
}GAMESTATE;

//プロトタイプ宣言
void InitGame(void); //ゲーム画面の初期化処理
void UninitGame(void); //ゲーム画面の終了処理
void UpdateGame(void); //ゲーム画面の更新処理
void DrawGame(void); //ゲーム画面の描画処理
void SetGameState(GAMESTATE state); //ゲーム状態の設定処理
GAMESTATE GetGameState(void); //ゲーム状態の取得処理

#endif //※最下行に必ず書くこと※