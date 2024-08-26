#include "R6.7.11-1-input.h" //PC内のライブラリを使いたい場合は「<〇〇.h>」,
							 // 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する

//マクロ定義
#define NUM_KEY_MAX (256) //キーの種類の最大数

//グローバル変数宣言
LPDIRECTINPUT8 g_pInput = NULL; //DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX]; //キーボードのプレス情報(バイト型)
BYTE g_aOldKeyState[NUM_KEY_MAX]; //1つ前のキーボードのプレス情報(バイト型)
XINPUT_STATE g_joykeyState; //ジョイパッドのプレス情報

//キーボードの初期化処理=======================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成

	//キーボードの  に失敗した場合の処理
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
											 IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の作成

	//キーボードの  に失敗した場合の処理
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モード
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得する
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//ジョイパッドの初期化処理=======================================================
HRESULT InitJoypad(void)
{
	//メモリのクリアを行う
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));

	//XInputのステートを設定(有効に)する
	XInputEnable(true);

	return S_OK;
}
//キーボードの更新処理=========================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //キーボードの入力情報
	int nCountKey;

	//1つ前のキー入力情報を保存する
	for (nCountKey = 0; nCountKey < NUM_KEY_MAX; nCountKey++)
	{
		g_aOldKeyState[nCountKey] = g_aKeyState[nCountKey];
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCountKey = 0; nCountKey < NUM_KEY_MAX; nCountKey++)
		{
			g_aKeyState[nCountKey] = aKeyState[nCountKey]; //キーボードのプレス情報を保存する
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); //キーボードのアクセス権を獲得
	}
}

//ジョイパッドの更新処理=========================================================
void UpdateJoypad(void)
{
	//ジョイパッドの入力情報
	XINPUT_STATE joykeyState;

	//ジョイパッドの状態を取得する
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joykeyState = joykeyState; //ジョイパッドのプレス情報を保存
	}
}

//キーボード入力のプレス情報を取得する処理=====================================
bool GetKeyboardPress(int nKey)
{
	//「条件式 ? A: B;」の形の3項演算子
	//  この場合、条件式が真(true)であればAを返し、偽(false)であればBを返す。
	return(g_aKeyState[nKey] & 0x80) ? true: false;

}

//キーボード入力のプレス情報(押された瞬間)を取得する処理=======================
bool GetKeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//キーボード入力のプレス情報(長押し)を取得する処理=============================
bool GetKeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;

}

//キーボード入力のプレス情報(離れた瞬間)を取得する処理=========================
bool GetKeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;

}

//ジョイパッド入力のプレス情報を取得する処理===================================
bool GetJoypadPress(JOYKEY nKey)
{
	return (g_joykeyState.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}

/*//ジョイパッド入力のプレス情報(押された瞬間)を取得する処理=====================
bool GetJoypadTrigger(JOYKEY nKey)
{
	
}

//ジョイパッド入力のプレス情報(長押し)を取得する処理===========================
bool GetJoypadRepeat(JOYKEY nKey)
{

}

//ジョイパッド入力のプレス情報(離れた瞬間)を取得する処理=======================
bool GetJoypadRelease(JOYKEY nKey)
{

}*/

//キーボードの終了処理=========================================================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //キーボードへのアクセス権を放棄する
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//ジョイパッドの終了処理=========================================================
void UninitJoypad(void)
{
	//XInputのステートを設定(無効に)する
	XInputEnable(false);
}