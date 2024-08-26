#include "R6.7.11-1-fade.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
							// 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferFade = NULL; //頂点バッファへのポインタ
FADE g_fade; //フェードの状態を管理する
MODE g_ModeNext; //次の画面(モード)
D3DXVECTOR3 g_posFade; //ポリゴン(フェード)の位置を管理する変数
D3DXCOLOR g_colorFade; //ポリゴン(フェード)の色を管理する変数

//フェード画面の初期化処理=====================================================
void InitFade(MODE ModeNext)
{
	//変数を宣言するところ-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceFade; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDeviceFade = GetDevice();

	g_fade = FADE_IN; //フェードイン状態にする

	g_ModeNext = ModeNext; //次の画面(モード)を設定する

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); //ポリゴンの色を真っ黒(不透明)にする

	//頂点バッファの生成
	pDeviceFade->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVertexBufferFade,
		NULL);

	VERTEX_2D* pVertexFade; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferFade->Lock(0, 0, (void**)&pVertexFade, 0);

	//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	//頂点座標の設定 ※必ず右回りになるように設定すること!!※
	pVertexFade[0].pos = D3DXVECTOR3(g_posFade.x - FADE_WIDTH / 2, g_posFade.y - FADE_HEIGHT / 2, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};
	pVertexFade[1].pos = D3DXVECTOR3(g_posFade.x + FADE_WIDTH / 2, g_posFade.y - FADE_HEIGHT / 2, 0.0f); //1番目の頂点
	pVertexFade[2].pos = D3DXVECTOR3(g_posFade.x - FADE_WIDTH / 2, g_posFade.y + FADE_HEIGHT / 2, 0.0f); //2番目の頂点
	pVertexFade[3].pos = D3DXVECTOR3(g_posFade.x + FADE_WIDTH / 2, g_posFade.y + FADE_HEIGHT / 2, 0.0f); //3番目の頂点

	//rhwの設定
	pVertexFade[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
	pVertexFade[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
	pVertexFade[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
	pVertexFade[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

	//モードの設定
	SetMode(g_ModeNext);
}

//フェード画面の更新処理=======================================================
void UpdateFade(void)
{
	VERTEX_2D* pVertexFade; //頂点情報へのポインタ

	if (g_fade != FADE_NONE) //
	{
		if (g_fade != FADE_IN) //フェードイン状態
		{
			g_colorFade.a -= 0.1f; //透明度の値を下げていく(ポリゴンを透明にしていく)

			if (g_colorFade.a <= 0.0f) //透明度の値が0.0f以下になった場合
			{
				g_colorFade.a = 0.0f; //透明度の値を0.0fに固定する

				g_fade = FADE_NONE; //フェードの状態を何もしていない状態にする
			}
		}

		else if (g_fade == FADE_OUT) //フェードアウト状態
		{
			g_colorFade.a += 0.1f; //透明度の値を上げていく(ポリゴンを不透明にしていく)

			if (g_colorFade.a >= 1.0f) //透明度の値が1.0fを超過した場合
			{
				g_colorFade.a = 1.0f; //透明度の値を1.0fに固定する

				g_fade = FADE_IN; //フェードイン状態

				//モード設定(次の画面に移行する)
				SetMode(g_ModeNext);
			}
		}
		//頂点カラーの設定
		pVertexFade[0].col = D3DCOLOR_RGBA(0, 0, 0, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
		pVertexFade[1].col = D3DCOLOR_RGBA(0, 0, 0, 255); //1番目の頂点
		pVertexFade[2].col = D3DCOLOR_RGBA(0, 0, 0, 255); //2番目の頂点
		pVertexFade[3].col = D3DCOLOR_RGBA(0, 0, 0, 255); //3番目の頂点
	}
}

//フェード画面の描画処理=======================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDeviceFade; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDeviceFade = GetDevice();

	//頂点バッファをデータストリームに設定
	pDeviceFade->SetStreamSource(0, g_pVertexBufferFade, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDeviceFade->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDeviceFade->SetTexture(0, NULL); //テクスチャを使用しない時は「NULL」とする

	//ポリゴンの描画
	pDeviceFade->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , 0…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)

}

//フェード画面の終了処理=======================================================
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVertexBufferFade != NULL)
	{
		g_pVertexBufferFade->Release();
		g_pVertexBufferFade = NULL;
	}
}

//フェード状態の設定処理(1Fだけ呼び出すようにする)=============================
void SetGameState(MODE ModeNext)
{
	g_fade = FADE_OUT; //フェードアウト状態にする

	g_ModeNext = ModeNext; //次の画面(モード)を設定する

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f); //ポリゴンの色を真っ黒(不透明)にしておく
}

//フェード状態の取得処理=======================================================
FADE GetFade(void)
{
	return g_fade;
}