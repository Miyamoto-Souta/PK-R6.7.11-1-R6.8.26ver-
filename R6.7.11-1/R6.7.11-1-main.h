#ifndef _MAIN_H_ //���̃}�N����`������Ă��Ȃ������ꍇ ��1�s�ڂɕK���������Ɓ�

#define _MAIN_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include <windows.h> //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
// ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "d3dx9.h" //�`�揈���ɕK�v

//�}�N����`�@
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�}�N����`
#include "dinput.h" //���͏����ɕK�v�ƂȂ�
#include "Xinput.h" //�W���C�p�b�h�̓��͏����ɕK�v�ƂȂ�
#include "xaudio2.h" //�T�E���h�����ɕK�v�ƂȂ�

//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib") //�`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib") //d3d9.lib�̊g�����C�u����
#pragma comment(lib, "dxguid.lib") //DirectX�R���|�[�l���g(���i)���g�p����̂ɕK�v�ƂȂ�
#pragma comment(lib, "winmm.lib") //�V�X�e���������擾����̂ɕK�v�ƂȂ�
#pragma comment(lib, "dinput8.lib") //���͏����ɕK�v�ƂȂ�
#pragma comment(lib, "xinput.lib") //�W���C�p�b�h�̓��͏����ɕK�v�ƂȂ�

//�}�N����`�A
#define CLASS_NAME "WindowClass" //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "DirectX�̊�{����" //�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1280) //�E�B���h�E�̕�
#define SCREEN_HEIGHT (720) //�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //�|���S���̒��_�t�H�[�}�b�g(2D)
//D3DFVF_XYZRHW�c���_���W(XYZ) D3DFVF_DIFFUSE�c���_�J���[ D3DFVF_TEX1�c�e�N�X�`�����W

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0, //�^�C�g�����
	MODE_GAME, //�Q�[�����
	MODE_RESULT, //���U���g���
	MODE_MANUAL, //�}�j���A�����
	MODE_OPTION, //�I�v�V�������
	MODE_MAX
} MODE;

//���_���(2D)�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W(�e�N�X�`���͕��ʂȂ̂�2D)
} VERTEX_2D;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void); //
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hwnd, BOOL bWindow); //����������
void Uninit(void); //�I������
void Update(void); //�X�V����
void Draw(void); //�`�揈��
void SetMode(MODE mode); //
MODE GetMode(void); //

#endif //���ŉ��s�ɕK���������Ɓ�