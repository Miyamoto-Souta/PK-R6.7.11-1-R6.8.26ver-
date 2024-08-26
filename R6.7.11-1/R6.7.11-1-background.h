#ifndef _BACKGROUND_H_ //このマクロ定義がされていなかった場合※1行目に必ず書くこと※

#define _BACKGROUND_H_ //多重インクルード(読み込み)防止用のマクロ定義

//プロトタイプ宣言
void InitBackground(void); //背景の初期化処理
void UninitBackground(void); //背景の終了処理
void UpdateBackground(void); //背景の更新処理
void DrawBackground(void); //背景の描画処理

#endif //※最下行に必ず書くこと※