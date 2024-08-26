#ifndef _TITLE_H_ //このマクロ定義がされていなかった場合 ※1行目に必ず書くこと※

#define _TITLE_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"
#include "R6.7.11-1-sound.h"

//マクロ定義
#define TITLE_WIDTH (1280) //タイトルの幅
#define TITLE_HEIGHT (720) //タイトルの高さ

//プロトタイプ宣言
void InitTitle(void); //タイトル画面の初期化処理
void UninitTitle(void); //タイトル画面の終了処理
void UpdateTitle(void); //タイトル画面の更新処理
void DrawTitle(void); //タイトル画面の描画処理

#endif //※最下行に必ず書くこと※