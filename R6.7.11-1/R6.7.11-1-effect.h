#ifndef _EFFECT_H_ //このマクロ定義がされていなかった場合※1行目に必ず書くこと※

#define _EFFECT_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"

//マクロ定義
//#define BULLET_WIDTH (150) //ショット弾の幅
//#define BULLET_HEIGHT (200) //ショット弾の高さ
#define MAX_LIFE (150) //エフェクトが消滅するまでの時間

//ショット弾構造体の定義
//typedef struct
//{
//	D3DXVECTOR3 pos; //位置
//	D3DXVECTOR3 move; //移動量
//	int nLife; //弾が消滅するまでの時間
//	BULLETTYPE type; //弾の種類(弾が自機のショット,敵の攻撃のどちらなのかを判別出来るようにする)
//	bool bUse; //使用しているかどうか
//} Bullet;

//弾の種類
//typedef enum
//{
//	BULLETTYPE_PLAYER1 = 0, //プレイヤー1の弾
//	BULLETTYPE_ENEMY, //敵の弾
//	BULLETTYPE_MAX
//} BULLETTYPE;

//プロトタイプ宣言
void InitEffect(void); //エフェクトの初期化処理
void UninitEffect(void); //エフェクトの終了処理
void UpdateEffect(void); //エフェクトの更新処理
void DrawEffect(void); //エフェクトの描画処理
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife); //エフェクトの設定処理
//pos…位置 col…頂点カラー fRadius…エフェクトの半径(大きさ) nLife…エフェクトが消滅するまでの時間

#endif //※最下行に必ず書くこと※