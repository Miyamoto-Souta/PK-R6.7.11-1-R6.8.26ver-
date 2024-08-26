#include "R6.7.11-1-result.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
#include "R6.7.11-1-input.h"  // ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-sound.h"


//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferResult = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posResult; //���U���g�̈ʒu���Ǘ�����ϐ�

//���U���g��ʂ̏���������
void InitResult(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceResult; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceResult = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDeviceResult,
		"data\\TEXTURE\\result000.png",
		&g_pTextureResult);

	//�e�퐔�l�̏�����
	g_posResult = D3DXVECTOR3(640.0f, 360.0f, 0.0f); //���U���g�̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};

	//���_�o�b�t�@�̐���
	pDeviceResult->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_��}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVertexBufferResult,
		NULL);

	VERTEX_2D* pVertexResult; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferResult->Lock(0, 0, (void**)&pVertexResult, 0);

	//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
	pVertexResult[0].pos = D3DXVECTOR3(g_posResult.x - RESULT_WIDTH / 2, g_posResult.y - RESULT_HEIGHT / 2, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
	pVertexResult[1].pos = D3DXVECTOR3(g_posResult.x + RESULT_WIDTH / 2, g_posResult.y - RESULT_HEIGHT / 2, 0.0f); //1�Ԗڂ̒��_
	pVertexResult[2].pos = D3DXVECTOR3(g_posResult.x - RESULT_WIDTH / 2, g_posResult.y + RESULT_HEIGHT / 2, 0.0f); //2�Ԗڂ̒��_
	pVertexResult[3].pos = D3DXVECTOR3(g_posResult.x + RESULT_WIDTH / 2, g_posResult.y + RESULT_HEIGHT / 2, 0.0f); //3�Ԗڂ̒��_

	//rhw�̐ݒ�
	pVertexResult[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexResult[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexResult[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexResult[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

	//���_�J���[�̐ݒ�
	pVertexResult[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
	pVertexResult[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
	pVertexResult[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
	pVertexResult[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_

	//�e�N�X�`�����W�̐ݒ�
	pVertexResult[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
	pVertexResult[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1�Ԗڂ̒��_
	pVertexResult[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
	pVertexResult[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3�Ԗڂ̒��_

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferResult->Unlock();
}

//���U���g��ʂ̍X�V����-----------------------------------------------------------
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true) //����(ENTER�L�[)�������ꂽ�ꍇ
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs����)
		SetMode(MODE_GAME);
	}
}

//���U���g��ʂ̕`�揈��-----------------------------------------------------------
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDeviceResult; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceResult = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceResult->SetStreamSource(0, g_pVertexBufferResult, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceResult->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDeviceResult->SetTexture(0, g_pTextureResult);

	//�|���S���̕`��
	pDeviceResult->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , 0�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
}

//���U���g��ʂ̏I������-----------------------------------------------------------
void UninitResult(void)
{
	//�e�N�X�`���̔j���@
	if (g_pTextureResult != NULL) //g_pTextureTitle�Ƀe�N�X�`�����ݒ肳��Ă���ꍇ�A
								  // �e�N�X�`����j�����鏈��
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferResult != NULL)
	{
		g_pVertexBufferResult->Release();
		g_pVertexBufferResult = NULL;
	}
}