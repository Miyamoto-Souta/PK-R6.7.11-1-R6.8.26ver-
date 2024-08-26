#ifndef _FADE_H_ //このマクロ定義がされていなかった場合 ※1行目に必ず書くこと※

#define _FADE_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"

//マクロ定義
#define FADE_WIDTH (1280) //タイトルの幅
#define FADE_HEIGHT (720) //タイトルの高さ

//ゲームの状態
typedef enum
{
	FADE_NONE = 0, //何もしていない状態(真っ黒)
	FADE_IN, //フェードイン状態(透明度を徐々に上げていく)
	FADE_OUT, //フェードアウト状態(透明度を徐々に下げていく)
	FADE_MAX
}FADE;

//プロトタイプ宣言
void InitFade(MODE ModeNext); //フェード画面の初期化処理
void UninitFade(void); //フェード画面の終了処理
void UpdateFade(void); //フェード画面の更新処理
void DrawFade(void); //フェード画面の描画処理
void SetGameState(MODE ModeNext); //フェード状態の設定処理
FADE GetFade(void); //フェード状態の取得処理

#endif //※最下行に必ず書くこと※