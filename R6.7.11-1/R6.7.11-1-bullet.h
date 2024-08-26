#ifndef _BULLET_H_ //このマクロ定義がされていなかった場合※1行目に必ず書くこと※

#define _BULLET_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"

//マクロ定義
#define BULLET_WIDTH (150) //ショット弾の幅
#define BULLET_HEIGHT (200) //ショット弾の高さ
#define MAX_LIFE (150) //ショット弾が消滅するまでの時間

//ショット弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 move; //移動量
	int nLife; //弾が消滅するまでの時間
	BULLETTYPE type; //弾の種類(弾が自機のショット,敵の攻撃のどちらなのかを判別出来るようにする)
	bool bUse; //使用しているかどうか
} Bullet;

//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER1 = 0, //プレイヤー1の弾
	BULLETTYPE_ENEMY, //敵の弾
	BULLETTYPE_MAX
} BULLETTYPE;

//プロトタイプ宣言
void InitBullet(void); //ショット弾の初期化処理
void UninitBullet(void); //ショット弾の終了処理
void UpdateBullet(void); //ショット弾の更新処理
void DrawBullet(void); //ショット弾の描画処理
Bullet* GetBullet(void); //弾を取得する処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type); //ショット弾の設定処理
//pos…発射位置 move…移動量 nLife…弾が消滅するまでの時間 type…弾の種類

#endif //※最下行に必ず書くこと※