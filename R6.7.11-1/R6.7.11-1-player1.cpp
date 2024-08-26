#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
//自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferPlayer1 = NULL; //頂点バッファへのポインタ
Player1 g_Player1; //プレイヤー1の情報を管理する変数
int g_nCounterAnimPlayer1; //アニメーションカウンター
int g_nPatternAnimPlayer1; //アニメーションパターンの番号
//D3DXVECTOR3 g_posPlayer1; //プレイヤー1の位置を管理する変数
//D3DXVECTOR3 g_movePlayer1; //プレイヤー1の移動量を管理する変数
//D3DXVECTOR3 g_moveBulletPlayer1; //プレイヤー1のショットの移動量を管理する変数
//D3DXVECTOR3 g_rotPlayer1; //プレイヤー1の向きを管理する変数
//float g_fLengthPlayer1; //プレイヤー1の対角線の長さ(拡大縮小用)を管理する変数
//float g_fAnglePlayer1; //プレイヤー1の対角線の角度(回転用)を管理する変数
int g_nMoveDirection; //移動方向を判別するための変数を宣言

//プレイヤー1を取得する処理============================================================
Player1* GetPlayer1(void)
{
	return &g_Player1; //プレイヤー1の情報の先頭アドレスを返す
}

//プレイヤー1の初期化処理======================================================
void InitPlayer1(void)
{
	LPDIRECT3DDEVICE9 pDevicePlayer1; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDevicePlayer1 = GetDevice();

	//テクスチャの読み込み①
	D3DXCreateTextureFromFile(pDevicePlayer1,
		"data\\TEXTURE\\runningman100.png",
		&g_pTexturePlayer1);

	//各種数値の初期化
	g_nCounterAnimPlayer1 = 0; //アニメーションカウンターを初期化する
	g_nPatternAnimPlayer1 = 0; //アニメーションパターンの番号を初期化する
	g_Player1.pos = D3DXVECTOR3(150.0f, 450.0f, 0.0f); //プレイヤー1の位置を初期化する {D3DXVECTOR3(X座標, Y座標, Z座標)};
	g_Player1.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //プレイヤー1の移動量を初期化する {D3DXVECTOR3(X方向, Y方向, Z方向)};
	g_Player1.movebullet = D3DXVECTOR3(0.0f, 4.0f, 0.0f); //プレイヤー1のショットの移動量を初期化する {D3DXVECTOR3(X方向, Y方向, Z方向)};
	g_Player1.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //プレイヤー1の向きを初期化する {D3DXVECTOR3(X方向, Y方向, Z方向)};

	//対角線の長さを算出する処理
	g_Player1.Length = sqrtf(PLAYER1_WIDTH * PLAYER1_WIDTH + PLAYER1_HEIGHT * PLAYER1_HEIGHT) / 2.0f; //sqrtf(プレイヤー1の幅 * プレイヤー1の幅 + プレイヤー1の高さ * プレイヤー1の高さ)

	//対角線の角度を算出する処理
	g_Player1.Angle = atan2f(PLAYER1_WIDTH, PLAYER1_HEIGHT); //atan2f(プレイヤー1の幅 ,プレイヤー1の高さ)

	//頂点バッファの生成
	pDevicePlayer1->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //確保するバッファのサイズ{sizeof(VERTEX_2D) × 必要な頂点数}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVertexBufferPlayer1,
		NULL);

	VERTEX_2D* pVertexPlayer1; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferPlayer1->Lock(0, 0, (void**)&pVertexPlayer1, 0);

	//pVertexの設定ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	//頂点座標の設定 ※必ず右回りになるように設定すること!!※
	pVertexPlayer1[0].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z - (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0番目の頂点のX座標 g_posPlayer1.x + sinf(向き + 角度(＝始点 + 対角線の角度)) * 長さ
	pVertexPlayer1[0].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z - (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0番目の頂点のY座標 g_posPlayer1.y + cosf(向き + 角度) * 長さ
	pVertexPlayer1[0].pos.z = 0.0f; //0番目の頂点のZ座標
	pVertexPlayer1[1].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0番目の頂点のX座標 g_posPlayer1.x + sinf(向き + 角度(＝始点 + 対角線の角度)) * 長さ
	pVertexPlayer1[1].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0番目の頂点のY座標 g_posPlayer1.y + cosf(向き + 角度) * 長さ
	pVertexPlayer1[1].pos.z = 0.0f; //0番目の頂点のZ座標
	pVertexPlayer1[2].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (0.0f - g_Player1.Angle)) * g_Player1.Length; //2番目の頂点のX座標 g_posPlayer1.x + sinf(向き + 角度(＝始点 + 対角線の角度)) * 長さ
	pVertexPlayer1[2].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (0.0f - g_Player1.Angle)) * g_Player1.Length; //2番目の頂点のY座標 g_posPlayer1.y + cosf(向き + 角度) * 長さ
	pVertexPlayer1[2].pos.z = 0.0f; //2番目の頂点のZ座標
	pVertexPlayer1[3].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (0.0f + g_Player1.Angle)) * g_Player1.Length; //3番目の頂点のX座標 g_posPlayer1.x + sinf(向き + 角度(＝始点 + 対角線の角度)) * 長さ
	pVertexPlayer1[3].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (0.0f + g_Player1.Angle)) * g_Player1.Length; //3番目の頂点のY座標 g_posPlayer1.y + cosf(向き + 角度) * 長さ
	pVertexPlayer1[3].pos.z = 0.0f; //3番目の頂点のZ座標
	//回転,拡大縮小を使わない場合 → pVertexPlayer1[0].pos = D3DXVECTOR3(g_Player1.pos.x - 75.0f, g_Player1.pos.y - 100.0f, 0.0f); //0番目の頂点{D3DXVECTOR3(X座標, Y座標, Z座標)};

	//rhwの設定
	pVertexPlayer1[0].rhw = 1.0f; //0番目の頂点(値は1.0fで固定)
	pVertexPlayer1[1].rhw = 1.0f; //1番目の頂点(値は1.0fで固定)
	pVertexPlayer1[2].rhw = 1.0f; //2番目の頂点(値は1.0fで固定)
	pVertexPlayer1[3].rhw = 1.0f; //3番目の頂点(値は1.0fで固定)

	//頂点カラーの設定
	pVertexPlayer1[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
	pVertexPlayer1[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
	pVertexPlayer1[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
	pVertexPlayer1[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点

	//テクスチャ座標の設定
	//pVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
	//pVertex[1].tex = D3DXVECTOR2(0.125f, 0.0f); //1番目の頂点
	//pVertex[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2番目の頂点
	//pVertex[3].tex = D3DXVECTOR2(0.125f, 1.0f); //3番目の頂点

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferPlayer1->Unlock();
}

//プレイヤー1の更新処理========================================================
void UpdatePlayer1(void)
{
	//変数を宣言するところ-----------------------------------------------------
	VERTEX_2D* pVertexPlayer1; //頂点情報へのポインタ

	g_nCounterAnimPlayer1++; //アニメーションカウンターを加算させる処理

	//移動関連の処理-----------------------------------------------------------

	//上…1 左方向…2 右方向…3 下…4 停止…5

	//g_movePlayer1 = D3DXVECTOR3(1.0f, 1.0f, 0.0f); //プレイヤー1の移動量を設定する {D3DXVECTOR3(X方向, Y方向, Z方向)};

	//プレイヤー1のY座標を－(上)方向に移動する
	if (GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_NUMPAD8) == true) //Wキー,↑キー,NUMパッドの8キーが押された場合
	{
		//Aキー,←キー,NUMパッドの4キーも同時に押されている場合
		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_NUMPAD4) == true)
		{ 
			g_Player1.move.x = sinf(-D3DX_PI * 0.75f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.75f) * 1.0f; //プレイヤー1のX,Y座標を－(左上)方向に移動する
			g_nMoveDirection = 2;
		}

		//Dキー,→キー,NUMパッドの6キーも同時に押されている場合
		else if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_NUMPAD6) == true)
		{
			g_Player1.move.x = sinf(D3DX_PI * 0.75f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.75f) * 1.0f; //プレイヤー1のX座標を＋,Y座標を－(右上)方向に移動する
			g_nMoveDirection = 3;
		}

		//Sキー,↓キー,NUMパッドの2キーも同時に押されている場合
		else if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_NUMPAD2) == true)
		{
			g_Player1.move.x = 0.0f, g_Player1.move.y = 0.0f; //その場に留まる
			g_nMoveDirection = 5;
		}

		//それ以外(Wキー,↑キー,NUMパッドの8キーのみが押されている場合)
		else
		{
			g_Player1.move.y = cosf(D3DX_PI * 1.0) * 1.0f;
			g_nMoveDirection = 1;
		}

		//キーの種類を16個全て入れること!!
	}

	//プレイヤー1のX座標を－(左)方向に移動する
	else if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_NUMPAD4) == true) //Aキー,←キー,NUMパッドの4キーが押された場合
	{
		//Sキー,↓キー,NUMパッドの2キーも同時に押されている場合
		if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_NUMPAD2) == true)
		{
			g_Player1.move.x = sinf(-D3DX_PI * 0.25f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.25f) * 1.0f; //プレイヤー1のX座標を－,Y座標を＋(左下)方向に移動する
			g_nMoveDirection = 2;
		}

		//Dキー,→キー,NUMパッドの6キーも同時に押されている場合
		else if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_NUMPAD6) == true)
		{
			g_Player1.move.x = 0.0f, g_Player1.move.y = 0.0f; //その場に留まる
			g_nMoveDirection = 5;
		}

		//それ以外(Aキー,←キー,NUMパッドの4キーのみが押されている場合)
		else
		{
			g_Player1.move.x = sinf(-D3DX_PI * 0.50) * 1.0f;
			g_nMoveDirection = 2;
		}
	}

	//プレイヤー1のX座標を＋(右)方向に移動する
	else if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_NUMPAD6) == true) //Dキー,→キー,NUMパッドの6キーが押された場合
	{
		//Sキー,↓キー,NUMパッドの2キーも同時に押されている場合
		if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_NUMPAD2) == true)
		{
			g_Player1.move.x = sinf(D3DX_PI * 0.25f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.25f) * 1.0f; //プレイヤー1のX,Y座標を＋(右下)方向に移動する
			g_nMoveDirection = 3;
		}

		//それ以外(Dキー,→キー,NUMパッドの6キーのみが押されている場合)
		else
		{
			g_Player1.move.x = sinf(D3DX_PI * 0.50f) * 1.0f;
			g_nMoveDirection = 3;
		}
	}
	
	//プレイヤー1のY座標を＋(下)方向に移動する
	else if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_NUMPAD2) == true) //Sキー,↓キー,NUMパッドの2キーが押された場合
	{
		g_Player1.move.y = cosf(D3DX_PI * 0.0) * 1.0f;
		g_nMoveDirection = 4;
	}

	//プレイヤー1のX,Y座標を－(左上)方向に移動する
	else if (GetKeyboardPress(DIK_NUMPAD7) == true) //NUMパッドの7キーが押された場合
	{
		g_Player1.move.x = sinf(-D3DX_PI * 0.75f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.75f) * 1.0f;
		g_nMoveDirection = 2;
	}

	//プレイヤー1のX座標を＋,Y座標を－(右上)方向に移動する
	else if (GetKeyboardPress(DIK_NUMPAD9) == true) //NUMパッドの9キーが押された場合
	{
		g_Player1.move.x = sinf(D3DX_PI * 0.75f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.75f) * 1.0f;
		g_nMoveDirection = 3;
	}

	//プレイヤー1のX座標を－,Y座標を＋(左下)方向に移動する
	else if (GetKeyboardPress(DIK_NUMPAD1) == true) //NUMパッドの1キーが押された場合
	{
		g_Player1.move.x = sinf(-D3DX_PI * 0.25f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.25f) * 1.0f;
		g_nMoveDirection = 2;
	}

	//プレイヤー1のX,Y座標を＋(右下)方向に移動する
	else if (GetKeyboardPress(DIK_NUMPAD3) == true) //NUMパッドの3キーが押された場合
	{
		g_Player1.move.x = sinf(D3DX_PI * 0.25f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.25f) * 1.0f;
		g_nMoveDirection = 3;
	}

	//移動量がゼロの(その場に留まっている)場合
	else
	{
		g_nMoveDirection = 5;
	}

	//画面端の処理ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・

	//プレイヤーが画面の左端に当たった場合
	if (g_Player1.pos.x <= 80)
	{
		g_Player1.move.x *= 0.0f; //これ以上左方向に移動できなくなる
	}

	//プレイヤーが画面の上端に当たった場合
	if (g_Player1.pos.y <= 80)
	{
		g_Player1.move.y *= 0.0f; //これ以上上方向に移動できなくなる
	}
	//プレイヤーが画面の右端に当たった場合
	if (g_Player1.pos.x >= SCREEN_WIDTH - 80)
	{
		g_Player1.move.x *= 0.0f; //これ以上右方向に移動できなくなる
	}
	//プレイヤーが画面の下端に当たった場合
	if (g_Player1.pos.y >= SCREEN_HEIGHT - 80)
	{
		g_Player1.move.y *= 0.0f; //これ以上下方向に移動できなくなる
	}

	//回転,拡大縮小関連の処理--------------------------------------------------
	
	//プレイヤー1を左回り方向に回転する
	if (GetKeyboardPress(DIK_Q) == true) //Qキーが押された場合
	{
		//Eキーも同時に押されている場合
		if (GetKeyboardPress(DIK_E) == true)
		{
			g_Player1.rot.z += 0.0f;
		}

		//それ以外(Qキーのみが押されている場合)
		else
		{
			g_Player1.rot.z += 0.01f;
		}
	}

	//プレイヤー1を右回り方向に回転する
	else if (GetKeyboardPress(DIK_E) == true) //Eキーのみが押されている場合
	{
		g_Player1.rot.z -= 0.01f;
	}

	//プレイヤー1を拡大する
	if (GetKeyboardPress(DIK_R) == true) //Rキーが押された場合
	{
		//Xキーも同時に押されている場合
		if (GetKeyboardPress(DIK_F) == true)
		{
			g_Player1.Length += 0.0f;
		}

		//それ以外(Zキーのみが押されている場合)
		else
		{
			g_Player1.Length += 0.3f;
		}
	}

	//プレイヤー1を縮小する
	else if (GetKeyboardPress(DIK_F) == true) //Fキーのみが押されている場合
	{
		g_Player1.Length -= 0.3f;
	}

	//プレイヤー1の位置,回転,拡大をリセットする
	else if (GetKeyboardPress(DIK_T) == true) //Tキーのみが押されている場合
	{
		InitPlayer1();
	}

	//ショット関連の処理-------------------------------------------------------

	//ショットを撃つ
	else if (GetKeyboardRepeat(DIK_Z) == true) //Zキーのみが押されている場合
	{
		SetBullet(g_Player1.pos, g_Player1.move, MAX_LIFE, BULLETTYPE_PLAYER1); //SetBullet(位置, 移動量, 弾が消滅するまでの時間 ,弾の種類);
	}

	//慣性の処理ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー
	if (GetKeyboardPress(DIK_C) == true) //Cキーが押された場合
	{ //移動量を更新(増加)させる
		g_Player1.move.x += 0.1f;
		g_Player1.move.y += -0.02f;
	}

	//プレイヤー1の位置を更新する処理 ※ここは消さないこと!!※
	g_Player1.pos.x += g_Player1.move.x; //プレイヤー1の現在位置のX座標にX方向の移動量を加算させる
	g_Player1.pos.y += g_Player1.move.y; //プレイヤー1の現在位置のY座標にY方向の移動量を加算させる

	//移動量を更新(減速)させる
	g_Player1.move.x += (0.0f - g_Player1.move.x) * 0.05f; //X方向の移動量 += (目的の(ここまで減速させたい)値 - 現在の値) * 減衰係数
	g_Player1.move.y += (0.0f - g_Player1.move.y) * 0.05f; //Y方向の移動量 += (目的の(ここまで減速させたい)値 - 現在の値) * 減衰係数

	//頂点座標の更新ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー・ー

	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferPlayer1->Lock(0, 0, (void**)&pVertexPlayer1, 0);

	//頂点座標の設定
	pVertexPlayer1[0].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z - (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0番目の頂点のX座標 g_Player1.pos.x + sinf(向き + 角度(＝始点 + 対角線の角度)) * 長さ
	pVertexPlayer1[0].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z - (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0番目の頂点のY座標 g_Player1.pos.y + cosf(向き + 角度) * 長さ
	pVertexPlayer1[0].pos.z = 0.0f; //0番目の頂点のZ座標
	pVertexPlayer1[1].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0番目の頂点のX座標 g_Player1.pos.x + sinf(向き + 角度(＝始点 + 対角線の角度)) * 長さ
	pVertexPlayer1[1].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0番目の頂点のY座標 g_Player1.pos.y + cosf(向き + 角度) * 長さ
	pVertexPlayer1[1].pos.z = 0.0f; //0番目の頂点のZ座標
	pVertexPlayer1[2].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (0.0f - g_Player1.Angle)) * g_Player1.Length; //2番目の頂点のX座標 g_Player1.pos.x + sinf(向き + 角度(＝始点 + 対角線の角度)) * 長さ
	pVertexPlayer1[2].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (0.0f - g_Player1.Angle)) * g_Player1.Length; //2番目の頂点のY座標 g_Player1.pos.y + cosf(向き + 角度) * 長さ
	pVertexPlayer1[2].pos.z = 0.0f; //2番目の頂点のZ座標
	pVertexPlayer1[3].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (0.0f + g_Player1.Angle)) * g_Player1.Length; //3番目の頂点のX座標 g_Player1.pos.x + sinf(向き + 角度(＝始点 + 対角線の角度)) * 長さ
	pVertexPlayer1[3].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (0.0f + g_Player1.Angle)) * g_Player1.Length; //3番目の頂点のY座標 g_Player1.pos.y + cosf(向き + 角度) * 長さ
	pVertexPlayer1[3].pos.z = 0.0f; //3番目の頂点のZ座標

	//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
	g_pVertexBufferPlayer1->Unlock();

	//アニメーション関連の処理-------------------------------------------------
	
	//頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
	g_pVertexBufferPlayer1->Lock(0, 0, (void**)&pVertexPlayer1, 0);

	if ((g_nCounterAnimPlayer1 % 10) == 0) //一定時間(12F)経過した場合
	{
		g_nPatternAnimPlayer1++; //アニメーションパターンの番号を更新(加算)する

		//移動量がゼロの(その場に留まっている)場合
		if (g_Player1.move.x >= -0.07f && g_Player1.move.x <= 0.07f && g_Player1.move.y >= -0.07f && g_Player1.move.y <= 0.07f)
		{
			g_nPatternAnimPlayer1--; //アニメーションパターンの番号を減算する(＝更新を止めさせる)
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

			//アニメーションパターンの番号を更新(加算)する
			g_nPatternAnimPlayer1 = (g_nPatternAnimPlayer1) % 10; //10…総パターン数

			if (g_nPatternAnimPlayer1 > 11) //アニメーションパターンの総数を超えた場合
			{
				g_nPatternAnimPlayer1 = 0; //アニメーションパターンの番号を初期値(0)に戻す
			}
		}

		//テクスチャ座標(UV)を更新する処理

		//テクスチャ座標の設定
		pVertexPlayer1[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 / 5 * 0.5f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
		pVertexPlayer1[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 / 5 * 0.5f); //1番目の頂点
		pVertexPlayer1[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 / 5 * 0.5f + 0.5f); //2番目の頂点
		pVertexPlayer1[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 / 5 * 0.5f + 0.5f); //3番目の頂点


		//else if (6 <= g_nPatternAnimPlayer2 <= 10)
		//{
			//pVertexPlayer2[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 0.5f); //0番目の頂点{D3DXVECTOR2(U座標, V座標)};
			//pVertexPlayer2[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 0.5f); //1番目の頂点
			//pVertexPlayer2[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 1.0f); //2番目の頂点
			//pVertexPlayer2[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 1.0f); //3番目の頂点
		//}

		//頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
		g_pVertexBufferPlayer1->Unlock();
	}

	//状態関連の処理-----------------------------------------------------------
	switch (g_Player1.state)
	{
	case PLAYER1STATE_NORMAL: //プレイヤー1が通常状態である場合
	
		break;
	

	case PLAYER1STATE_DAMAGE: //プレイヤー1がダメージ状態である場合
	
		g_Player1.nCounterState--; //状態管理カウンターを毎Fデクリメントしていく

		if (g_Player1.nCounterState <= 0) //状態管理カウンターの数値が0以下になった場合
		{
			g_Player1.state = PLAYER1STATE_NORMAL; //敵の状態を通常状態にする

			//頂点カラーの設定(ポリゴンを通常色に戻す)
			pVertexPlayer1[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
			pVertexPlayer1[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1番目の頂点
			pVertexPlayer1[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2番目の頂点
			pVertexPlayer1[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3番目の頂点
		}
		break;

	case PLAYER1STATE_DEATH: //プレイヤー1が死亡状態である場合

		g_Player1.nCounterState--; //状態管理カウンターを毎Fデクリメントしていく

		if (g_Player1.nCounterState <= 0) //状態管理カウンターの数値が0以下になった場合
		{
			SetMode(MODE_RESULT); //モード設定(リザルト画面に移動する)

			return;
		}
		break;

	}
}

//プレイヤー1の描画処理========================================================
void DrawPlayer1(void)
{
	LPDIRECT3DDEVICE9 pDevicePlayer1; //デバイスへのポインタを宣言

	//デバイスの取得(ゲッター)処理
	pDevicePlayer1 = GetDevice();

	if (g_Player1.bDisp == true) //プレイヤーが表示されている時のみに括弧内の処理を行う
								 // (プレイヤーが非表示である場合はこの処理を行わないようにするため)
	{
		//頂点バッファをデータストリームに設定
		pDevicePlayer1->SetStreamSource(0, g_pVertexBufferPlayer1, 0, sizeof(VERTEX_2D));
		//g_pVertexBufferPolygon…頂点バッファへのポインタ VERTEX_2D…頂点情報構造体のサイズ

		//頂点フォーマットの設定
		pDevicePlayer1->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevicePlayer1->SetTexture(0, g_pTexturePlayer1);

		//ポリゴンの描画
		pDevicePlayer1->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//(D3DPT_TRIANGLESTRIP…プリミティブの種類 , 0…描画する最初の頂点インデックス , 2…描画するプリミティブ(ポリゴン)の数)
	}
}

//プレイヤー1の終了処理========================================================
void UninitPlayer1(void)
{
	//テクスチャの破棄①
	if (g_pTexturePlayer1 != NULL) //g_pTexturePlayer1にテクスチャが設定されている場合、
								   // テクスチャを破棄する処理
	{
		g_pTexturePlayer1->Release();
		g_pTexturePlayer1 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVertexBufferPlayer1 != NULL)
	{
		g_pVertexBufferPlayer1->Release();
		g_pVertexBufferPlayer1 = NULL;
	}
}

//プレイヤー1の被弾処理========================================================
void HitPlayer1(int nDamage)
{
	//変数を宣言するところ-----------------------------------------------------
	VERTEX_2D* pVertexPlayer1; //頂点情報へのポインタ
	int nCountPlayer1; //プレイヤー1の  をカウントするための変数

	g_Player1.nLife -= nDamage;

	if (g_Player1.nLife <= 0) //プレイヤー1の体力が0以下になった場合
	{
		//爆発の設定
		SetExplosion(g_Player1.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //位置, 色

		g_Player1.bDisp = false; //プレイヤー1を非表示にする

		g_Player1.state = PLAYER1STATE_DEATH; //プレイヤー1を死亡状態にする

		g_Player1.nCounterState = 60; //
	}

	else //敵の体力が0を超過している場合
	{
		g_Player1.state = PLAYER1STATE_DAMAGE;
		g_Player1.nCounterState = 5; //ダメージ状態を保持する時間を設定する

		pVertexPlayer1 += 4 * nCountPlayer1; //頂点データのポインタを4つ分進める

										   //頂点バッファをロックし、頂点情報へのポインタを取得する処理 ※この処理は各頂点設定の直上に置くこと※
		g_pVertexBufferPlayer1->Lock(0, 0, (void**)&pVertexPlayer1, 0);

		//頂点カラーの設定(ポリゴンをダメージ色に変更する)
		pVertexPlayer1[0].col = D3DCOLOR_RGBA(255, 0, 0, 255); //0番目の頂点{D3DCOLOR_RGBA(赤, 緑, 青, 透明度)};
		pVertexPlayer1[1].col = D3DCOLOR_RGBA(255, 0, 0, 255); //1番目の頂点
		pVertexPlayer1[2].col = D3DCOLOR_RGBA(255, 0, 0, 255); //2番目の頂点
		pVertexPlayer1[3].col = D3DCOLOR_RGBA(255, 0, 0, 255); //3番目の頂点

															  //頂点バッファをアンロックする処理 ※この処理は各頂点設定の直下に置くこと※
		g_pVertexBufferPlayer1->Unlock();
	}
}