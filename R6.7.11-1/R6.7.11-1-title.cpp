#include "R6.7.11-1-title.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
#include "R6.7.11-1-input.h" // 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-sound.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferTitle = NULL; //頂点バッファへのポインタ
D3DXVECTOR3 g_posTitle; //タイトルの位置を管理する変数

//タイトル画面の初期化処理
void InitTitle(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceTitle; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDeviceTitle = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDeviceTitle,
		"data\\TEXTURE\\title000.png",
		&g_pTextureTitle);

	//各種数値の初期化
	g_posTitle = D3DXVECTOR3(640.0f, 360.0f, 0.0f); //プレイヤー1の位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};

	//頂点バッファの生成
	pDeviceTitle->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVertexBufferTitle,
		NULL);

	VERTEX_2D* pVertexTitle; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferTitle->Lock(0, 0, (void**)&pVertexTitle, 0);

	//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	//頂点座標の設定 ※必ず右回りになるように設定すること!!※
	pVertexTitle[0].pos = D3DXVECTOR3(g_posTitle.x - TITLE_WIDTH / 2, g_posTitle.y - TITLE_HEIGHT / 2, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
	pVertexTitle[1].pos = D3DXVECTOR3(g_posTitle.x + TITLE_WIDTH / 2, g_posTitle.y - TITLE_HEIGHT / 2, 0.0f); //1番目の頂点
	pVertexTitle[2].pos = D3DXVECTOR3(g_posTitle.x - TITLE_WIDTH / 2, g_posTitle.y + TITLE_HEIGHT / 2, 0.0f); //2番目の頂点
	pVertexTitle[3].pos = D3DXVECTOR3(g_posTitle.x + TITLE_WIDTH / 2, g_posTitle.y + TITLE_HEIGHT / 2, 0.0f); //3番目の頂点

	//rhwの設定
	pVertexTitle[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
	pVertexTitle[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
	pVertexTitle[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
	pVertexTitle[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

	//頂点カラーの設定
	pVertexTitle[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
	pVertexTitle[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
	pVertexTitle[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
	pVertexTitle[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点

	//テクスチャ座標の設定
	pVertexTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
	pVertexTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1番目の頂点
	pVertexTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
	pVertexTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3番目の頂点

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferTitle->Unlock();

	//サウンドを再生する
	PlaySound(SOUND_LABEL_TITLE_BGM); //SOUND_LABEL_BGMに指定した音声ファイルを再生する
	PlaySound(SOUND_LABEL_SE); //SOUND_LABEL_SEに指定した音声ファイルを再生する
}

//タイトル画面の更新処理-----------------------------------------------------------
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true) //決定(ENTERキー)が押された場合
	{
		//モード設定(ゲーム画面に移行する)
		SetMode(MODE_GAME);
	}
}

//タイトル画面の描画処理-----------------------------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDeviceTitle; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDeviceTitle = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceTitle->SetStreamSource(0, g_pVertexBufferTitle, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceTitle->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDeviceTitle->SetTexture(0, g_pTextureTitle);

	//ポリゴンの描画
	pDeviceTitle->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , 0…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
}

//タイトル画面の終了処理-----------------------------------------------------------
void UninitTitle(void)
{
	//サウンドを停止する
	StopSound();

	//テクスチャの破棄①
	if (g_pTextureTitle != NULL) //g_pTextureTitleにテクスチャが設定されている場合、
								 // テクスチャを破棄する処理
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVertexBufferTitle != NULL)
	{
		g_pVertexBufferTitle->Release();
		g_pVertexBufferTitle = NULL;
	}
}