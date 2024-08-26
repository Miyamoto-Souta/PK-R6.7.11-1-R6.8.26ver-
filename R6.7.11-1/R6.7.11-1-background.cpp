#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
							// 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-background.h"

//マクロ定義
#define NUM_BACKGROUND (3) //背景の重ねる数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureBackground[NUM_BACKGROUND] = {}; //テクスチャ([NUM_BACKGROUND])枚分へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferBackground = NULL; //頂点バッファへのポインタ
float g_aPosTextureU[NUM_BACKGROUND]; //テクスチャ座標のU値の開始位置

//背景の初期化処理---------------------------------------------------------
void InitBackground(void)
{
	LPDIRECT3DDEVICE9 pDeviceBackground; //デバイスへのポインタを宣言
	int nCountBackGround; //背景の枚数をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceBackground = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDeviceBackground,
							  "data\\TEXTURE\\bg101.jpg",
							  &g_apTextureBackground[0]);

	//テクスチャの読み込み②
	D3DXCreateTextureFromFile(pDeviceBackground,
							  "data\\TEXTURE\\bg102.jpg",
							  &g_apTextureBackground[1]);

	//テクスチャの読み込み③
	D3DXCreateTextureFromFile(pDeviceBackground,
							  "data\\TEXTURE\\bg103.jpg",
							  &g_apTextureBackground[2]);

	//テクスチャ座標の開始位置(U値)の初期化
	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		g_aPosTextureU[nCountBackGround] = 0.0f;
	}

	//頂点バッファの生成
	pDeviceBackground->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACKGROUND, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数 × [NUM_BACKGROUND]}
										  D3DUSAGE_WRITEONLY,
										  FVF_VERTEX_2D, //頂点フォーマット
										  D3DPOOL_MANAGED,
										  &g_pVertexBufferBackground,
										  NULL);

	VERTEX_2D* pVertexBackground; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferBackground->Lock(0, 0, (void**)&pVertexBackground, 0);

	//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		//頂点座標の設定 ※必ず右回りになるように設定すること!!※
		pVertexBackground[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
		pVertexBackground[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f); //1番目の頂点
		pVertexBackground[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f); //2番目の頂点
		pVertexBackground[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f); //3番目の頂点

		//rhwの設定
		pVertexBackground[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
		pVertexBackground[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
		pVertexBackground[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
		pVertexBackground[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

		//頂点カラーの設定
		pVertexBackground[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
		pVertexBackground[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
		pVertexBackground[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
		pVertexBackground[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点

		//テクスチャ座標の設定
		pVertexBackground[0].tex = D3DXVECTOR2(g_aPosTextureU[nCountBackGround], 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
		pVertexBackground[1].tex = D3DXVECTOR2(g_aPosTextureU[nCountBackGround] + 1.0f, 0.0f); //1番目の頂点
		pVertexBackground[2].tex = D3DXVECTOR2(g_aPosTextureU[nCountBackGround], 1.0f); //2番目の頂点
		pVertexBackground[3].tex = D3DXVECTOR2(g_aPosTextureU[nCountBackGround] + 1.0f, 1.0f); //3番目の頂点

		pVertexBackground += 4; //頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferBackground->Unlock();
}

//背景の更新処理-----------------------------------------------------------
void UpdateBackground(void)
{
	int nCountBackGround; //背景の枚数をカウントするための変数

	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		//テクスチャ座標のU値の開始位置を更新する処理
		ａ

		//テクスチャ座標を更新する処理
		ｂ

	}
}

//背景の描画処理-----------------------------------------------------------
void DrawBackground(void)
{
	LPDIRECT3DDEVICE9 pDeviceBackground; //デバイスへのポインタを宣言
	int nCountBackGround; //背景の枚数をカウントするための変数

	//デバイスの取得(ゲッター)処理
	pDeviceBackground = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceBackground->SetStreamSource(0, g_pVertexBufferBackground, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceBackground->SetFVF(FVF_VERTEX_2D);

	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		//テクスチャの設定
		pDeviceBackground->SetTexture(0, g_apTextureBackground[nCountBackGround]);

		//ポリゴンの描画
		pDeviceBackground->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , 0…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
	}
}

//背景の終了処理-----------------------------------------------------------
void UninitBackground(void)
{
	int nCountBackGround; //背景の枚数をカウントするための変数

	//テクスチャの破棄
	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		if (g_apTextureBackground[nCountBackGround] != NULL) //g_apTextureBackground[nCountBackGround]に
															 // テクスチャが設定されている場合、テクスチャを破棄する処理
		{
			g_apTextureBackground[nCountBackGround]->Release();
			g_apTextureBackground[nCountBackGround] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVertexBufferBackground != NULL)
	{
		g_pVertexBufferBackground->Release();
		g_pVertexBufferBackground = NULL;
	}
}