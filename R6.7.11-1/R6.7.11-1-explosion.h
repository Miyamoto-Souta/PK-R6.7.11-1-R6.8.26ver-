#ifndef _EXPLOSION_H_ //このマクロ定義がされていなかった場合※1行目に必ず書くこと※

#define _EXPLOSION_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"

//マクロ定義
#define BULLET_WIDTH (150) //ショット弾爆発の幅
#define BULLET_HEIGHT (200) //ショット弾爆発の高さ

//プロトタイプ宣言
void InitExplosion(void); //ショット弾爆発の初期化処理
void UninitExplosion(void); //ショット弾爆発の終了処理
void UpdateExplosion(void); //ショット弾爆発の更新処理
void DrawExplosion(void); //ショット弾爆発の描画処理
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col); //ショット弾爆発の設定処理 pos…発生位置 col…色を指定する
													 //爆発はその場から動かないため、move(移動量)ではなく代わりにcolを用いる

#endif //※最下行に必ず書くこと※