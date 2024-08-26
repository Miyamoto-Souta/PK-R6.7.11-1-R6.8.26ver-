//���v���W�F�N�g�̃v���p�e�B��C/C++���v���v���Z�b�T�̒�`����ԏ�̗��Ɂu_CRT_SECURE_NO_WARNINGS�v�Ɠ���,
// �v���W�F�N�g�����E�N���b�N���v���p�e�B���ڍׁ��}���`�o�C�g�����Z�b�g���g�p�����I��,
// VC++ �f�B���N�g�����C���N���[�h�f�B���N�g����I�����t�H���_�̃A�C�R�������N���b�N���O�_���[�_�[��I����
// C : \Program Files(x86)\Microsoft DirectX SDK(June 2010)\Include�̃t�H���_�[��I��,
// �߂��ă��C�u�����f�B���N�g����I�����t�H���_�̃A�C�R�������N���b�N���O�_���[�_�[��I����
// C : \Program Files(x86)\Microsoft DirectX SDK(June 2010)\Lib\x86�̃t�H���_�[��I������̂�Y�ꂸ��!!��

//==========================================
//�|���S���̈ړ�����(R6.7.11-1.cpp)
// author:�{�{����
//==========================================

#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
						    // ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-player2.h"
#include "R6.7.11-1-background.h"
#include "R6.7.11-1-input.h" //���͏����ɓ��������������Ǘ�����.h�t�@�C��
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

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL; //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; //Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE; //���݂̃��[�h(�����ɂ�����̂��ŏ��ɕ\������郂�[�h�ƂȂ�)

//----------
//���C���֐�
//----------
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hInstancePrev,
	_In_ LPSTR IpCmdLine,
	_In_ int nCmdShow)
	//_In_ , _In_opt_�c�\�[�X�R�[�h���ߌ���(�Δg�����C�����邱�Ƃ��o����)
	// hInstance�c���̃A�v���P�[�V�����̃C���X�^���g�n���h��(���ʎq) hInstancePrev�c(���NULL�ƂȂ��Ă���)
	// IpCmdLine�c�R�}���h���C���Ŏ󂯎���������ւ̃|�C���^ nCmdShow�c�����E�B���h�E�̕\�����@
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	DWORD dwCurrentTime; //���ݎ���
	DWORD dwExecLastTime; //�Ō�ɏ�����������

	//�E�B���h�E�N���X�̍\���̂��`-------------------------------------------
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC, //�E�B���h�E�̃X�^�C��
		WindowProc, //�E�B���h�E�v���V�[�W��
		0, //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0, //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW), //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1), //�N���C�A���g�̈�̔w�i�F
		NULL, //���j���[�o�[
		CLASS_NAME, //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION) //�t�@�C���̃A�C�R��
	};

	HWND hWnd; //�E�B���h�E�n���h��(���ʎq)
	MSG msg; //���b�Z�[�W���i�[����ϐ�

	//���C���֐��ɏ����ύX��������!!
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; //��ʃT�C�Y�̍\����!!

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���!!
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐����鏈��-------------------------------------------------
	hWnd = CreateWindowEx(0,
		CLASS_NAME, //�E�B���h�E�N���X�̖��O
		WINDOW_NAME, //�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW, //�E�B���h�E�X�^�C��
		CW_USEDEFAULT, //�E�B���h�E�̍���X���W
		CW_USEDEFAULT, //�E�B���h�E�̍���Y���W
		(rect.right - rect.left), //�E�B���h�E�̕�!!
		(rect.bottom - rect.top), //�E�B���h�E�̍���!!
		NULL, //�e�E�B���h�E�̃n���h��
		NULL, //���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance, //�C���X�^���X�n���h��
		NULL); //�E�B���h�E�쐬�f�[�^

	//�������������K������Ȃ���΂Ȃ�Ȃ����́�
	if (FAILED(Init(hInstance, hWnd, TRUE))) //���������������s�����ꍇ
	{
		return -1; //
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0; //����������
	dwExecLastTime = timeGetTime(); //���ݎ������擾(�ۑ�)����

	//�E�B���h�E��\�����鏈��-------------------------------------------------
	ShowWindow(hWnd, nCmdShow); //�N���C�A���g�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd); //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v�����̕����͂ǂ̃Q�[���ł����Ă��������̂ɂȂ遦
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)//���b�Z�[�W�L���[���烁�b�Z�[�W���擾���A
														  // WM_QUIT���b�Z�[�W���擾�����ꍇ��0��Ԃ�
		{ //Windows�̏���
			if (msg.message == WM_QUIT) //WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂��鏈��
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); //���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�����
				DispatchMessage(&msg); //�E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�o��
			}
		}
		else
		{ //DirectX�̏���
			dwExecLastTime = timeGetTime(); //���ݎ������擾(�ۑ�)����

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) //60����1�b(1F)�o�߂����ꍇ
			{	
				dwExecLastTime = dwCurrentTime; //�����J�n�̎���(���ݎ���)��ۑ�

				Update(); //�X�V����
				Draw(); //�`�揈��
			}
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W��=======================================================

//�ϐ���錾����Ƃ���---------------------------------------------------------
int nID; //�Ԃ�l���i�[����ϐ���錾����
HWND hWndButtonFinish; //�I���{�^���̃E�B���h�E�n���h��(���ʎq)
static HWND hWndEditInput; //���̓E�B���h�E�n���h��(�R�s�[��)
static HWND hWndEditOutput; //�o�̓E�B���h�E�n���h��(�R�s�[��)
							// ���ϐ��̌^�̑O�Ɂustatic�v���w�肷��ƁA
							//    �֐��𔲂��Ă��ϐ��̒��̒l���ێ������悤�ɂȂ遦

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*static POINT pos = {7, 7}; //�����̎n�_{���l��X���W,Y���W}
	static POINT posRectangle = { 50, 570 }; //��`�̎n�_{���l��X���W,Y���W}
	static int nMoveX1 = 3; //�����̎n�_(X���W)�̈ړ���
	static int nMoveY1 = 3; //�����̎n�_(Y���W)�̈ړ���
	static int nMoveX2 = 3; //�����̎n�_(X���W)�̈ړ���
	static int nMoveY2 = 3; //�����̎n�_(Y���W)�̈ړ���*/
	//�������������߂ɂǂ�ʂ̐��l���K�v��
	//�������̏����Œl���ω�����悤�Ȃ��͕̂ϐ��Ƃ��Ă������Ɓ�
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; //�E�B���h�E�̗̈�(��`)
	//�ϐ��̌^�̑O�Ɂuconst�v���w�肷��ƁA���̕ϐ��͏��������s�̒萔�ƂȂ�
	/*char aString[256] = "test"; //�`�悷��e�L�X�g���i�[����ϐ�*/

	switch (uMsg)
	{
	case WM_DESTROY: //�E�B���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂鏈��
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE: //Esc�L�[�������ꂽ�ꍇ

			//���b�Z�[�W�{�b�N�X��\�����鏈��
			nID = MessageBox(hWnd, "�E�B���h�E����܂����H", "�I���m�F", MB_YESNOCANCEL | MB_ICONQUESTION);
			//NULL�cNULL���w��(���̏ꍇ�A���̃��b�Z�[�W�{�b�N�X���A�N�e�B�u�E�B���h�E�ɂȂ�Ȃ�)
			// NULL�̕�����hWnd�ɂ���ƁA���̃E�B���h�E���e(�I�[�i�[)�ƂȂ� ���̃��b�Z�[�W�{�b�N�X�̏������I�����Ȃ����葼�̏������o���Ȃ��Ȃ�
			// "�E�B���h�E����܂����H"�c�\�����镶���� "�I���m�F"�c�L���v�V�����̕����� MB_YESNOCANCEL�c�\���̎��()
			// MB_ICONQUESTION�c�\�����镶����̍����ɏo��A�C�R���̎��

			if (nID == IDYES) //���b�Z�[�W�{�b�N�X�ł͂�(Y)��I�������ꍇ
			{
				MessageBox(hWnd, "�E�B���h�E����܂�", " ", MB_OK);
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
				break;
			}
			else if (nID == IDNO) //���b�Z�[�W�{�b�N�X�ł�����(N)��I�������ꍇ
			{
				MessageBox(hWnd, "�E�B���h�E�ɖ߂�܂�", " ", MB_OK);
			}
			else if (nID == IDCANCEL) //���b�Z�[�W�{�b�N�X�ŃL�����Z����I�������ꍇ
			{
				MessageBox(hWnd, "�E�B���h�E�ɖ߂�܂�", " ", MB_OK);
			}
			break;

		/*case WM_CLOSE: //�E�B���h�E�E��́u�~�v�{�^���������ꂽ�ꍇ

			//���b�Z�[�W�{�b�N�X��\�����鏈��
			nID = MessageBox(hWnd, "�E�B���h�E����܂����H", "�I���m�F", MB_YESNOCANCEL | MB_ICONQUESTION);
			//NULL�cNULL���w��(���̏ꍇ�A���̃��b�Z�[�W�{�b�N�X���A�N�e�B�u�E�B���h�E�ɂȂ�Ȃ�)
			// NULL�̕�����hWnd�ɂ���ƁA���̃E�B���h�E���e(�I�[�i�[)�ƂȂ� ���̃��b�Z�[�W�{�b�N�X�̏������I�����Ȃ����葼�̏������o���Ȃ��Ȃ�
			// "�E�B���h�E����܂����H"�c�\�����镶���� "�I���m�F"�c�L���v�V�����̕����� MB_YESNOCANCEL�c�\���̎��()
			// MB_ICONQUESTION�c�\�����镶����̍����ɏo��A�C�R���̎��

			if (nID == IDYES) //���b�Z�[�W�{�b�N�X�ł͂�(Y)��I�������ꍇ
			{
				MessageBox(hWnd, "�E�B���h�E����܂�", " ", MB_OK);
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
				break;
			}
			else if (nID == IDNO) //���b�Z�[�W�{�b�N�X�ł�����(N)��I�������ꍇ
			{
				MessageBox(hWnd, "�E�B���h�E�ɖ߂�܂�", " ", MB_OK);
				return 0; //������0��Ԃ��Ȃ��Ƃ��̂܂܏I�����Ă��܂�����
			}
			else if (nID == IDCANCEL) //���b�Z�[�W�{�b�N�X�ŃL�����Z����I�������ꍇ
			{
				MessageBox(hWnd, "�E�B���h�E�ɖ߂�܂�", " ", MB_OK);
				return 0; //������0��Ԃ��Ȃ��Ƃ��̂܂܏I�����Ă��܂�����
			}
			else
			{
				return 0; //������0��Ԃ��Ȃ��Ƃ��̂܂܏I�����Ă��܂�����
			}
			break;*/

		case WM_LBUTTONDOWN: //�}�E�X���N���b�N�̃��b�Z�[�W
							 // �}�E�X�����N���b�N�����E�B���h�E���A�N�e�B�u�ɂȂ�
							 // (ESC�����͐e�E�B���h�E�݂̂ł����������Ȃ�����)
			//�E�B���h�E�Ƀt�H�[�J�X�����킹�鏈��
			SetFocus(hWnd);
			break;
		}
	}

	//�����̏�����Ԃ�
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//�f�o�C�X�̎擾(�Q�b�^�[)����
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//����������===================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm; //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp; //�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL) //�k���`�F�b�N()
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH; //�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; //�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format; //�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1; //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.BackBufferWidth = SCREEN_WIDTH; //�Q�[����ʃT�C�Y(��)
	d3dpp.EnableAutoDepthStencil = TRUE; //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow; //�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
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

	//�����_�[�X�e�[�g�̐ݒ�---------------------------------------------------
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //�J�����O(�s�v�ȃ|���S����`�悵�Ȃ����Ƃŏ����s���y������)�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); //�A���t�@�u�����h(�����x�̐��l�𔽉f������)�̐ݒ�@
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //�A���t�@�u�����h(�����x�̐��l�𔽉f������)�̐ݒ�A
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //�A���t�@�u�����h(�����x�̐��l�𔽉f������)�̐ݒ�B

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	
	

	//�L�[�{�[�h�̏���������---------------------------------------------------
	if(FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�h�̏���������---------------------------------------------------
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//�T�E���h�̏���������---------------------------------------------------
	InitSound(hWnd); //�T�E���h�̏����������̊֐����Ăяo��

	SetMode(g_mode); //���[�h�̐ݒ�

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	return S_OK;
}

//�X�V����=====================================================================
void Update(void)
{
	//�e�I�u�W�F�N�g�̍X�V����-------------------------------------------------	
	UpdateKeyboard(); //�L�[�{�[�h�̍X�V�����̊֐����Ăяo��
	UpdateJoypad(); //�W���C�p�b�h�̍X�V�����̊֐����Ăяo��

	switch (g_mode) //g_mode�c���݂̃��[�h���Ǘ�����O���[�o���ϐ�
	{
	case MODE_TITLE: //�^�C�g����ʂ��I�����ꂽ�ꍇ
		UpdateTitle();
		break;

	case MODE_GAME: //�Q�[����ʂ��I�����ꂽ�ꍇ
		UpdateGame();
		break;

	case MODE_RESULT: //���U���g��ʂ��I�����ꂽ�ꍇ
		UpdateResult();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//�`�揈��=====================================================================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene())) //�`��J�n�����������ꍇ
	{
		switch (g_mode) //g_mode�c���݂̃��[�h���Ǘ�����O���[�o���ϐ�
		{
		case MODE_TITLE: //�^�C�g����ʂ��I�����ꂽ�ꍇ
			DrawTitle();
			break;

		case MODE_GAME: //�Q�[����ʂ��I�����ꂽ�ꍇ
			DrawGame();
			break;

		case MODE_RESULT: //���U���g��ʂ��I�����ꂽ�ꍇ
			DrawResult();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//�I������=====================================================================
void Uninit(void)
{
	//�^�C�g����ʂ̏I������
	UninitTitle();

	//�Q�[����ʂ̏I������
	UninitGame();

	//���U���g��ʂ̏I������
	UninitResult();

	//�t�F�[�h�̏I������
	UninitFade();

	//�e�I�u�W�F�N�g�̏I������-------------------------------------------------
	UninitSound(); //�T�E���h�̏I�������̊֐����Ăяo��
	UninitKeyboard(); //�L�[�{�[�h�̏I�������̊֐����Ăяo��
	UninitJoypad(); //�W���C�p�b�h�̏I�������̊֐����Ăяo��

	/*//Direct3D�f�o�C�X�̔j��---------------------------------------------------
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�f�o�C�X�̔j��---------------------------------------------------
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}*/
}

//���[�h�̐ݒ菈��
void SetMode(MODE mode)
{
	//���݂̃��[�h�̏I������
	switch (g_mode) //g_mode�c���݂̃��[�h���Ǘ�����O���[�o���ϐ�
	{
	case MODE_TITLE: //�^�C�g����ʂ��I�����ꂽ�ꍇ
		UninitTitle();
		break;

	case MODE_GAME: //�Q�[����ʂ��I�����ꂽ�ꍇ
		UninitGame();
		break;

	case MODE_RESULT: //���U���g��ʂ��I�����ꂽ�ꍇ
		UninitResult();
		break;
	}

	//�V�������(���[�h)�̏���������
	switch (g_mode) //g_mode�c���݂̃��[�h���Ǘ�����O���[�o���ϐ�
	{
	case MODE_TITLE: //�^�C�g����ʂ��I�����ꂽ�ꍇ
		InitTitle();
		break;

	case MODE_GAME: //�Q�[����ʂ��I�����ꂽ�ꍇ
		InitGame();
		break;

	case MODE_RESULT: //���U���g��ʂ��I�����ꂽ�ꍇ
		InitResult();
		break;
	}

	g_mode = mode; //���݂̉��(���[�h)��؂�ւ���
}

//���[�h�̎擾����
MODE GetMode(void)
{
	return g_mode;
}