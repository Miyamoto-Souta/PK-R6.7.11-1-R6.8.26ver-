#ifndef _MAIN_H_ //このマクロ定義がされていなかった場合 ※1行目に必ず書くこと※

#define _MAIN_H_ //多重インクルード(読み込み)防止用のマクロ定義

#include <windows.h> //PC内のライブラリを使いたい場合は「<〇〇.h>」,
// 自作のヘッダーファイルを使いたい場合は「"〇〇.h"」と記入する
#include "d3dx9.h" //描画処理に必要

//マクロ定義①
#define DIRECTINPUT_VERSION (0x0800) //ビルド時の警告対処用マクロ定義
#include "dinput.h" //入力処理に必要となる
#include "Xinput.h" //ジョイパッドの入力処理に必要となる
#include "xaudio2.h" //サウンド処理に必要となる

//ライブラリのリンク
#pragma comment(lib, "d3d9.lib") //描画処理に必要
#pragma comment(lib, "d3dx9.lib") //d3d9.libの拡張ライブラリ
#pragma comment(lib, "dxguid.lib") //DirectXコンポーネント(部品)を使用するのに必要となる
#pragma comment(lib, "winmm.lib") //システム時刻を取得するのに必要となる
#pragma comment(lib, "dinput8.lib") //入力処理に必要となる
#pragma comment(lib, "xinput.lib") //ジョイパッドの入力処理に必要となる

//マクロ定義②
#define CLASS_NAME "WindowClass" //ウィンドウクラスの名前
#define WINDOW_NAME "DirectXの基本処理" //ウィンドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280) //ウィンドウの幅
#define SCREEN_HEIGHT (720) //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //ポリゴンの頂点フォーマット(2D)
//D3DFVF_XYZRHW…頂点座標(XYZ) D3DFVF_DIFFUSE…頂点カラー D3DFVF_TEX1…テクスチャ座標

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0, //タイトル画面
	MODE_GAME, //ゲーム画面
	MODE_RESULT, //リザルト画面
	MODE_MANUAL, //マニュアル画面
	MODE_OPTION, //オプション画面
	MODE_MAX
} MODE;

//頂点情報(2D)の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float rhw; //座標変換用係数(1.0fで固定)
	D3DCOLOR col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標(テクスチャは平面なので2D)
} VERTEX_2D;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void); //
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hwnd, BOOL bWindow); //初期化処理
void Uninit(void); //終了処理
void Update(void); //更新処理
void Draw(void); //描画処理
void SetMode(MODE mode); //
MODE GetMode(void); //

#endif //※最下行に必ず書くこと※