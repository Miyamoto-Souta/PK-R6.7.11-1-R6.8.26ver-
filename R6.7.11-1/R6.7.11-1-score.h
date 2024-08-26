#ifndef _SCORE_H_ //このマクロ定義がされていなかった場合 ※1行目に必ず書くこと※

#define _SCORE_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"

//マクロ定義
#define SCORE_WIDTH (35) //スコア1桁分のポリゴンの幅
#define SCORE_HEIGHT (70) //スコア1桁分のポリゴンの高さ

//プロトタイプ宣言
void InitScore(void); //スコアの初期化処理
void UninitScore(void); //スコアの終了処理
void UpdateScore(void); //スコアの更新処理
void DrawScore(void); //スコアの描画処理
void SetScore(int nScore); //スコアの設定処理
void AddScore(int nValue); //スコアの加算処理

#endif //※最下行に必ず書くこと※