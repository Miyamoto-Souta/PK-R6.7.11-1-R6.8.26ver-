#ifndef _PLAYER1_H_ //このマクロ定義がされていなかった場合※1行目に必ず書くこと※

#define _PLAYER1_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include <math.h>

//マクロ定義
#define PLAYER1_WIDTH (150) //プレイヤー1の幅
#define PLAYER1_HEIGHT (200) //プレイヤー1の高さ

//プレイヤー1構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 move; //移動量
	D3DXVECTOR3 movebullet; //ショットの移動量
	D3DXVECTOR3 rot; //向き
	PLAYER1STATE state; //プレイヤー1の状態
	int nCounterState; //状態管理カウンター
	int nLife; //プレイヤー1の体力
	bool bDisp; //プレイヤー1を表示するか表示しないか
	float Length; //対角線の長さ(拡大縮小用)
	float Angle; //対角線の角度(回転用)
	int movedirection; //移動方向
} Player1;

//プレイヤー1の状態
typedef enum
{
	PLAYER1STATE_APPEAR = 0, //出現状態(点滅)
	PLAYER1STATE_NORMAL, //通常状態
	PLAYER1STATE_DAMAGE, //ダメージ状態
	PLAYER1STATE_DEATH, //死亡状態
	PLAYER1STATE_INVINCIBLE, //無敵状態
	PLAYER1STATE_MAX
}PLAYER1STATE;

//プロトタイプ宣言
void InitPlayer1(void); //プレイヤー1の初期化処理
void UninitPlayer1(void); //プレイヤー1の終了処理
void UpdatePlayer1(void); //プレイヤー1の更新処理
void DrawPlayer1(void); //プレイヤー1の描画処理
Player1* GetPlayer1(void); //プレイヤー1を取得する処理
void HitPlayer1(int nDamage); //プレイヤー1の被弾処理

//グローバル変数宣言

#endif //※最下行に必ず書くこと※