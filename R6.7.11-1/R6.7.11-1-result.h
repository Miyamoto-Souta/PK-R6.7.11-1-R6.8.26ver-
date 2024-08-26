#ifndef _RESULT_H_ //このマクロ定義がされていなかった場合 ※1行目に必ず書くこと※

#define _RESULT_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"

//マクロ定義
#define RESULT_WIDTH (1280) //リザルトの幅
#define RESULT_HEIGHT (720) //リザルトの高さ

//プロトタイプ宣言
void InitResult(void); //リザルト画面の初期化処理
void UninitResult(void); //リザルト画面の終了処理
void UpdateResult(void); //リザルト画面の更新処理
void DrawResult(void); //リザルト画面の描画処理

#endif //※最下行に必ず書くこと※