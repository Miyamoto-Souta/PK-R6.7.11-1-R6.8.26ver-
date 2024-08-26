#ifndef _PLAYER2_H_ //このマクロ定義がされていなかった場合※1行目に必ず書くこと※

#define _PLAYER2_H_ //多重インクルード(読み込み)防止用のマクロ定義

//プロトタイプ宣言
void InitPlayer2(void); //プレイヤー2の初期化処理
void UninitPlayer2(void); //プレイヤー2の終了処理
void UpdatePlayer2(void); //プレイヤー2の更新処理
void DrawPlayer2(void); //プレイヤー2の描画処理

#endif //※最下行に必ず書くこと※