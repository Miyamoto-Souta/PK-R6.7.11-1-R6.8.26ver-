#include "R6.7.11-1-game.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
#include "R6.7.11-1-input.h" //自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-background.h"
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-player2.h"
#include "R6.7.11-1-enemy1.h"
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-sound.h"
#include "R6.7.11-1-score.h"
#include "R6.7.11-1-effect.h"

//グローバル変数宣言
GAMESTATE g_GameState = GAMESTATE_NONE; //ゲームの状態
int g_nCounterGameState = 0; //状態管理カウンター
Enemy* pEnemy1; //敵の情報へのポインタ

//ゲーム画面の初期化処理=======================================================
void InitGame(void)
{
	//各オブジェクトの初期化処理-----------------------------------------------
	InitPlayer1(); //プレイヤー1の初期化処理の関数を呼び出す
	InitPlayer2(); //プレイヤー2の初期化処理の関数を呼び出す
	InitBackground(); //背景の初期化処理の関数を呼び出す
	InitBullet(); //ショット弾の初期化処理の関数を呼び出す
	InitExplosion(); //ショット弾爆発の初期化処理
	InitEnemy1(); //敵1の初期化処理の関数を呼び出す
	InitEffect(); //エフェクトの初期化処理の関数を呼び出す
	SetEnemy1(pEnemy1->pos, g_aEnemy1[nCountEnemy1].nType); //敵1の設定処理の関数を呼び出す 位置, 種類
	SetEnemy1(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0); //敵1の設定処理の関数を呼び出す 位置, 種類
	SetEnemy1(D3DXVECTOR3(100.0f, 100.0f, 100.0f), 1); //敵1の設定処理の関数を呼び出す 位置, 種類
	InitScore(); //スコアの初期化処理の関数を呼び出す

	GAMESTATE g_GameState = GAMESTATE_NOMAL; //ゲームの状態を通常状態に設定
	int g_nCounterGameState = 0;

	//サウンドを再生する
	PlaySound(SOUND_LABEL_GAME_BGM); //SOUND_LABEL_BGMに指定した音声ファイルを再生する
	PlaySound(SOUND_LABEL_SE); //SOUND_LABEL_SEに指定した音声ファイルを再生する
}

//ゲーム画面の更新処理=========================================================
void UpdateGame(void)
{
	int nEnemyTotal = EnemyTotal(); //現在の敵の総数を引き出すための変数

	//各オブジェクトの更新処理-------------------------------------------------
	UpdatePlayer1(); //プレイヤー1の更新処理の関数を呼び出す
	UpdatePlayer2(); //プレイヤー2の更新処理の関数を呼び出す
	UpdateBackground(); //背景の更新処理の関数を呼び出す
	UpdateBullet(); //ショット弾の更新処理の関数を呼び出す
	UpdateExplosion(); //ショット弾爆発の更新処理の関数を呼び出す
	UpdateEnemy1(); //敵1の更新処理の関数を呼び出す
	UpdateScore(); //スコアの更新処理の関数を呼び出す
	UpdateEffect(); //エフェクトの更新処理の関数を呼び出す

	switch (g_GameState)
	{
	case GAMESTATE_NOMAL: //通常状態
		break;

	case GAMESTATE_END: //終了状態
		g_nCounterGameState++; //状態管理カウンターの値を(毎Fごとに)インクリメント(カウントアップ)する

		if (g_nCounterGameState >= 60) //
		{
			g_GameState = GAMESTATE_NONE; //何もしていない状態に設定

			//画面(モード)の設定
			SetMode(MODE_RESULT); //
		}

		break;
	}

	//画面遷移の条件を設定する
	if (GetKeyboardTrigger(DIK_RETURN) == true) //決定(ENTERキー)が押された場合
	{
		//モード設定(ゲーム画面に移行する)
		SetMode(MODE_GAME);
	}

	if (nEnemyTotal <= 0) //敵の総数が0以下になった場合
	{
		//モード設定(リザルト画面に移行する) ←ここに置くのは正しくない!!
		SetMode(MODE_RESULT);
	}

}

//ゲーム画面の描画処理=========================================================
void DrawGame(void)
{
	//各種オブジェクトの描画処理-----------------------------------------------
	// (一番下の行にあるものが一番前に描画される)
	DrawBackground(); //背景の更新処理の関数を呼び出す
	DrawPlayer2(); //プレイヤー2の描画処理の関数を呼び出す
	DrawBullet(); //ショット弾の描画処理の関数を呼び出す
	DrawEnemy1(); //敵1の描画処理の関数を呼び出す
	DrawEffect(); //エフェクトの描画処理の関数を呼び出す
	DrawExplosion(); //ショット弾爆発の描画処理の関数を呼び出す
	DrawPlayer1(); //プレイヤー1の描画処理の関数を呼び出す
	DrawScore(); //スコアの描画処理の関数を呼び出す
}

//ゲーム画面の終了処理=========================================================
void UninitGame(void)
{
	//サウンドを停止する
	StopSound();

	//各オブジェクトの終了処理-----------------------------------------------
	UninitPlayer1(); //プレイヤー1の終了処理の関数を呼び出す
	UninitPlayer2(); //プレイヤー2の終了処理の関数を呼び出す
	UninitEnemy1(); //敵1の終了処理の関数を呼び出す
	UninitBackground(); //背景の終了処理の関数を呼び出す
	UninitBullet(); //ショット弾爆発の終了処理の関数を呼び出す
	UninitExplosion(); //ショット弾爆発の終了処理の関数を呼び出す
	UninitScore(); //スコアの終了処理の関数を呼び出す
	UninitEffect(); //エフェクトの終了処理の関数を呼び出す
}

//ゲーム状態の設定処理=========================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state; //

	g_nCounterGameState = 0;
}

//ゲーム状態の取得処理=========================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}