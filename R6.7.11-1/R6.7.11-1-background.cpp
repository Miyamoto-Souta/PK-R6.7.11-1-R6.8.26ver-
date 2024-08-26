#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
							// ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-background.h"

//�}�N����`
#define NUM_BACKGROUND (3) //�w�i�̏d�˂鐔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureBackground[NUM_BACKGROUND] = {}; //�e�N�X�`��([NUM_BACKGROUND])�����ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferBackground = NULL; //���_�o�b�t�@�ւ̃|�C���^
float g_aPosTextureU[NUM_BACKGROUND]; //�e�N�X�`�����W��U�l�̊J�n�ʒu

//�w�i�̏���������---------------------------------------------------------
void InitBackground(void)
{
	LPDIRECT3DDEVICE9 pDeviceBackground; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountBackGround; //�w�i�̖������J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceBackground = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDeviceBackground,
							  "data\\TEXTURE\\bg101.jpg",
							  &g_apTextureBackground[0]);

	//�e�N�X�`���̓ǂݍ��݇A
	D3DXCreateTextureFromFile(pDeviceBackground,
							  "data\\TEXTURE\\bg102.jpg",
							  &g_apTextureBackground[1]);

	//�e�N�X�`���̓ǂݍ��݇B
	D3DXCreateTextureFromFile(pDeviceBackground,
							  "data\\TEXTURE\\bg103.jpg",
							  &g_apTextureBackground[2]);

	//�e�N�X�`�����W�̊J�n�ʒu(U�l)�̏�����
	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		g_aPosTextureU[nCountBackGround] = 0.0f;
	}

	//���_�o�b�t�@�̐���
	pDeviceBackground->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACKGROUND, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_�� �~ [NUM_BACKGROUND]}
										  D3DUSAGE_WRITEONLY,
										  FVF_VERTEX_2D, //���_�t�H�[�}�b�g
										  D3DPOOL_MANAGED,
										  &g_pVertexBufferBackground,
										  NULL);

	VERTEX_2D* pVertexBackground; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferBackground->Lock(0, 0, (void**)&pVertexBackground, 0);

	//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
		pVertexBackground[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
		pVertexBackground[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f); //1�Ԗڂ̒��_
		pVertexBackground[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f); //2�Ԗڂ̒��_
		pVertexBackground[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f); //3�Ԗڂ̒��_

		//rhw�̐ݒ�
		pVertexBackground[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexBackground[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexBackground[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexBackground[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

		//���_�J���[�̐ݒ�
		pVertexBackground[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
		pVertexBackground[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
		pVertexBackground[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
		pVertexBackground[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_

		//�e�N�X�`�����W�̐ݒ�
		pVertexBackground[0].tex = D3DXVECTOR2(g_aPosTextureU[nCountBackGround], 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
		pVertexBackground[1].tex = D3DXVECTOR2(g_aPosTextureU[nCountBackGround] + 1.0f, 0.0f); //1�Ԗڂ̒��_
		pVertexBackground[2].tex = D3DXVECTOR2(g_aPosTextureU[nCountBackGround], 1.0f); //2�Ԗڂ̒��_
		pVertexBackground[3].tex = D3DXVECTOR2(g_aPosTextureU[nCountBackGround] + 1.0f, 1.0f); //3�Ԗڂ̒��_

		pVertexBackground += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferBackground->Unlock();
}

//�w�i�̍X�V����-----------------------------------------------------------
void UpdateBackground(void)
{
	int nCountBackGround; //�w�i�̖������J�E���g���邽�߂̕ϐ�

	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		//�e�N�X�`�����W��U�l�̊J�n�ʒu���X�V���鏈��
		��

		//�e�N�X�`�����W���X�V���鏈��
		��

	}
}

//�w�i�̕`�揈��-----------------------------------------------------------
void DrawBackground(void)
{
	LPDIRECT3DDEVICE9 pDeviceBackground; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountBackGround; //�w�i�̖������J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceBackground = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceBackground->SetStreamSource(0, g_pVertexBufferBackground, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceBackground->SetFVF(FVF_VERTEX_2D);

	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		//�e�N�X�`���̐ݒ�
		pDeviceBackground->SetTexture(0, g_apTextureBackground[nCountBackGround]);

		//�|���S���̕`��
		pDeviceBackground->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , 0�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
	}
}

//�w�i�̏I������-----------------------------------------------------------
void UninitBackground(void)
{
	int nCountBackGround; //�w�i�̖������J�E���g���邽�߂̕ϐ�

	//�e�N�X�`���̔j��
	for (nCountBackGround = 0; nCountBackGround < NUM_BACKGROUND; nCountBackGround++)
	{
		if (g_apTextureBackground[nCountBackGround] != NULL) //g_apTextureBackground[nCountBackGround]��
															 // �e�N�X�`�����ݒ肳��Ă���ꍇ�A�e�N�X�`����j�����鏈��
		{
			g_apTextureBackground[nCountBackGround]->Release();
			g_apTextureBackground[nCountBackGround] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferBackground != NULL)
	{
		g_pVertexBufferBackground->Release();
		g_pVertexBufferBackground = NULL;
	}
}