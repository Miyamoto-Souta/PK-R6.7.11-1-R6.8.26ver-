#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
							// ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-player2.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer2 = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferPlayer2 = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posPlayer2; //�v���C���[1�̈ʒu���Ǘ�����ϐ�
int g_nCounterAnimPlayer2; //�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer2; //�A�j���[�V�����p�^�[���̔ԍ�

//�v���C���[2�̏���������---------------------------------------------------------
void InitPlayer2(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDevicePlayer2; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDevicePlayer2 = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDevicePlayer2,
		"data\\TEXTURE\\runningman200.png",
		&g_pTexturePlayer2);

	//�e�퐔�l�̏�����
	g_posPlayer2 = D3DXVECTOR3(1100.0f, 200.0f, 0.0f); //�v���C���[2�̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};
	g_nCounterAnimPlayer2 = 0; //�A�j���[�V�����J�E���^�[������������
	g_nPatternAnimPlayer2 = 0; //�A�j���[�V�����p�^�[���̔ԍ�������������

	//���_�o�b�t�@�̐���
	pDevicePlayer2->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_��}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVertexBufferPlayer2,
		NULL);

	VERTEX_2D* pVertexPlayer2; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferPlayer2->Lock(0, 0, (void**)&pVertexPlayer2, 0);

	//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
	pVertexPlayer2[0].pos = D3DXVECTOR3(g_posPlayer2.x - 150.0f, g_posPlayer2.y - 200.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
	pVertexPlayer2[1].pos = D3DXVECTOR3(g_posPlayer2.x + 150.0f, g_posPlayer2.y - 200.0f, 0.0f); //1�Ԗڂ̒��_
	pVertexPlayer2[2].pos = D3DXVECTOR3(g_posPlayer2.x - 150.0f, g_posPlayer2.y + 200.0f, 0.0f); //2�Ԗڂ̒��_
	pVertexPlayer2[3].pos = D3DXVECTOR3(g_posPlayer2.x + 150.0f, g_posPlayer2.y + 200.0f, 0.0f); //3�Ԗڂ̒��_

	//rhw�̐ݒ�
	pVertexPlayer2[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexPlayer2[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexPlayer2[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexPlayer2[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

	//���_�J���[�̐ݒ�
	pVertexPlayer2[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
	pVertexPlayer2[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
	pVertexPlayer2[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
	pVertexPlayer2[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_

	//�e�N�X�`�����W�̐ݒ�
	//pVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
	//pVertex[1].tex = D3DXVECTOR2(0.125f, 0.0f); //1�Ԗڂ̒��_
	//pVertex[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
	//pVertex[3].tex = D3DXVECTOR2(0.125f, 1.0f); //3�Ԗڂ̒��_

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferPlayer2->Unlock();
}

//�v���C���[2�̍X�V����========================================================
void UpdatePlayer2(void)
{
	//�ϐ���錾����Ƃ���
	VERTEX_2D* pVertexPlayer2; //���_���ւ̃|�C���^

	g_nCounterAnimPlayer2++; //�A�j���[�V�����J�E���^�[�����Z�����鏈��

	//�A�j���[�V�����֘A�̏���-------------------------------------------------
	if ((g_nCounterAnimPlayer2 % 60) == 0) //��莞��(60F)�o�߂����ꍇ
	{
		g_nPatternAnimPlayer2++; //�A�j���[�V�����p�^�[���̔ԍ����X�V(���Z)����

		//�A�j���[�V�����p�^�[���̔ԍ����X�V(���Z)����
		g_nPatternAnimPlayer2 = (g_nPatternAnimPlayer2) % 10; //10�c���p�^�[����

		if(g_nPatternAnimPlayer2 > 11) //�A�j���[�V�����p�^�[���̑����𒴂����ꍇ
		{ 
			g_nPatternAnimPlayer2 = 0; //�A�j���[�V�����p�^�[���̔ԍ��������l(0)�ɖ߂�
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
		g_pVertexBufferPlayer2->Lock(0, 0, (void**)&pVertexPlayer2, 0);

		//�e�N�X�`�����W(UV)���X�V���鏈��

		//�e�N�X�`�����W�̐ݒ�
		pVertexPlayer2[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, g_nPatternAnimPlayer2 / 5 * 0.5f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
		pVertexPlayer2[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, g_nPatternAnimPlayer2 / 5 * 0.5f); //1�Ԗڂ̒��_
		pVertexPlayer2[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, g_nPatternAnimPlayer2 / 5 * 0.5 + 0.5f); //2�Ԗڂ̒��_
		pVertexPlayer2[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, g_nPatternAnimPlayer2 / 5 * 0.5 + 0.5f); //3�Ԗڂ̒��_
		

		//else if (6 <= g_nPatternAnimPlayer2 <= 10)
		//{
			//pVertexPlayer2[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 0.5f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
			//pVertexPlayer2[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 0.5f); //1�Ԗڂ̒��_
			//pVertexPlayer2[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 1.0f); //2�Ԗڂ̒��_
			//pVertexPlayer2[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 1.0f); //3�Ԗڂ̒��_
		//}

		//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
		g_pVertexBufferPlayer2->Unlock();
	}
}

//�v���C���[2�̕`�揈��-----------------------------------------------------------
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevicePlayer2; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDevicePlayer2 = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevicePlayer2->SetStreamSource(0, g_pVertexBufferPlayer2, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevicePlayer2->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevicePlayer2->SetTexture(0, g_pTexturePlayer2);

	//�|���S���̕`��
	pDevicePlayer2->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , 0�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
}

//�v���C���[2�̏I������-----------------------------------------------------------
void UninitPlayer2(void)
{
	//�e�N�X�`���̔j���@
	if (g_pTexturePlayer2 != NULL) //g_pTexturePlayer1�Ƀe�N�X�`�����ݒ肳��Ă���ꍇ�A
								   // �e�N�X�`����j�����鏈��
	{
		g_pTexturePlayer2->Release();
		g_pTexturePlayer2 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferPlayer2 != NULL)
	{
		g_pVertexBufferPlayer2->Release();
		g_pVertexBufferPlayer2 = NULL;
	}
}