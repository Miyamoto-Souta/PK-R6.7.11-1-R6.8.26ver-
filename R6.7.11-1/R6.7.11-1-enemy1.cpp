#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
//自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-enemy1.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-bullet.h"

//マクロ定義
#define NUM_ENEMY1 (4) //敵の種類の最大数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureEnemy1[NUM_ENEMY1] = {}; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferEnemy1 = NULL; //頂点バッファへのポインタ
Enemy g_aEnemy1[MAX_ENEMY1]; //敵の情報
//D3DXVECTOR3 g_posEnemy1; //敵1の位置を管理する変数
//D3DXVECTOR3 g_moveEnemy1; //敵1の移動量を管理する変数
int g_nCounterAnimEnemy1; //アニメーションカウンター
int g_nPatternAnimEnemy1; //アニメーションパターンの番号
int g_NumEnemy1 = 0; //敵1の総数を管理する変数

//敵1を取得する処理============================================================
Enemy* GetEnemy1(void)
{
	return &g_aEnemy1[0]; //敵の情報の先頭アドレスを返す
}


//敵1の初期化処理==============================================================
void InitEnemy1(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceEnemy1; //デバイスへのポインタを宣言
	int nCountEnemy1; //敵の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceEnemy1 = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDeviceEnemy1,
		"data\\TEXTURE\\big_fairy001.png",
		&g_apTextureEnemy1[0]);

	//テクスチャの読み込み②
	D3DXCreateTextureFromFile(pDeviceEnemy1,
		"data\\TEXTURE\\big_fairy002.png",
		&g_apTextureEnemy1[1]);

	//テクスチャの読み込み③
	D3DXCreateTextureFromFile(pDeviceEnemy1,
		"data\\TEXTURE\\big_fairy003.png",
		&g_apTextureEnemy1[2]);

	//テクスチャの読み込み④
	D3DXCreateTextureFromFile(pDeviceEnemy1,
		"data\\TEXTURE\\big_fairy004.png",
		&g_apTextureEnemy1[3]);

	//各種数値の初期化
	//g_nCounterAnimEnemy1 = 0; //アニメーションカウンターを初期化する
	//g_nPatternAnimEnemy1 = 0; //アニメーションパターンの番号を初期化する
	g_NumEnemy1 = 0; //敵1の総数を管理する変数を初期化する

	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		g_aEnemy1[nCountEnemy1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //敵1の位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};
		g_aEnemy1[nCountEnemy1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //敵1の移動量を初期化する {D3DXVECTOR3(X方向, Y方向, Z方向)};
	}

	//対角線の長さを算出する処理
	//g_fLengthEnemy1 = sqrtf(ENEMY1_WIDTH * ENEMY1_WIDTH + ENEMY1_HEIGHT * ENEMY1_HEIGHT) / 2.0f; //sqrtf(プレイヤー1の幅 * プレイヤー1の幅 + プレイヤー1の高さ * プレイヤー1の高さ)

	//対角線の角度を算出する処理
	//g_fAngleEnemy1 = atan2f(ENEMY1_WIDTH, ENEMY1_HEIGHT); //atan2f(プレイヤー1の幅 ,プレイヤー1の高さ)

	//頂点バッファの生成
	pDeviceEnemy1->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ENEMY1, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数 × [NUM_ENEMY1]}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVertexBufferEnemy1,
		NULL);

	VERTEX_2D* pVertexEnemy1; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

	//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		//頂点座標の設定 ※必ず右回りになるように設定すること!!※
		pVertexEnemy1[0].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
		pVertexEnemy1[1].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //1番目の頂点
		pVertexEnemy1[2].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //2番目の頂点
		pVertexEnemy1[3].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //3番目の頂点
		//回転,拡大縮小を使わない場合 → pVertexPlayer1[0].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};

		//rhwの設定
		pVertexEnemy1[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
		pVertexEnemy1[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
		pVertexEnemy1[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
		pVertexEnemy1[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

		//頂点カラーの設定
		pVertexEnemy1[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
		pVertexEnemy1[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
		pVertexEnemy1[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
		pVertexEnemy1[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点

		//テクスチャ座標の設定
		pVertexEnemy1[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
		pVertexEnemy1[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1番目の頂点
		pVertexEnemy1[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
		pVertexEnemy1[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3番目の頂点
	}

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferEnemy1->Unlock();
}




//敵1の更新処理================================================================
void UpdateEnemy1(void)
{
	//変数を宣言するところ-----------------------------------------------------
	VERTEX_2D* pVertexEnemy1; //頂点情報へのポインタ
	int nCountEnemy1; //敵の  をカウントするための変数

	g_nCounterAnimEnemy1++; //アニメーションカウンターを加算させる処理

	//移動関連の処理-----------------------------------------------------------

	

	//敵1の位置を更新する処理 ※ここは消さないこと!!※
	g_aEnemy1[0].pos.x += g_aEnemy1[0].move.x; //敵1の現在位置のX座標にX方向の移動量を加算させる
	g_aEnemy1[0].pos.y += g_aEnemy1[0].move.y; //敵1の現在位置のY座標にY方向の移動量を加算させる


	//頂点座標の更新ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

	//頂点座標の設定
	pVertexEnemy1[0].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
	pVertexEnemy1[1].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //1番目の頂点
	pVertexEnemy1[2].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //2番目の頂点
	pVertexEnemy1[3].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //3番目の頂点

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferEnemy1->Unlock();

	//アニメーション関連の処理-------------------------------------------------
	
	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

	if ((g_nCounterAnimEnemy1 % 10) == 0) //一定時間(12F)経過した場合
	{
		g_nPatternAnimEnemy1++; //アニメーションパターンの番号を更新(加算)する

		//移動量がゼロの(その場に留まっている)場合
		if (g_aEnemy1[nCountEnemy1].move.x >= -0.07f && g_aEnemy1[nCountEnemy1].move.x <= 0.07f && g_aEnemy1[nCountEnemy1].move.y >= -0.07f && g_aEnemy1[nCountEnemy1].move.y <= 0.07f)
		{
			g_nPatternAnimEnemy1--; //アニメーションパターンの番号を減算する(＝更新を止めさせる)
		}

		else //移動している場合
		{
			/*if (g_nMoveDirection == 2) //左方向に移動している場合
			{	//テクスチャを左向きにさせる処理
				pVertexPlayer1[0].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
				pVertexPlayer1[1].pos = D3DXVECTOR3(g_posPlayer1.x + 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //1番目の頂点
				pVertexPlayer1[2].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y + 100.0f, 0.0f); //2番目の頂点
				pVertexPlayer1[3].pos = D3DXVECTOR3(g_posPlayer1.x + 75.0f, g_posPlayer1.y + 100.0f, 0.0f); //3番目の頂点
			}

			if (g_nMoveDirection == 2) //右方向に移動している場合
			{	//テクスチャを右向きにさせる処理
				pVertexPlayer1[0].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
				pVertexPlayer1[1].pos = D3DXVECTOR3(g_posPlayer1.x + 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //1番目の頂点
				pVertexPlayer1[2].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y + 100.0f, 0.0f); //2番目の頂点
				pVertexPlayer1[3].pos = D3DXVECTOR3(g_posPlayer1.x + 75.0f, g_posPlayer1.y + 100.0f, 0.0f); //3番目の頂点
			}*/

			/*//アニメーションパターンの番号を更新(加算)する
			g_nPatternAnimEnemy1 = (g_nPatternAnimEnemy1) % 10; //10…総パターン数

			if (g_nPatternAnimEnemy1 > 11) //アニメーションパターンの総数を超えた場合
			{
				g_nPatternAnimEnemy1 = 0; //アニメーションパターンの番号を初期値(0)に戻す
			}*/
		}

		//テクスチャ座標(UV)を更新する処理

		/*//テクスチャ座標の設定
		pVertexEnemy1[0].tex = D3DXVECTOR2(g_nPatternAnimEnemy1 * 0.2f, g_nPatternAnimEnemy1 / 5 * 0.5f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
		pVertexEnemy1[1].tex = D3DXVECTOR2(g_nPatternAnimEnemy1 * 0.2f + 0.2f, g_nPatternAnimEnemy1 / 5 * 0.5f); //1番目の頂点
		pVertexEnemy1[2].tex = D3DXVECTOR2(g_nPatternAnimEnemy1 * 0.2f, g_nPatternAnimEnemy1 / 5 * 0.5 + 0.5f); //2番目の頂点
		pVertexEnemy1[3].tex = D3DXVECTOR2(g_nPatternAnimEnemy1 * 0.2f + 0.2f, g_nPatternAnimEnemy1 / 5 * 0.5 + 0.5f); //3番目の頂点*/


		//else if (6 <= g_nPatternAnimPlayer2 <= 10)
		//{
			//pVertexPlayer2[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 0.5f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
			//pVertexPlayer2[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 0.5f); //1番目の頂点
			//pVertexPlayer2[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 1.0f); //2番目の頂点
			//pVertexPlayer2[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 1.0f); //3番目の頂点
		//}

		//敵の状態によって行動をさせる処理
		for (nCountEnemy1 = 0; nCountEnemy1 < MAX_ENEMY1; nCountEnemy1++)
		{
			if (g_aEnemy1[nCountEnemy1].bUse == true) //敵が使用されている場合
			{
				switch (g_aEnemy1[nCountEnemy1].state)
				{
				case ENEMYSTATE_NOMAL: //敵が通常状態である場合
					
					/*if (一定時間が経過したら)
					{
						SetBullet(g_aEnemy1[nCountEnemy1].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY); //SetBullet(位置, 移動量, 弾の種類);
					}*/
					break;
					
				case ENEMYSTATE_DAMAGE: //敵がダメージ状態である場合
					
					g_aEnemy1[nCountEnemy1].nCounterState--; //状態管理カウンターを毎Fデクリメントしていく

					if(g_aEnemy1[nCountEnemy1].nCounterState <= 0) //状態管理カウンターの数値が0以下になった場合
					{ 
						g_aEnemy1[nCountEnemy1].state = ENEMYSTATE_NOMAL; //敵の状態を通常状態にする

						//頂点カラーの設定(ポリゴンを通常色に戻す)
						pVertexEnemy1[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
						pVertexEnemy1[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
						pVertexEnemy1[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
						pVertexEnemy1[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点
					}
					break;					
				}
			}
		}

		//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
		g_pVertexBufferEnemy1->Unlock();
	}
}

//敵1の描画処理========================================================
void DrawEnemy1(void)
{
	LPDIRECT3DDEVICE9 pDeviceEnemy1; //デバイスへのポインタを宣言
	int nCountEnemy1; //敵の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceEnemy1 = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceEnemy1->SetStreamSource(0, g_pVertexBufferEnemy1, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceEnemy1->SetFVF(FVF_VERTEX_2D);

	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		//テクスチャの設定
		pDeviceEnemy1->SetTexture(0, g_apTextureEnemy1[nCountEnemy1]);

		//ポリゴンの描画
		pDeviceEnemy1->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , 0…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
	}
}

//敵1の設定処理(pos…出現位置 int nType…種類)=================================
void SetEnemy1(D3DXVECTOR3 pos, int nType)
{
	//変数を宣言するところ-----------------------------------------------------
	int nCountEnemy1; //敵の  をカウントするための変数
	LPDIRECT3DDEVICE9 pDeviceEnemy1; //デバイスへのポインタを宣言
	VERTEX_2D* pVertexEnemy1; //頂点情報へのポインタ

	//デバイスの取得(ゲッター)処理
	pDeviceEnemy1 = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceEnemy1->SetStreamSource(0, g_pVertexBufferEnemy1, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		pVertexEnemy1 += 4 * nCountEnemy1; //頂点データのポインタを4つ分進める

		if (g_aEnemy1[nCountEnemy1].bUse == false) //敵が使用されていない場合
		{
			//敵の情報の設定(出現させる際のもの)
			
			//頂点座標の設定
			pVertexEnemy1[0].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
			pVertexEnemy1[1].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //1番目の頂点
			pVertexEnemy1[2].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //2番目の頂点
			pVertexEnemy1[3].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //3番目の頂点

			g_aEnemy1[nCountEnemy1].bUse = true; //敵を使用されている状態にする
			g_aEnemy1[nCountEnemy1].pos = pos; //敵の出現位置を設定する
			g_aEnemy1[nCountEnemy1].nType = nType; //敵の種類を設定する
			g_aEnemy1[nCountEnemy1].state = ENEMYSTATE_NOMAL; //敵の状態を設定する
			g_aEnemy1[nCountEnemy1].nCounterState = 0; //状態管理カウンターを設定する

			g_NumEnemy1++; //敵1の総数を管理する変数をインクリメント(カウントアップ)する
			break;
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferEnemy1->Unlock();
}

//敵1の終了処理-----------------------------------------------------------
void UninitEnemy1(void)
{
	int nCountEnemy1; //敵の  をカウントするための変数

	//テクスチャの破棄
	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		if (g_apTextureEnemy1[nCountEnemy1] != NULL) //g_apTextureBackground[nCountBackGround]に
															 // テクスチャが設定されている場合、テクスチャを破棄する処理
		{
			g_apTextureEnemy1[nCountEnemy1]->Release();
			g_apTextureEnemy1[nCountEnemy1] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVertexBufferEnemy1 != NULL)
	{
		g_pVertexBufferEnemy1->Release();
		g_pVertexBufferEnemy1 = NULL;
	}
}

//敵1の被弾処理================================================================
inline void HitEnemy1(int nCountEnemy1, int nDamage)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceEnemy1; //デバイスへのポインタを宣言
									 //int nCountEnemy1; //敵の  をカウントするための変数
	VERTEX_2D* pVertexEnemy1; //頂点情報へのポインタ

							  //デバイスの取得(ゲッター)処理
	pDeviceEnemy1 = GetDevice();

	g_aEnemy1[nCountEnemy1].nLife -= 1;

	if (g_aEnemy1[nCountEnemy1].nLife <= 0) //敵の体力が0以下になった場合
	{
		//爆発の設定
		SetExplosion(g_aEnemy1[nCountEnemy1].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //位置, 色

		g_aEnemy1[nCountEnemy1].bUse = false; //敵1を使用していない状態にする

		g_NumEnemy1--; //敵1の総数を管理する変数をインクリメント(カウントダウン)する

		if (g_NumEnemy1 <= 0) //敵の総数が0以下になった場合
		{
			//モード設定(リザルト画面に移行する) ←ここに置くのは正しくない!!
			SetMode(MODE_RESULT);
		}
	}

	else //敵の体力が0を超過している場合
	{
		g_aEnemy1[nCountEnemy1].state = ENEMYSTATE_DAMAGE;
		g_aEnemy1[nCountEnemy1].nCounterState = 5; //ダメージ状態を保持する時間を設定する

		pVertexEnemy1 += 4 * nCountEnemy1; //頂点データのポインタを4つ分進める

		//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
		g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

		//頂点カラーの設定(ポリゴンをダメージ色に変更する)
		pVertexEnemy1[0].col = D3DCOLOR_RGBA(255, 0, 0, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
		pVertexEnemy1[1].col = D3DCOLOR_RGBA(255, 0, 0, 255); //1番目の頂点
		pVertexEnemy1[2].col = D3DCOLOR_RGBA(255, 0, 0, 255); //2番目の頂点
		pVertexEnemy1[3].col = D3DCOLOR_RGBA(255, 0, 0, 255); //3番目の頂点

		//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
		g_pVertexBufferEnemy1->Unlock();
	}
}

//現在の敵の総数を管理する処理=================================================
int EnemyTotal()
{
	return g_NumEnemy1; //現在の敵の総数を返す
}