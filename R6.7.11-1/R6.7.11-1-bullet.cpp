#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
							// 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-enemy1.h"

//マクロ定義
#define MAX_BULLET (128) //ショット弾の最大数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferBullet = NULL; //頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET]; //ショット弾の情報

//弾を取得する処理============================================================
Bullet* GetBullet(void)
{
	return &g_aBullet[0]; //弾の情報の先頭アドレスを返す
}

//ショット弾の初期化処理=======================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDeviceBullet; //デバイスへのポインタを宣言
	int nCountBullet; //ショット弾の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceBullet = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDeviceBullet,
							  "data\\TEXTURE\\bullet000.png",
							  &g_pTextureBullet);

	//ショット弾の情報の初期化
	for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		g_aBullet[nCountBullet].pos = D3DXVECTOR3(150.0f, 450.0f, 0.0f); //ショット弾の位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};
		g_aBullet[nCountBullet].move = D3DXVECTOR3(0.0f, -4.0f, 0.0f); //ショット弾の移動量を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};
		g_aBullet[nCountBullet].nLife = MAX_LIFE; //ショット弾が消滅するまでの時間を設定する
		g_aBullet[nCountBullet].bUse = false; //falseの場合、使用していない状態になる

		//頂点バッファの生成
		pDeviceBullet->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数 * ショット弾の最大数}
										  D3DUSAGE_WRITEONLY,
										  FVF_VERTEX_2D, //頂点フォーマット
										  D3DPOOL_MANAGED,
										  &g_pVertexBufferBullet,
										  NULL);

		VERTEX_2D* pVertexBullet; //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
		g_pVertexBufferBullet->Lock(0, 0, (void**)&pVertexBullet, 0);

		for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
		{
			//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・

			//頂点座標の設定 ※必ず右回りになるように設定すること!!※
			pVertexBullet[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
			pVertexBullet[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //1番目の頂点
			pVertexBullet[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //2番目の頂点
			pVertexBullet[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //3番目の頂点

			//rhwの設定
			pVertexBullet[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
			pVertexBullet[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
			pVertexBullet[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
			pVertexBullet[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

			//頂点カラーの設定
			pVertexBullet[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //0番目の頂点{D3DXCOLOR(赤, 緑, 青, 透明度)};
			pVertexBullet[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //1番目の頂点
			pVertexBullet[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //2番目の頂点
			pVertexBullet[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //3番目の頂点

			//テクスチャ座標の設定
			pVertexBullet[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
			pVertexBullet[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1番目の頂点
			pVertexBullet[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
			pVertexBullet[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3番目の頂点

			pVertexBullet += 4; //頂点データのポインタを4つ分進める
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferBullet->Unlock();	
}

//ショット弾の更新処理=========================================================
void UpdateBullet(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceBullet; //デバイスへのポインタを宣言
	VERTEX_2D* pVertexBullet; //頂点情報へのポインタ
	int nCountBullet; //ショット弾の  をカウントするための変数
	int nCountExplosion; //ショット弾爆発の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceBullet = GetDevice();

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferBullet->Lock(0, 0, (void**)&pVertexBullet, 0);

	for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		if(g_aBullet[nCountBullet].bUse == true) //使用されているショット弾のみに更新処理を適用する
		{
			//ショット弾の位置の更新
			g_aBullet[nCountBullet].pos.y += g_aBullet[nCountBullet].move.y; //プレイヤー1の現在位置のY座標にY方向の移動量を加算させる

			//ショット弾の頂点座標の更新
			pVertexBullet[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
			pVertexBullet[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //1番目の頂点
			pVertexBullet[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //2番目の頂点
			pVertexBullet[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //3番目の頂点

			Player1* pPlayer1; //プレイヤー1の情報へのポインタ
			Enemy* pEnemy1; //敵の情報へのポインタ
			int nCountEnemy1; //敵の  をカウントするための変数

			pPlayer1 = GetPlayer1(); //プレイヤー1を取得する
								     //プレイヤー1の情報への先頭アドレスが代入される
			pEnemy1 = GetEnemy1(); //敵を取得する
								   //敵の情報への先頭アドレスが代入される

			for (nCountEnemy1 = 0; nCountEnemy1 < MAX_ENEMY1; nCountEnemy1++, pEnemy1++)
			{
				if (pEnemy1->bUse == true) //敵が使用されている場合
				{
					if (g_aBullet[nCountBullet].type == BULLETTYPE_PLAYER1) //この弾がプレイヤー1の弾である場合
					{
						if (g_aBullet[nCountBullet].pos.x >= (pEnemy1->pos.x - (ENEMY1_WIDTH / 2)) && g_aBullet[nCountBullet].pos.x <= (pEnemy1->pos.x + (ENEMY1_WIDTH / 2)) && g_aBullet[nCountBullet].pos.y >= (pEnemy1->pos.y - (ENEMY1_HEIGHT / 2)) && g_aBullet[nCountBullet].pos.y <= (pEnemy1->pos.y + (ENEMY1_HEIGHT / 2))) //ショット弾が敵に当たった場合
							  // ｼｮｯﾄ弾のX座標 >= 敵の左端 && ｼｮｯﾄ弾のX座標 <= 敵の右端 && ｼｮｯﾄ弾のY座標 >= 敵の上端 && ｼｮｯﾄ弾のY座標 <= 敵の下端
						{
							//敵の被弾処理
							HitEnemy1(nCountEnemy1, 1); //敵が被弾したときにnDamageの値を1減らす

							//爆発の設定
							SetExplosion(g_aBullet[nCountBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //位置, 色

							pEnemy1->bUse = false; //敵を使用していない状態にする
							g_aBullet[nCountBullet].bUse = false; //ショット弾を使用していない状態にする
						}
					}

					else if (g_aBullet[nCountBullet].type == BULLETTYPE_ENEMY) //この弾が敵の弾である場合
					{
						if (g_aBullet[nCountBullet].pos.x >= (pPlayer1->pos.x - (PLAYER1_WIDTH / 2)) && g_aBullet[nCountBullet].pos.x <= (pPlayer1->pos.x + (PLAYER1_WIDTH / 2)) && g_aBullet[nCountBullet].pos.y >= (pPlayer1->pos.y - (PLAYER1_HEIGHT / 2)) && g_aBullet[nCountBullet].pos.y <= pPlayer1->pos.y + ((PLAYER1_HEIGHT / 2))) //敵弾がプレイヤー1に当たった場合
							  // 敵弾のX座標 >= プレイヤー1の左端 && 敵弾のX座標 <= プレイヤー1の右端 && 敵弾のY座標 >= プレイヤー1の上端 && 敵弾のY座標 <= プレイヤー1の下端
						{
							//爆発の設定
							SetExplosion(g_aBullet[nCountBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //位置, 色

							g_aBullet[nCountBullet].bUse = false; //ショット弾を使用していない状態にする
						}
					}
				}
			}

			//ショット弾を使用していない状態にする処理-------------------------------------
			
			//画面端の処理ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・

			//ショット弾が画面の上端に当たった場合
			if (g_aBullet[nCountBullet].pos.y <= 20)
			{
				g_aBullet[nCountBullet].bUse = false; //ショット弾を使用していない状態にする
			}

			//ショット弾が画面の左端に当たった場合
			else if (g_aBullet[nCountBullet].pos.x <= 20)
			{
				g_aBullet[nCountBullet].bUse = false; //ショット弾を使用していない状態にする
			}

			//ショット弾が画面の右端に当たった場合
			else if (g_aBullet[nCountBullet].pos.x >= SCREEN_WIDTH - 20)
			{
				g_aBullet[nCountBullet].bUse = false; //ショット弾を使用していない状態にする
			}

			//ショット弾が画面の下端に当たった場合
			else if (g_aBullet[nCountBullet].pos.y >= SCREEN_HEIGHT - 20)
			{
				g_aBullet[nCountBullet].bUse = false; //ショット弾を使用していない状態にする
			}

			//ショット弾が生成されてからの時間を計測する
			g_aBullet[nCountBullet].nLife--;

			if (g_aBullet[nCountBullet].nLife < 0) //ショット弾が消滅するまでの時間を超過した場合
			{
				//ショット弾爆発の設定
				SetExplosion(g_aBullet[nCountBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //位置,色

				g_aBullet[nCountBullet].bUse = false; //ショット弾を使用していない状態にする
			}
		}
		pVertexBullet += 4; //頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferBullet->Unlock();
}

//ショット弾の描画処理=========================================================
void DrawBullet(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceBullet; //デバイスへのポインタを宣言
	int nCountBullet; //ショット弾の  をカウントするための変数

	VERTEX_2D* pVertexBullet; //頂点情報へのポインタ

	//デバイスの取得(ゲッター)処理
	pDeviceBullet = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceBullet->SetStreamSource(0, g_pVertexBufferBullet, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceBullet->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDeviceBullet->SetTexture(0, g_pTextureBullet);

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferBullet->Lock(0, 0, (void**)&pVertexBullet, 0);

	for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == true) //使用されているショット弾のみに描画処理を適用する
		{
			//ポリゴンの描画
			pDeviceBullet->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountBullet * 4, 2);
			//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , nCountBullet * 4…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferBullet->Unlock();
}

//ショット弾の設定処理=========================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
//pos…発射位置 move…移動量 nLife…弾が消滅するまでの時間 type…弾の種類
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceBullet; //デバイスへのポインタを宣言
	VERTEX_2D* pVertexBullet; //頂点情報へのポインタ
	int nCountBullet; //ショット弾の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceBullet = GetDevice();

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferBullet->Lock(0, 0, (void**)&pVertexBullet, 0);

	for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == false) //使用されていないショット弾のみに更新処理を適用する
		{
			pVertexBullet += 4 * nCountBullet;

			g_aBullet[nCountBullet].pos = pos;

			//頂点座標の設定
			pVertexBullet[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
			pVertexBullet[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //1番目の頂点
			pVertexBullet[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //2番目の頂点
			pVertexBullet[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //3番目の頂点
			g_aBullet[nCountBullet].move = move;
			g_aBullet[nCountBullet].nLife = MAX_LIFE; //ショット弾が消滅するまでの時間
			g_aBullet[nCountBullet].bUse = true; //trueの場合、使用している状態になる

			break;
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferBullet->Unlock();
}

//ショット弾の終了処理=========================================================
void UninitBullet(void)
{
	//テクスチャの破棄①
	if (g_pTextureBullet != NULL) //g_pTexturePolygon1にテクスチャが設定されている場合、
								   // テクスチャを破棄する処理
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVertexBufferBullet != NULL)
	{
		g_pVertexBufferBullet->Release();
		g_pVertexBufferBullet = NULL;
	}
}