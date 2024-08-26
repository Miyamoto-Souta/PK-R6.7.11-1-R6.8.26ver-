#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
							// 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-player2.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer2 = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferPlayer2 = NULL; //頂点バッファへのポインタ
D3DXVECTOR3 g_posPlayer2; //プレイヤー1の位置を管理する変数
int g_nCounterAnimPlayer2; //アニメーションカウンター
int g_nPatternAnimPlayer2; //アニメーションパターンの番号

//プレイヤー2の初期化処理---------------------------------------------------------
void InitPlayer2(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDevicePlayer2; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDevicePlayer2 = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDevicePlayer2,
		"data\\TEXTURE\\runningman200.png",
		&g_pTexturePlayer2);

	//各種数値の初期化
	g_posPlayer2 = D3DXVECTOR3(1100.0f, 200.0f, 0.0f); //プレイヤー2の位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};
	g_nCounterAnimPlayer2 = 0; //アニメーションカウンターを初期化する
	g_nPatternAnimPlayer2 = 0; //アニメーションパターンの番号を初期化する

	//頂点バッファの生成
	pDevicePlayer2->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVertexBufferPlayer2,
		NULL);

	VERTEX_2D* pVertexPlayer2; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferPlayer2->Lock(0, 0, (void**)&pVertexPlayer2, 0);

	//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	//頂点座標の設定 ※必ず右回りになるように設定すること!!※
	pVertexPlayer2[0].pos = D3DXVECTOR3(g_posPlayer2.x - 150.0f, g_posPlayer2.y - 200.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
	pVertexPlayer2[1].pos = D3DXVECTOR3(g_posPlayer2.x + 150.0f, g_posPlayer2.y - 200.0f, 0.0f); //1番目の頂点
	pVertexPlayer2[2].pos = D3DXVECTOR3(g_posPlayer2.x - 150.0f, g_posPlayer2.y + 200.0f, 0.0f); //2番目の頂点
	pVertexPlayer2[3].pos = D3DXVECTOR3(g_posPlayer2.x + 150.0f, g_posPlayer2.y + 200.0f, 0.0f); //3番目の頂点

	//rhwの設定
	pVertexPlayer2[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
	pVertexPlayer2[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
	pVertexPlayer2[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
	pVertexPlayer2[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

	//頂点カラーの設定
	pVertexPlayer2[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
	pVertexPlayer2[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
	pVertexPlayer2[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
	pVertexPlayer2[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点

	//テクスチャ座標の設定
	//pVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
	//pVertex[1].tex = D3DXVECTOR2(0.125f, 0.0f); //1番目の頂点
	//pVertex[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
	//pVertex[3].tex = D3DXVECTOR2(0.125f, 1.0f); //3番目の頂点

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferPlayer2->Unlock();
}

//プレイヤー2の更新処理========================================================
void UpdatePlayer2(void)
{
	//変数を宣言するところ
	VERTEX_2D* pVertexPlayer2; //頂点情報へのポインタ

	g_nCounterAnimPlayer2++; //アニメーションカウンターを加算させる処理

	//アニメーション関連の処理-------------------------------------------------
	if ((g_nCounterAnimPlayer2 % 60) == 0) //一定時間(60F)経過した場合
	{
		g_nPatternAnimPlayer2++; //アニメーションパターンの番号を更新(加算)する

		//アニメーションパターンの番号を更新(加算)する
		g_nPatternAnimPlayer2 = (g_nPatternAnimPlayer2) % 10; //10…総パターン数

		if(g_nPatternAnimPlayer2 > 11) //アニメーションパターンの総数を超えた場合
		{ 
			g_nPatternAnimPlayer2 = 0; //アニメーションパターンの番号を初期値(0)に戻す
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
		g_pVertexBufferPlayer2->Lock(0, 0, (void**)&pVertexPlayer2, 0);

		//テクスチャ座標(UV)を更新する処理

		//テクスチャ座標の設定
		pVertexPlayer2[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, g_nPatternAnimPlayer2 / 5 * 0.5f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
		pVertexPlayer2[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, g_nPatternAnimPlayer2 / 5 * 0.5f); //1番目の頂点
		pVertexPlayer2[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, g_nPatternAnimPlayer2 / 5 * 0.5 + 0.5f); //2番目の頂点
		pVertexPlayer2[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, g_nPatternAnimPlayer2 / 5 * 0.5 + 0.5f); //3番目の頂点
		

		//else if (6 <= g_nPatternAnimPlayer2 <= 10)
		//{
			//pVertexPlayer2[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 0.5f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
			//pVertexPlayer2[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 0.5f); //1番目の頂点
			//pVertexPlayer2[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 1.0f); //2番目の頂点
			//pVertexPlayer2[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 1.0f); //3番目の頂点
		//}

		//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
		g_pVertexBufferPlayer2->Unlock();
	}
}

//プレイヤー2の描画処理-----------------------------------------------------------
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevicePlayer2; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDevicePlayer2 = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevicePlayer2->SetStreamSource(0, g_pVertexBufferPlayer2, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDevicePlayer2->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevicePlayer2->SetTexture(0, g_pTexturePlayer2);

	//ポリゴンの描画
	pDevicePlayer2->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , 0…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
}

//プレイヤー2の終了処理-----------------------------------------------------------
void UninitPlayer2(void)
{
	//テクスチャの破棄①
	if (g_pTexturePlayer2 != NULL) //g_pTexturePlayer1にテクスチャが設定されている場合、
								   // テクスチャを破棄する処理
	{
		g_pTexturePlayer2->Release();
		g_pTexturePlayer2 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVertexBufferPlayer2 != NULL)
	{
		g_pVertexBufferPlayer2->Release();
		g_pVertexBufferPlayer2 = NULL;
	}
}