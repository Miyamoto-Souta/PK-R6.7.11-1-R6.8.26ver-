#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
							// 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-player1.h"

//マクロ定義
#define MAX_EXPLOSION (128) //ショット弾爆発の最大数

//ショット弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXCOLOR col; //色
	int nCounterAnimExplosion; //アニメーションカウンター
	int nPatternAnimExplosion; //アニメーションパターンの番号
	bool bUse; //使用しているかどうか
} Explosion;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferExplosion = NULL; //頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION]; //ショット弾爆発の情報

//ショット弾爆発の初期化処理=======================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDeviceExplosion; //デバイスへのポインタを宣言
	int nCountExplosion; //ショット弾爆発の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceExplosion = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDeviceExplosion,
							  "data\\TEXTURE\\explosion000.png",
							  &g_pTextureExplosion);

	//ショット弾爆発の情報の初期化
	for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		g_aExplosion[nCountExplosion].pos = D3DXVECTOR3(150.0f, 450.0f, 0.0f); //ショット弾爆発の位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};
		g_aExplosion[nCountExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //ショット弾爆発の色を初期化する {D3DXCOLOR(赤, 緑, 青, 透明度)};
		g_aExplosion[nCountExplosion].bUse = false; //falseの場合、使用していない状態になる

		//頂点バッファの生成
		pDeviceExplosion->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数 * ショット弾の最大数}
										     D3DUSAGE_WRITEONLY,
										     FVF_VERTEX_2D, //頂点フォーマット
										     D3DPOOL_MANAGED,
										     &g_pVertexBufferExplosion,
										     NULL);

		VERTEX_2D* pVertexExplosion; //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
		g_pVertexBufferExplosion->Lock(0, 0, (void**)&pVertexExplosion, 0);

		for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
		{
			//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・

			//頂点座標の設定 ※必ず右回りになるように設定すること!!※
			pVertexExplosion[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
			pVertexExplosion[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //1番目の頂点
			pVertexExplosion[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //2番目の頂点
			pVertexExplosion[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //3番目の頂点

			//rhwの設定
			pVertexExplosion[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
			pVertexExplosion[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
			pVertexExplosion[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
			pVertexExplosion[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

			//頂点カラーの設定
			pVertexExplosion[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //0番目の頂点{D3DXCOLOR(赤, 緑, 青, 透明度)};
			pVertexExplosion[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //1番目の頂点
			pVertexExplosion[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //2番目の頂点
			pVertexExplosion[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //3番目の頂点

			//テクスチャ座標の設定
			pVertexExplosion[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
			pVertexExplosion[1].tex = D3DXVECTOR2(0.125f, 0.0f); //1番目の頂点
			pVertexExplosion[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
			pVertexExplosion[3].tex = D3DXVECTOR2(0.125f, 1.0f); //3番目の頂点

			pVertexExplosion += 4; //頂点データのポインタを4つ分進める
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferExplosion->Unlock();
}

//ショット弾爆発の更新処理=========================================================
void UpdateExplosion(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceExplosion; //デバイスへのポインタを宣言
	VERTEX_2D* pVertexExplosion; //頂点情報へのポインタ
	int nCountExplosion; //ショット弾の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceExplosion = GetDevice();

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferExplosion->Lock(0, 0, (void**)&pVertexExplosion, 0);

	for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if(g_aExplosion[nCountExplosion].bUse == true) //使用されている爆発のみに更新処理を適用する
		{
			if ((g_aExplosion[nCountExplosion].nCounterAnimExplosion % 60) == 0) //一定時間(60F)経過した場合
			{
				g_aExplosion[nCountExplosion].nPatternAnimExplosion++; //アニメーションパターンの番号を更新(加算)する

				//アニメーションパターンの番号を更新(加算)する
				g_aExplosion[nCountExplosion].nPatternAnimExplosion = (g_aExplosion[nCountExplosion].nPatternAnimExplosion) % 9; //9…総パターン数

				if (g_aExplosion[nCountExplosion].nPatternAnimExplosion > 9) //アニメーションパターンの総数を超えた場合
				{
					g_aExplosion[nCountExplosion].bUse == false; //爆発を使用していない状態にする
				}

				//ショット弾爆発の位置の更新
				//g_aExplosion[nCountExplosion].pos.y += g_aExplosion[nCountExplosion].move.y; //プレイヤー1の現在位置のY座標にY方向の移動量を加算させる

				//ショット弾爆発の頂点座標の更新
				pVertexExplosion[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
				pVertexExplosion[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //1番目の頂点
				pVertexExplosion[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //2番目の頂点
				pVertexExplosion[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //3番目の頂点

				//テクスチャ座標(UV)を更新する処理
				pVertexExplosion[0].tex = D3DXVECTOR2(g_aExplosion[nCountExplosion].nPatternAnimExplosion * 0.0f, 1.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
				pVertexExplosion[1].tex = D3DXVECTOR2(g_aExplosion[nCountExplosion].nPatternAnimExplosion * 0.125f, 1.0f); //1番目の頂点
				pVertexExplosion[2].tex = D3DXVECTOR2(g_aExplosion[nCountExplosion].nPatternAnimExplosion * 0.0f, 1.0f); //2番目の頂点
				pVertexExplosion[3].tex = D3DXVECTOR2(g_aExplosion[nCountExplosion].nPatternAnimExplosion * 0.125f, 1.0f); //3番目の頂点
			
				//画面端の処理ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・

			}
		}
		pVertexExplosion += 4; //頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferExplosion->Unlock();
}

//ショット弾爆発の描画処理=========================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDeviceExplosion; //デバイスへのポインタを宣言
	int nCountExplosion; //ショット弾爆発の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceExplosion = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceExplosion->SetStreamSource(0, g_pVertexBufferExplosion, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferExplosion…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceExplosion->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDeviceExplosion->SetTexture(0, g_pTextureExplosion);

	for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if (g_aExplosion[nCountExplosion].bUse == true) //使用されているショット弾のみに描画処理を適用する
		{
			//ポリゴンの描画
			pDeviceExplosion->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountExplosion * 4, 2);
			//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , nCountBullet * 4…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
		}
	}
}

//ショット弾爆発の設定処理=========================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceExplosion; //デバイスへのポインタを宣言
	VERTEX_2D* pVertexExplosion; //頂点情報へのポインタ
	int nCountExplosion; //ショット弾爆発の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceExplosion = GetDevice();

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferExplosion->Lock(0, 0, (void**)&pVertexExplosion, 0);

	for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if (g_aExplosion[nCountExplosion].bUse == false) //使用されていない爆発のみに更新処理を適用する
		{
			pVertexExplosion += 4 * nCountExplosion;

			g_aExplosion[nCountExplosion].pos = pos;

			g_aExplosion[nCountExplosion].nCounterAnimExplosion = 0; //アニメーションカウンターを初期化する
			g_aExplosion[nCountExplosion].nPatternAnimExplosion = 0; //アニメーションパターンの番号を初期化する

			//頂点座標の設定 ※必ず右回りになるように設定すること!!※
			pVertexExplosion[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
			pVertexExplosion[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //1番目の頂点
			pVertexExplosion[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //2番目の頂点
			pVertexExplosion[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //3番目の頂点

			//rhwの設定
			pVertexExplosion[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
			pVertexExplosion[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
			pVertexExplosion[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
			pVertexExplosion[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

			//頂点カラーの設定
			pVertexExplosion[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //0番目の頂点{D3DXCOLOR(赤, 緑, 青, 透明度)};
			pVertexExplosion[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //1番目の頂点
			pVertexExplosion[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //2番目の頂点
			pVertexExplosion[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //3番目の頂点

			//テクスチャ座標の設定
			pVertexExplosion[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
			pVertexExplosion[1].tex = D3DXVECTOR2(0.125f, 0.0f); //1番目の頂点
			pVertexExplosion[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
			pVertexExplosion[3].tex = D3DXVECTOR2(0.125f, 1.0f); //3番目の頂点

			break;
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferExplosion->Unlock();
}

//ショット弾の終了処理=========================================================
void UninitExplosion(void)
{
	//テクスチャの破棄①
	if (g_pTextureExplosion != NULL) //g_pTextureExplosionにテクスチャが設定されている場合、
								     // テクスチャを破棄する処理
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVertexBufferExplosion != NULL)
	{
		g_pVertexBufferExplosion->Release();
		g_pVertexBufferExplosion = NULL;
	}
}