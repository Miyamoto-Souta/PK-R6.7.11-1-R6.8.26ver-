#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
							// 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-enemy1.h"
#include "R6.7.11-1-effect.h"

//マクロ定義
#define MAX_EFFECT (4096) //エフェクトの最大数

//エフェクト構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXCOLOR col; //頂点カラー
	float fRadius; //エフェクトの半径(大きさ)
	int nLife; //寿命(エフェクトが消滅するまでの時間)
	bool bUse; //使用しているかどうか
} Effect;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferEffect = NULL; //頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT]; //エフェクトの情報

//エフェクトの初期化処理=======================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDeviceEffect; //デバイスへのポインタを宣言
	int nCountEffect; //エフェクトの  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceEffect = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDeviceEffect,
							  "data\\TEXTURE\\effect000.jpg",
							  &g_pTextureEffect);

	//エフェクトの情報の初期化
	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		g_aEffect[nCountEffect].pos = D3DXVECTOR3(150.0f, 450.0f, 0.0f); //エフェクトの位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};
	    g_aEffect[nCountEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //エフェクトの色を初期化する {D3DXCOLOR(赤, 緑, 青, 透明度)};
		g_aEffect[nCountEffect].nLife = MAX_LIFE; //エフェクトが消滅するまでの時間を設定する
		g_aEffect[nCountEffect].bUse = false; //falseの場合、使用していない状態になる

		//頂点バッファの生成
		pDeviceEffect->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数 * ショット弾の最大数}
										  D3DUSAGE_WRITEONLY,
										  FVF_VERTEX_2D, //頂点フォーマット
										  D3DPOOL_MANAGED,
										  &g_pVertexBufferEffect,
										  NULL);

		VERTEX_2D* pVertexEffect; //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
		g_pVertexBufferEffect->Lock(0, 0, (void**)&pVertexEffect, 0);

		for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
		{
			//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・

			//頂点座標の設定 ※必ず右回りになるように設定すること!!※
			pVertexEffect[0].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x - 10.0f, g_aEffect[nCountEffect].pos.y - 110.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
			pVertexEffect[1].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x + 10.0f, g_aEffect[nCountEffect].pos.y - 110.0f, 0.0f); //1番目の頂点
			pVertexEffect[2].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x - 10.0f, g_aEffect[nCountEffect].pos.y - 90.0f, 0.0f); //2番目の頂点
			pVertexEffect[3].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x + 10.0f, g_aEffect[nCountEffect].pos.y - 90.0f, 0.0f); //3番目の頂点

			//rhwの設定
			pVertexEffect[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
			pVertexEffect[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
			pVertexEffect[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
			pVertexEffect[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

			//頂点カラーの設定
			pVertexEffect[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //0番目の頂点{D3DXCOLOR(赤, 緑, 青, 透明度)};
			pVertexEffect[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //1番目の頂点
			pVertexEffect[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //2番目の頂点
			pVertexEffect[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //3番目の頂点

			//テクスチャ座標の設定
			pVertexEffect[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
			pVertexEffect[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1番目の頂点
			pVertexEffect[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
			pVertexEffect[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3番目の頂点

			pVertexEffect += 4; //頂点データのポインタを4つ分進める
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferEffect->Unlock();
}

//エフェクトの更新処理=========================================================
void UpdateEffect(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceEffect; //デバイスへのポインタを宣言
	VERTEX_2D* pVertexEffect; //頂点情報へのポインタ
	int nCountEffect; //エフェクトの  をカウントするための変数
	int nCountExplosion; //ショット弾爆発の  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceEffect = GetDevice();

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferEffect->Lock(0, 0, (void**)&pVertexEffect, 0);

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if(g_aEffect[nCountEffect].bUse == true) //使用されているエフェクトのみに更新処理を適用する
		{
			//頂点カラーの設定(更新)
			pVertexEffect[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //0番目の頂点{D3DXCOLOR(赤, 緑, 青, 透明度)};
			pVertexEffect[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //1番目の頂点
			pVertexEffect[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //2番目の頂点
			pVertexEffect[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //3番目の頂点

			//頂点座標の設定(更新)
			pVertexEffect[0].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x - 10.0f, g_aEffect[nCountEffect].pos.y - 110.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
			pVertexEffect[1].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x + 10.0f, g_aEffect[nCountEffect].pos.y - 110.0f, 0.0f); //1番目の頂点
			pVertexEffect[2].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x - 10.0f, g_aEffect[nCountEffect].pos.y - 90.0f, 0.0f); //2番目の頂点
			pVertexEffect[3].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x + 10.0f, g_aEffect[nCountEffect].pos.y - 90.0f, 0.0f); //3番目の頂点

			Player1* pPlayer1; //プレイヤー1の情報へのポインタ
			Enemy* pEnemy1; //敵の情報へのポインタ
			int nCountEnemy1; //敵の  をカウントするための変数

			pPlayer1 = GetPlayer1(); //プレイヤー1を取得する
								     //プレイヤー1の情報への先頭アドレスが代入される
			pEnemy1 = GetEnemy1(); //敵を取得する
								   //敵の情報への先頭アドレスが代入される

			//エフェクトを使用していない状態にする処理-------------------------------------

			//エフェクトが生成されてからの時間を計測する
			g_aEffect[nCountEffect].nLife--;

			if (g_aEffect[nCountEffect].nLife < 0) //ショット弾が消滅するまでの時間を超過した場合
			{
				g_aEffect[nCountEffect].bUse = false; //エフェクトを使用していない状態にする
			}
		}
		pVertexEffect += 4; //頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferEffect->Unlock();
}

//エフェクトの描画処理=========================================================
void DrawEffect(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceEffect; //デバイスへのポインタを宣言
	int nCountEffect; //ショット弾の  をカウントするための変数

	VERTEX_2D* pVertexEffect; //頂点情報へのポインタ

	//デバイスの取得(ゲッター)処理
	pDeviceEffect = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceEffect->SetStreamSource(0, g_pVertexBufferEffect, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceEffect->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDeviceEffect->SetTexture(0, g_pTextureEffect);

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferEffect->Lock(0, 0, (void**)&pVertexEffect, 0);

	//アルファブレンディングを加算合成に設定
	pDeviceEffect->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //ブレンド方法
	pDeviceEffect->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //
	pDeviceEffect->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); //

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if (g_aEffect[nCountEffect].bUse == true) //使用されているショット弾のみに描画処理を適用する
		{
			//ポリゴンの描画
			pDeviceEffect->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountEffect * 4, 2);
			//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , nCountEffect * 4…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferEffect->Unlock();

	//アルファブレンディングを加算合成に設定
	pDeviceEffect->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //ブレンド方法
	pDeviceEffect->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //
	pDeviceEffect->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //
}

//エフェクトの設定処理=========================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
//pos…位置 col…頂点カラー fRadius…エフェクトの半径(大きさ) nLife…エフェクトが消滅するまでの時間
{
	//変数を宣言するところ-----------------------------------------------------
	//LPDIRECT3DDEVICE9 pDeviceEffect; //デバイスへのポインタを宣言
	//VERTEX_2D* pVertexEffect; //頂点情報へのポインタ
	int nCountEffect; //エフェクトの  をカウントするための変数

	//デバイスの取得(ゲッター)処理
	//pDeviceEffect = GetDevice();

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	//g_pVertexBufferEffect->Lock(0, 0, (void**)&pVertexEffect, 0);

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if (g_aEffect[nCountEffect].bUse == false) //使用されていないエフェクトのみに更新処理を適用する
		{
			g_aEffect[nCountEffect].pos = pos; //位置
			g_aEffect[nCountEffect].col = col; //頂点カラーの設定(更新)
			g_aEffect[nCountEffect].fRadius = fRadius; //頂点座標の設定(更新)
			g_aEffect[nCountEffect].nLife = nLife; //寿命(エフェクトが消滅するまでの時間)
			g_aEffect[nCountEffect].bUse = true; //使用しているかどうか

			break;
		}
	}
	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	//g_pVertexBufferEffect->Unlock();
}

//エフェクトの終了処理=========================================================
void UninitEffect(void)
{
	//テクスチャの破棄①
	if (g_pTextureEffect != NULL) //g_pTextureEffectにテクスチャが設定されている場合、
								   // テクスチャを破棄する処理
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVertexBufferEffect != NULL)
	{
		g_pVertexBufferEffect->Release();
		g_pVertexBufferEffect = NULL;
	}
}