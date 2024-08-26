#include "R6.7.11-1-title.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
#include "R6.7.11-1-input.h" // ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferTitle = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTitle; //�^�C�g���̈ʒu���Ǘ�����ϐ�

//�^�C�g����ʂ̏���������
void InitTitle(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceTitle; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceTitle = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDeviceTitle,
		"data\\TEXTURE\\title000.png",
		&g_pTextureTitle);

	//�e�퐔�l�̏�����
	g_posTitle = D3DXVECTOR3(640.0f, 360.0f, 0.0f); //�v���C���[1�̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};

	//���_�o�b�t�@�̐���
	pDeviceTitle->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_��}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVertexBufferTitle,
		NULL);

	VERTEX_2D* pVertexTitle; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferTitle->Lock(0, 0, (void**)&pVertexTitle, 0);

	//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
	pVertexTitle[0].pos = D3DXVECTOR3(g_posTitle.x - TITLE_WIDTH / 2, g_posTitle.y - TITLE_HEIGHT / 2, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
	pVertexTitle[1].pos = D3DXVECTOR3(g_posTitle.x + TITLE_WIDTH / 2, g_posTitle.y - TITLE_HEIGHT / 2, 0.0f); //1�Ԗڂ̒��_
	pVertexTitle[2].pos = D3DXVECTOR3(g_posTitle.x - TITLE_WIDTH / 2, g_posTitle.y + TITLE_HEIGHT / 2, 0.0f); //2�Ԗڂ̒��_
	pVertexTitle[3].pos = D3DXVECTOR3(g_posTitle.x + TITLE_WIDTH / 2, g_posTitle.y + TITLE_HEIGHT / 2, 0.0f); //3�Ԗڂ̒��_

	//rhw�̐ݒ�
	pVertexTitle[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexTitle[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexTitle[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexTitle[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

	//���_�J���[�̐ݒ�
	pVertexTitle[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
	pVertexTitle[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
	pVertexTitle[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
	pVertexTitle[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_

	//�e�N�X�`�����W�̐ݒ�
	pVertexTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
	pVertexTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1�Ԗڂ̒��_
	pVertexTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
	pVertexTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3�Ԗڂ̒��_

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferTitle->Unlock();

	//�T�E���h���Đ�����
	PlaySound(SOUND_LABEL_TITLE_BGM); //SOUND_LABEL_BGM�Ɏw�肵�������t�@�C�����Đ�����
	PlaySound(SOUND_LABEL_SE); //SOUND_LABEL_SE�Ɏw�肵�������t�@�C�����Đ�����
}

//�^�C�g����ʂ̍X�V����-----------------------------------------------------------
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true) //����(ENTER�L�[)�������ꂽ�ꍇ
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs����)
		SetMode(MODE_GAME);
	}
}

//�^�C�g����ʂ̕`�揈��-----------------------------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDeviceTitle; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceTitle = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceTitle->SetStreamSource(0, g_pVertexBufferTitle, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceTitle->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDeviceTitle->SetTexture(0, g_pTextureTitle);

	//�|���S���̕`��
	pDeviceTitle->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , 0�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
}

//�^�C�g����ʂ̏I������-----------------------------------------------------------
void UninitTitle(void)
{
	//�T�E���h���~����
	StopSound();

	//�e�N�X�`���̔j���@
	if (g_pTextureTitle != NULL) //g_pTextureTitle�Ƀe�N�X�`�����ݒ肳��Ă���ꍇ�A
								 // �e�N�X�`����j�����鏈��
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferTitle != NULL)
	{
		g_pVertexBufferTitle->Release();
		g_pVertexBufferTitle = NULL;
	}
}