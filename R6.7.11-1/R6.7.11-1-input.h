#ifndef _INPUT_H_ //このマクロ定義がされていなかった場合 ※1行目に必ず書くこと※

#define _INPUT_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include "R6.7.11-1-main.h"

//キーの種類(16個全て入れること!!)
typedef enum
{
	JOYKEY_UP = 0, //十字キー(上)
	JOYKEY_DOWN, //十字キー(下)
	JOYKEY_LEFT, //十字キー(左)
	JOYKEY_RIGHT, //十字キー(右)
	JOYKEY_START, //STARTボタン
	JOYKEY_SELECT, //SELECTボタン
	JOYKEY_L3, //L3ボタン(Lスティック押し込み)
	JOYKEY_R3, //R3ボタン(Rスティック押し込み)
	JOYKEY_L1, //L1ボタン
	JOYKEY_R1, //R1ボタン
	JOYKEY_L2, //L2ボタン(現在は出来ない)
	JOYKEY_R2, //R2ボタン(現在は出来ない)
	JOYKEY_A, //Aボタン
	JOYKEY_B, //Bボタン
	JOYKEY_X, //Xボタン
	JOYKEY_Y, //Yボタン
	JOYKEY_MAX
}JOYKEY;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd); //キーボード入力の初期化処理
void UninitKeyboard(void); //キーボード入力の終了処理
void UpdateKeyboard(void); //キーボード入力の更新処理
HRESULT InitJoypad(void); //ジョイパッド入力の初期化処理
void UninitJoypad(void); //ジョイパッド入力の終了処理
void UpdateJoypad(void); //ジョイパッド入力の更新処理
bool GetKeyboardPress(int nKey); //キーボード入力のプレス情報を取得する処理
bool GetKeyboardTrigger(int nKey); //キーボード入力のプレス情報(押された瞬間)を取得する処理
bool GetKeyboardRepeat(int nKey); //キーボード入力のプレス情報(長押し)を取得する処理
bool GetKeyboardRelease(int nKey); //キーボード入力のプレス情報(離れた瞬間)を取得する処理
bool GetJoypadPress(JOYKEY nKey); //ジョイパッド入力のプレス情報を取得する処理
/*bool GetJoypadTrigger(JOYKEY nKey); //ジョイパッド入力のプレス情報(押された瞬間)を取得する処理
bool GetJoypadRepeat(JOYKEY nKey); //ジョイパッド入力のプレス情報(長押し)を取得する処理
bool GetJoypadRelease(JOYKEY nKey); //ジョイパッド入力のプレス情報(離れた瞬間)を取得する処理*/

#endif //※最下行に必ず書くこと※