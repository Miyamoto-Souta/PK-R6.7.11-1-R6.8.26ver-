#ifndef _ENEMY1_H_ //このマクロ定義がされていなかった場合※1行目に必ず書くこと※

#define _ENEMY1_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include <math.h>
#include "R6.7.11-1-main.h"

//マクロ定義
#define MAX_ENEMY1 (128) //敵の最大数
#define ENEMY1_WIDTH (64) //敵1の幅
#define ENEMY1_HEIGHT (53) //敵1の高さ

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 move; //移動量
	D3DXVECTOR3 movebullet; //敵弾の移動量
	int nType; //種類
	ENEMYSTATE state; //状態
	int nCounterState; //状態管理カウンター
	int nLife = 5; //体力
	bool bUse; //使用しているかどうか
} Enemy;

//敵の状態
typedef enum
{
	ENEMYSTATE_NOMAL = 0, //通常状態
	ENEMYSTATE_DAMAGE, //ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//プロトタイプ宣言
void InitEnemy1(void); //敵1の初期化処理
void UninitEnemy1(void); //敵1の終了処理
void UpdateEnemy1(void); //敵1の更新処理
void DrawEnemy1(void); //敵1の描画処理
void SetEnemy1(D3DXVECTOR3 pos, int nType); //敵1の設定処理 pos…出現位置 int nType…種類
Enemy* GetEnemy1(void); //敵1を取得する処理
inline void HitEnemy1(int nCountEnemy1, int nDamage); //敵1の被弾処理
int EnemyTotal(); //現在の敵の総数を管理する処理

//グローバル変数宣言

#endif //※最下行に必ず書くこと※