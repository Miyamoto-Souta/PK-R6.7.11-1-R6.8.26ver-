#include "R6.7.11-1-result.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
#include "R6.7.11-1-input.h"  // 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-sound.h"


//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferResult = NULL; //頂点バッファへのポインタ
D3DXVECTOR3 g_posResult; //リザルトの位置を管理する変数

//リザルト画面の初期化処理
void InitResult(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceResult; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDeviceResult = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDeviceResult,
		"data\\TEXTURE\\result000.png",
		&g_pTextureResult);

	//各種数値の初期化
	g_posResult = D3DXVECTOR3(640.0f, 360.0f, 0.0f); //リザルトの位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};

	//頂点バッファの生成
	pDeviceResult->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVertexBufferResult,
		NULL);

	VERTEX_2D* pVertexResult; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferResult->Lock(0, 0, (void**)&pVertexResult, 0);

	//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	//頂点座標の設定 ※必ず右回りになるように設定すること!!※
	pVertexResult[0].pos = D3DXVECTOR3(g_posResult.x - RESULT_WIDTH / 2, g_posResult.y - RESULT_HEIGHT / 2, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
	pVertexResult[1].pos = D3DXVECTOR3(g_posResult.x + RESULT_WIDTH / 2, g_posResult.y - RESULT_HEIGHT / 2, 0.0f); //1番目の頂点
	pVertexResult[2].pos = D3DXVECTOR3(g_posResult.x - RESULT_WIDTH / 2, g_posResult.y + RESULT_HEIGHT / 2, 0.0f); //2番目の頂点
	pVertexResult[3].pos = D3DXVECTOR3(g_posResult.x + RESULT_WIDTH / 2, g_posResult.y + RESULT_HEIGHT / 2, 0.0f); //3番目の頂点

	//rhwの設定
	pVertexResult[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
	pVertexResult[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
	pVertexResult[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
	pVertexResult[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

	//頂点カラーの設定
	pVertexResult[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
	pVertexResult[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
	pVertexResult[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
	pVertexResult[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点

	//テクスチャ座標の設定
	pVertexResult[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
	pVertexResult[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1番目の頂点
	pVertexResult[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
	pVertexResult[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3番目の頂点

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferResult->Unlock();
}

//リザルト画面の更新処理-----------------------------------------------------------
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true) //決定(ENTERキー)が押された場合
	{
		//モード設定(ゲーム画面に移行する)
		SetMode(MODE_GAME);
	}
}

//リザルト画面の描画処理-----------------------------------------------------------
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDeviceResult; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDeviceResult = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceResult->SetStreamSource(0, g_pVertexBufferResult, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceResult->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDeviceResult->SetTexture(0, g_pTextureResult);

	//ポリゴンの描画
	pDeviceResult->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , 0…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
}

//リザルト画面の終了処理-----------------------------------------------------------
void UninitResult(void)
{
	//テクスチャの破棄①
	if (g_pTextureResult != NULL) //g_pTextureTitleにテクスチャが設定されている場合、
								  // テクスチャを破棄する処理
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVertexBufferResult != NULL)
	{
		g_pVertexBufferResult->Release();
		g_pVertexBufferResult = NULL;
	}
}