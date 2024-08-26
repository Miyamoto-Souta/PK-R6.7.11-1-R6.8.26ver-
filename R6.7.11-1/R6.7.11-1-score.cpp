#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
#include "R6.7.11-1-score.h" //自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferScore = NULL; //頂点バッファへのポインタ
D3DXVECTOR3 g_posScore; //スコアの位置を管理する変数
int g_nScore; //スコアの値を管理する変数

//スコアの初期化処理===========================================================
void InitScore(void)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceScore; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDeviceScore = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDeviceScore,
		"data\\TEXTURE\\Score000.png",
		&g_pTextureScore);

	//各種数値の初期化
	g_posScore = D3DXVECTOR3(640.0f, 360.0f, 0.0f); //スコアの位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};

	g_nScore = 0; //スコアの値を初期化する

	//頂点バッファの生成
	pDeviceScore->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVertexBufferScore,
		NULL);

	VERTEX_2D* pVertexScore; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferScore->Lock(0, 0, (void**)&pVertexScore, 0);

	//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	//頂点座標の設定 ※必ず右回りになるように設定すること!!※
	pVertexScore[0].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH / 2, g_posScore.y - SCORE_HEIGHT / 2, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
	pVertexScore[1].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH / 2, g_posScore.y - SCORE_HEIGHT / 2, 0.0f); //1番目の頂点
	pVertexScore[2].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH / 2, g_posScore.y + SCORE_HEIGHT / 2, 0.0f); //2番目の頂点
	pVertexScore[3].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH / 2, g_posScore.y + SCORE_HEIGHT / 2, 0.0f); //3番目の頂点

	//rhwの設定
	pVertexScore[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
	pVertexScore[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
	pVertexScore[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
	pVertexScore[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

	//頂点カラーの設定
	pVertexScore[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
	pVertexScore[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
	pVertexScore[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
	pVertexScore[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点

	//テクスチャ座標の設定
	pVertexScore[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
	pVertexScore[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1番目の頂点
	pVertexScore[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
	pVertexScore[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3番目の頂点

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferScore->Unlock();
}

//スコアの更新処理=============================================================
void UpdateScore(void)
{
	//現在のスコアまでカウントアップさせる等の動きを付けたい場合はここに処理を追加する
}

//スコアの描画処理=============================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDeviceScore; //デバイスへのポインタを宣言
	int nCount; //回数を測る

	VERTEX_2D* pVertexScore; //頂点情報へのポインタ

	//デバイスの取得(ゲッター)処理
	pDeviceScore = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceScore->SetStreamSource(0, g_pVertexBufferScore, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceScore->SetFVF(FVF_VERTEX_2D);
	
	//テクスチャの設定(必要な桁数分描画させるようにすること)
	pDeviceScore->SetTexture(0, g_pTextureScore);
	
	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferScore->Lock(0, 0, (void**)&pVertexScore, 0);

	for (nCount = 0; nCount < 8; nCount++) //8…最大桁数
	{
		//ポリゴンの描画
		pDeviceScore->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , nCount * 4…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)

		//頂点座標の設定 ※必ず右回りになるように設定すること!!※
		pVertexScore[0].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH / 2, g_posScore.y - SCORE_HEIGHT / 2, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
		pVertexScore[1].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH / 2, g_posScore.y - SCORE_HEIGHT / 2, 0.0f); //1番目の頂点
		pVertexScore[2].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH / 2, g_posScore.y + SCORE_HEIGHT / 2, 0.0f); //2番目の頂点
		pVertexScore[3].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH / 2, g_posScore.y + SCORE_HEIGHT / 2, 0.0f); //3番目の頂点

		//rhwの設定
		pVertexScore[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
		pVertexScore[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
		pVertexScore[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
		pVertexScore[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

		//頂点カラーの設定
		pVertexScore[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
		pVertexScore[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
		pVertexScore[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
		pVertexScore[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点

		//テクスチャ座標の設定
		pVertexScore[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
		pVertexScore[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1番目の頂点
		pVertexScore[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
		pVertexScore[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3番目の頂点
	}

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferScore->Unlock();
}

//スコアの終了処理=============================================================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL) //g_pTextureScoreにテクスチャが設定されている場合、
								 // テクスチャを破棄する処理
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVertexBufferScore != NULL)
	{
		g_pVertexBufferScore->Release();
		g_pVertexBufferScore = NULL;
	}
}

//スコアの設定処理=============================================================
void SetScore(int nScore)
{
	//変数を宣言するところ-----------------------------------------------------
	int aPosTextureU[8]; //各桁の数字を格納する(この場合は最大8桁)

	LPDIRECT3DDEVICE9 pDeviceScore; //デバイスへのポインタを宣言
	int nCountScore; //回数を測る

	VERTEX_2D* pVertexScore; //頂点情報へのポインタ

	//デバイスの取得(ゲッター)処理
	pDeviceScore = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceScore->SetStreamSource(0, g_pVertexBufferScore, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceScore->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(必要な桁数分描画させるようにすること)
	pDeviceScore->SetTexture(0, g_pTextureScore);

	//??の処理---------------------------------------------------------------------
	g_nScore = nScore; //

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferScore->Lock(0, 0, (void**)&pVertexScore, 0);

	aPosTextureU[0] = g_nScore % 100000000 / 10000000; //8桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[1] = g_nScore % 10000000 / 1000000; //7桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[2] = g_nScore % 1000000 / 100000; //6桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[3] = g_nScore % 100000 / 10000; //5桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[4] = g_nScore % 10000 / 1000; //4桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[5] = g_nScore % 1000 / 100; //3桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[6] = g_nScore % 100 / 10; //2桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[7] = g_nScore % 10 / 1; //1桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;

	//テクスチャ座標の設定
	for (nCountScore = 0; nCountScore < 8; nCountScore++) //8…最大桁数
	{
		pVertexScore[0].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
		pVertexScore[1].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f + 0.1f, 0.0f); //1番目の頂点
		pVertexScore[2].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f, 1.0f); //2番目の頂点
		pVertexScore[3].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f + 0.1f, 1.0f); //3番目の頂点

		pVertexScore += 4; //
	}

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferScore->Unlock();
}

//スコアの加算処理=============================================================
void AddScore(int nValue)
{
	//変数を宣言するところ-----------------------------------------------------
	int aPosTextureU[8]; //各桁の数字を格納する(この場合は最大8桁)

	LPDIRECT3DDEVICE9 pDeviceScore; //デバイスへのポインタを宣言
	int nCountScore; //回数を測る

	VERTEX_2D* pVertexScore; //頂点情報へのポインタ

	//デバイスの取得(ゲッター)処理
	pDeviceScore = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceScore->SetStreamSource(0, g_pVertexBufferScore, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceScore->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定(必要な桁数分描画させるようにすること)
	pDeviceScore->SetTexture(0, g_pTextureScore);

	//処理---------------------------------------------------------------------
	g_nScore += nValue; //現在のスコアの値に加算する値を足す

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferScore->Lock(0, 0, (void**)&pVertexScore, 0);

	aPosTextureU[0] = g_nScore % 100000000 / 10000000; //8桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[1] = g_nScore % 10000000 / 1000000; //7桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[2] = g_nScore % 1000000 / 100000; //6桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[3] = g_nScore % 100000 / 10000; //5桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[4] = g_nScore % 10000 / 1000; //4桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[5] = g_nScore % 1000 / 100; //3桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[6] = g_nScore % 100 / 10; //2桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;
	aPosTextureU[7] = g_nScore % 10 / 1; //1桁目 スコア % 現在求める位の1つ上の位 / 現在求める位;

	//テクスチャ座標の設定
	for (nCountScore = 0; nCountScore < 8; nCountScore++) //8…最大桁数
	{
		pVertexScore[0].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
		pVertexScore[1].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f + 0.1f, 0.0f); //1番目の頂点
		pVertexScore[2].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f, 1.0f); //2番目の頂点
		pVertexScore[3].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f + 0.1f, 1.0f); //3番目の頂点

		pVertexScore += 4; //頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferScore->Unlock();
}