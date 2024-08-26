//※プロジェクトのプロパティ→C/C++→プリプロセッサの定義→一番上の欄に「_CRT_SECURE_NO_WARNINGS」と入力,
// プロジェクト名を右クリック→プロパティ→詳細→マルチバイト文字セットを使用するを選択,
// VC++ ディレクトリ→インクルードディレクトリを選択→フォルダのアイコンを左クリック→三点リーダーを選択→
// C : \Program Files(x86)\Microsoft DirectX SDK(June 2010)\Includeのフォルダーを選択,
// 戻ってライブラリディレクトリを選択→フォルダのアイコンを左クリック→三点リーダーを選択→
// C : \Program Files(x86)\Microsoft DirectX SDK(June 2010)\Lib\x86のフォルダーを選択するのを忘れずに!!※

//==========================================
//ポリゴンの移動処理(R6.7.11-1.cpp)
// author:宮本蒼大
//==========================================

#include "R6.7.11-1-main.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
						    // 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-player2.h"
#include "R6.7.11-1-background.h"
#include "R6.7.11-1-input.h" //入力処理に特化した処理を管理する.hファイル
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-enemy1.h"
#include "R6.7.11-1-title.h"
#include "R6.7.11-1-game.h"
#include "R6.7.11-1-result.h"
#include "R6.7.11-1-fade.h"
#include "R6.7.11-1-sound.h"
#include "R6.7.11-1-score.h"
#include "R6.7.11-1-effect.h"

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL; //Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; //Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE; //現在のモード(ここにあるものが最初に表示されるモードとなる)

//----------
//メイン関数
//----------
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hInstancePrev,
	_In_ LPSTR IpCmdLine,
	_In_ int nCmdShow)
	//_In_ , _In_opt_…ソースコード注釈言語(緑波線を修正することが出来る)
	// hInstance…このアプリケーションのインスタントハンドル(識別子) hInstancePrev…(常にNULLとなっている)
	// IpCmdLine…コマンドラインで受け取った引数へのポインタ nCmdShow…初期ウィンドウの表示方法
{
	//変数を宣言するところ-----------------------------------------------------
	DWORD dwCurrentTime; //現在時刻
	DWORD dwExecLastTime; //最後に処理した時刻

	//ウィンドウクラスの構造体を定義-------------------------------------------
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //WNDCLASSEXのメモリサイズ
		CS_CLASSDC, //ウィンドウのスタイル
		WindowProc, //ウィンドウプロシージャ
		0, //0にする(通常は使用しない)
		0, //0にする(通常は使用しない)
		hInstance, //インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW), //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1), //クライアント領域の背景色
		NULL, //メニューバー
		CLASS_NAME, //ウィンドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION) //ファイルのアイコン
	};

	HWND hWnd; //ウィンドウハンドル(識別子)
	MSG msg; //メッセージを格納する変数

	//メイン関数に少し変更を加える!!
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; //画面サイズの構造体!!

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整!!
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成する処理-------------------------------------------------
	hWnd = CreateWindowEx(0,
		CLASS_NAME, //ウィンドウクラスの名前
		WINDOW_NAME, //ウィンドウの名前
		WS_OVERLAPPEDWINDOW, //ウィンドウスタイル
		CW_USEDEFAULT, //ウィンドウの左上X座標
		CW_USEDEFAULT, //ウィンドウの左上Y座標
		(rect.right - rect.left), //ウィンドウの幅!!
		(rect.bottom - rect.top), //ウィンドウの高さ!!
		NULL, //親ウィンドウのハンドル
		NULL, //メニューハンドルまたは子ウィンドウID
		hInstance, //インスタンスハンドル
		NULL); //ウィンドウ作成データ

	//初期化処理※必ず入れなければならないもの※
	if (FAILED(Init(hInstance, hWnd, TRUE))) //初期化処理が失敗した場合
	{
		return -1; //
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0; //初期化する
	dwExecLastTime = timeGetTime(); //現在時刻を取得(保存)する

	//ウィンドウを表示する処理-------------------------------------------------
	ShowWindow(hWnd, nCmdShow); //クライアントの表示状態を設定
	UpdateWindow(hWnd); //クライアント領域を更新

	//メッセージループ※この部分はどのゲームであっても同じものになる※
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)//メッセージキューからメッセージを取得し、
														  // WM_QUITメッセージを取得した場合に0を返す
		{ //Windowsの処理
			if (msg.message == WM_QUIT) //WM_QUITメッセージを受け取ったらメッセージループを抜ける処理
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg); //仮想キーメッセージを文字メッセージに変換する
				DispatchMessage(&msg); //ウィンドウプロシージャにメッセージを送り出す
			}
		}
		else
		{ //DirectXの処理
			dwExecLastTime = timeGetTime(); //現在時刻を取得(保存)する

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) //60分の1秒(1F)経過した場合
			{	
				dwExecLastTime = dwCurrentTime; //処理開始の時刻(現在時刻)を保存

				Update(); //更新処理
				Draw(); //描画処理
			}
		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//ウィンドウプロシージャ=======================================================

//変数を宣言するところ---------------------------------------------------------
int nID; //返り値を格納する変数を宣言する
HWND hWndButtonFinish; //終了ボタンのウィンドウハンドル(識別子)
static HWND hWndEditInput; //入力ウィンドウハンドル(コピー元)
static HWND hWndEditOutput; //出力ウィンドウハンドル(コピー元)
							// ※変数の型の前に「static」を指定すると、
							//    関数を抜けても変数の中の値が保持されるようになる※

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*static POINT pos = {7, 7}; //線分の始点{数値はX座標,Y座標}
	static POINT posRectangle = { 50, 570 }; //矩形の始点{数値はX座標,Y座標}
	static int nMoveX1 = 3; //線分の始点(X座標)の移動量
	static int nMoveY1 = 3; //線分の始点(Y座標)の移動量
	static int nMoveX2 = 3; //線分の始点(X座標)の移動量
	static int nMoveY2 = 3; //線分の始点(Y座標)の移動量*/
	//自分が動くためにどれ位の数値が必要か
	//※何かの条件で値が変化するようなものは変数としておくこと※
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; //ウィンドウの領域(矩形)
	//変数の型の前に「const」を指定すると、その変数は書き換え不可の定数となる
	/*char aString[256] = "test"; //描画するテキストを格納する変数*/

	switch (uMsg)
	{
	case WM_DESTROY: //ウィンドウ破棄のメッセージ
		//WM_QUITメッセージを送る処理
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE: //Escキーが押された場合

			//メッセージボックスを表示する処理
			nID = MessageBox(hWnd, "ウィンドウを閉じますか？", "終了確認", MB_YESNOCANCEL | MB_ICONQUESTION);
			//NULL…NULLを指定(この場合、このメッセージボックスがアクティブウィンドウにならない)
			// NULLの部分をhWndにすると、このウィンドウが親(オーナー)となり このメッセージボックスの処理が終了しない限り他の処理が出来なくなる
			// "ウィンドウを閉じますか？"…表示する文字列 "終了確認"…キャプションの文字列 MB_YESNOCANCEL…表示の種類()
			// MB_ICONQUESTION…表示する文字列の左側に出るアイコンの種類

			if (nID == IDYES) //メッセージボックスではい(Y)を選択した場合
			{
				MessageBox(hWnd, "ウィンドウを閉じます", " ", MB_OK);
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
				break;
			}
			else if (nID == IDNO) //メッセージボックスでいいえ(N)を選択した場合
			{
				MessageBox(hWnd, "ウィンドウに戻ります", " ", MB_OK);
			}
			else if (nID == IDCANCEL) //メッセージボックスでキャンセルを選択した場合
			{
				MessageBox(hWnd, "ウィンドウに戻ります", " ", MB_OK);
			}
			break;

		/*case WM_CLOSE: //ウィンドウ右上の「×」ボタンが押された場合

			//メッセージボックスを表示する処理
			nID = MessageBox(hWnd, "ウィンドウを閉じますか？", "終了確認", MB_YESNOCANCEL | MB_ICONQUESTION);
			//NULL…NULLを指定(この場合、このメッセージボックスがアクティブウィンドウにならない)
			// NULLの部分をhWndにすると、このウィンドウが親(オーナー)となり このメッセージボックスの処理が終了しない限り他の処理が出来なくなる
			// "ウィンドウを閉じますか？"…表示する文字列 "終了確認"…キャプションの文字列 MB_YESNOCANCEL…表示の種類()
			// MB_ICONQUESTION…表示する文字列の左側に出るアイコンの種類

			if (nID == IDYES) //メッセージボックスではい(Y)を選択した場合
			{
				MessageBox(hWnd, "ウィンドウを閉じます", " ", MB_OK);
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
				break;
			}
			else if (nID == IDNO) //メッセージボックスでいいえ(N)を選択した場合
			{
				MessageBox(hWnd, "ウィンドウに戻ります", " ", MB_OK);
				return 0; //ここで0を返さないとそのまま終了してしまうため
			}
			else if (nID == IDCANCEL) //メッセージボックスでキャンセルを選択した場合
			{
				MessageBox(hWnd, "ウィンドウに戻ります", " ", MB_OK);
				return 0; //ここで0を返さないとそのまま終了してしまうため
			}
			else
			{
				return 0; //ここで0を返さないとそのまま終了してしまうため
			}
			break;*/

		case WM_LBUTTONDOWN: //マウス左クリックのメッセージ
							 // マウスを左クリックしたウィンドウがアクティブになる
							 // (ESC押下は親ウィンドウのみでしか反応しないため)
			//ウィンドウにフォーカスを合わせる処理
			SetFocus(hWnd);
			break;
		}
	}

	//既存の処理を返す
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//デバイスの取得(ゲッター)処理
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//初期化処理===================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm; //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL) //ヌルチェック()
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH; //ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; //ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format; //バックバッファの形式
	d3dpp.BackBufferCount = 1; //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //ダブルバッファの切り替え(映像信号に同期)
	d3dpp.BackBufferWidth = SCREEN_WIDTH; //ゲーム画面サイズ(幅)
	d3dpp.EnableAutoDepthStencil = TRUE; //デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow; //ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理と頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定---------------------------------------------------
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //カリング(不要なポリゴンを描画しないことで処理不可を軽減する)の設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); //アルファブレンド(透明度の数値を反映させる)の設定①
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //アルファブレンド(透明度の数値を反映させる)の設定②
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //アルファブレンド(透明度の数値を反映させる)の設定③

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	
	

	//キーボードの初期化処理---------------------------------------------------
	if(FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ジョイパッドの初期化処理---------------------------------------------------
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//サウンドの初期化処理---------------------------------------------------
	InitSound(hWnd); //サウンドの初期化処理の関数を呼び出す

	SetMode(g_mode); //モードの設定

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}

//更新処理=====================================================================
void Update(void)
{
	//各オブジェクトの更新処理-------------------------------------------------	
	UpdateKeyboard(); //キーボードの更新処理の関数を呼び出す
	UpdateJoypad(); //ジョイパッドの更新処理の関数を呼び出す

	switch (g_mode) //g_mode…現在のモードを管理するグローバル変数
	{
	case MODE_TITLE: //タイトル画面が選択された場合
		UpdateTitle();
		break;

	case MODE_GAME: //ゲーム画面が選択された場合
		UpdateGame();
		break;

	case MODE_RESULT: //リザルト画面が選択された場合
		UpdateResult();
		break;
	}

	//フェードの更新処理
	UpdateFade();
}

//描画処理=====================================================================
void Draw(void)
{
	//画面クリア(バックバッファ＆Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene())) //描画開始が成功した場合
	{
		switch (g_mode) //g_mode…現在のモードを管理するグローバル変数
		{
		case MODE_TITLE: //タイトル画面が選択された場合
			DrawTitle();
			break;

		case MODE_GAME: //ゲーム画面が選択された場合
			DrawGame();
			break;

		case MODE_RESULT: //リザルト画面が選択された場合
			DrawResult();
			break;
		}

		//フェードの描画処理
		DrawFade();

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//終了処理=====================================================================
void Uninit(void)
{
	//タイトル画面の終了処理
	UninitTitle();

	//ゲーム画面の終了処理
	UninitGame();

	//リザルト画面の終了処理
	UninitResult();

	//フェードの終了処理
	UninitFade();

	//各オブジェクトの終了処理-------------------------------------------------
	UninitSound(); //サウンドの終了処理の関数を呼び出す
	UninitKeyboard(); //キーボードの終了処理の関数を呼び出す
	UninitJoypad(); //ジョイパッドの終了処理の関数を呼び出す

	/*//Direct3Dデバイスの破棄---------------------------------------------------
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dデバイスの破棄---------------------------------------------------
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}*/
}

//モードの設定処理
void SetMode(MODE mode)
{
	//現在のモードの終了処理
	switch (g_mode) //g_mode…現在のモードを管理するグローバル変数
	{
	case MODE_TITLE: //タイトル画面が選択された場合
		UninitTitle();
		break;

	case MODE_GAME: //ゲーム画面が選択された場合
		UninitGame();
		break;

	case MODE_RESULT: //リザルト画面が選択された場合
		UninitResult();
		break;
	}

	//新しい画面(モード)の初期化処理
	switch (g_mode) //g_mode…現在のモードを管理するグローバル変数
	{
	case MODE_TITLE: //タイトル画面が選択された場合
		InitTitle();
		break;

	case MODE_GAME: //ゲーム画面が選択された場合
		InitGame();
		break;

	case MODE_RESULT: //リザルト画面が選択された場合
		InitResult();
		break;
	}

	g_mode = mode; //現在の画面(モード)を切り替える
}

//モードの取得処理
MODE GetMode(void)
{
	return g_mode;
}