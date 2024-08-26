#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
							// ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-enemy1.h"
#include "R6.7.11-1-effect.h"

//�}�N����`
#define MAX_EFFECT (4096) //�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXCOLOR col; //���_�J���[
	float fRadius; //�G�t�F�N�g�̔��a(�傫��)
	int nLife; //����(�G�t�F�N�g�����ł���܂ł̎���)
	bool bUse; //�g�p���Ă��邩�ǂ���
} Effect;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferEffect = NULL; //���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT]; //�G�t�F�N�g�̏��

//�G�t�F�N�g�̏���������=======================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDeviceEffect; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountEffect; //�G�t�F�N�g��  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceEffect = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDeviceEffect,
							  "data\\TEXTURE\\effect000.jpg",
							  &g_pTextureEffect);

	//�G�t�F�N�g�̏��̏�����
	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		g_aEffect[nCountEffect].pos = D3DXVECTOR3(150.0f, 450.0f, 0.0f); //�G�t�F�N�g�̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};
	    g_aEffect[nCountEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //�G�t�F�N�g�̐F������������ {D3DXCOLOR(��, ��, ��, �����x)};
		g_aEffect[nCountEffect].nLife = MAX_LIFE; //�G�t�F�N�g�����ł���܂ł̎��Ԃ�ݒ肷��
		g_aEffect[nCountEffect].bUse = false; //false�̏ꍇ�A�g�p���Ă��Ȃ���ԂɂȂ�

		//���_�o�b�t�@�̐���
		pDeviceEffect->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_�� * �V���b�g�e�̍ő吔}
										  D3DUSAGE_WRITEONLY,
										  FVF_VERTEX_2D, //���_�t�H�[�}�b�g
										  D3DPOOL_MANAGED,
										  &g_pVertexBufferEffect,
										  NULL);

		VERTEX_2D* pVertexEffect; //���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
		g_pVertexBufferEffect->Lock(0, 0, (void**)&pVertexEffect, 0);

		for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
		{
			//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E

			//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
			pVertexEffect[0].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x - 10.0f, g_aEffect[nCountEffect].pos.y - 110.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
			pVertexEffect[1].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x + 10.0f, g_aEffect[nCountEffect].pos.y - 110.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexEffect[2].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x - 10.0f, g_aEffect[nCountEffect].pos.y - 90.0f, 0.0f); //2�Ԗڂ̒��_
			pVertexEffect[3].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x + 10.0f, g_aEffect[nCountEffect].pos.y - 90.0f, 0.0f); //3�Ԗڂ̒��_

			//rhw�̐ݒ�
			pVertexEffect[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexEffect[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexEffect[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexEffect[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

			//���_�J���[�̐ݒ�
			pVertexEffect[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //0�Ԗڂ̒��_{D3DXCOLOR(��, ��, ��, �����x)};
			pVertexEffect[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //1�Ԗڂ̒��_
			pVertexEffect[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //2�Ԗڂ̒��_
			pVertexEffect[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //3�Ԗڂ̒��_

			//�e�N�X�`�����W�̐ݒ�
			pVertexEffect[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
			pVertexEffect[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexEffect[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
			pVertexEffect[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3�Ԗڂ̒��_

			pVertexEffect += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferEffect->Unlock();
}

//�G�t�F�N�g�̍X�V����=========================================================
void UpdateEffect(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceEffect; //�f�o�C�X�ւ̃|�C���^��錾
	VERTEX_2D* pVertexEffect; //���_���ւ̃|�C���^
	int nCountEffect; //�G�t�F�N�g��  ���J�E���g���邽�߂̕ϐ�
	int nCountExplosion; //�V���b�g�e������  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceEffect = GetDevice();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferEffect->Lock(0, 0, (void**)&pVertexEffect, 0);

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if(g_aEffect[nCountEffect].bUse == true) //�g�p����Ă���G�t�F�N�g�݂̂ɍX�V������K�p����
		{
			//���_�J���[�̐ݒ�(�X�V)
			pVertexEffect[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //0�Ԗڂ̒��_{D3DXCOLOR(��, ��, ��, �����x)};
			pVertexEffect[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //1�Ԗڂ̒��_
			pVertexEffect[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //2�Ԗڂ̒��_
			pVertexEffect[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //3�Ԗڂ̒��_

			//���_���W�̐ݒ�(�X�V)
			pVertexEffect[0].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x - 10.0f, g_aEffect[nCountEffect].pos.y - 110.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
			pVertexEffect[1].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x + 10.0f, g_aEffect[nCountEffect].pos.y - 110.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexEffect[2].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x - 10.0f, g_aEffect[nCountEffect].pos.y - 90.0f, 0.0f); //2�Ԗڂ̒��_
			pVertexEffect[3].pos = D3DXVECTOR3(g_aEffect[nCountEffect].pos.x + 10.0f, g_aEffect[nCountEffect].pos.y - 90.0f, 0.0f); //3�Ԗڂ̒��_

			Player1* pPlayer1; //�v���C���[1�̏��ւ̃|�C���^
			Enemy* pEnemy1; //�G�̏��ւ̃|�C���^
			int nCountEnemy1; //�G��  ���J�E���g���邽�߂̕ϐ�

			pPlayer1 = GetPlayer1(); //�v���C���[1���擾����
								     //�v���C���[1�̏��ւ̐擪�A�h���X����������
			pEnemy1 = GetEnemy1(); //�G���擾����
								   //�G�̏��ւ̐擪�A�h���X����������

			//�G�t�F�N�g���g�p���Ă��Ȃ���Ԃɂ��鏈��-------------------------------------

			//�G�t�F�N�g����������Ă���̎��Ԃ��v������
			g_aEffect[nCountEffect].nLife--;

			if (g_aEffect[nCountEffect].nLife < 0) //�V���b�g�e�����ł���܂ł̎��Ԃ𒴉߂����ꍇ
			{
				g_aEffect[nCountEffect].bUse = false; //�G�t�F�N�g���g�p���Ă��Ȃ���Ԃɂ���
			}
		}
		pVertexEffect += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferEffect->Unlock();
}

//�G�t�F�N�g�̕`�揈��=========================================================
void DrawEffect(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceEffect; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountEffect; //�V���b�g�e��  ���J�E���g���邽�߂̕ϐ�

	VERTEX_2D* pVertexEffect; //���_���ւ̃|�C���^

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceEffect = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceEffect->SetStreamSource(0, g_pVertexBufferEffect, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceEffect->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDeviceEffect->SetTexture(0, g_pTextureEffect);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferEffect->Lock(0, 0, (void**)&pVertexEffect, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDeviceEffect->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //�u�����h���@
	pDeviceEffect->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //
	pDeviceEffect->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); //

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if (g_aEffect[nCountEffect].bUse == true) //�g�p����Ă���V���b�g�e�݂̂ɕ`�揈����K�p����
		{
			//�|���S���̕`��
			pDeviceEffect->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountEffect * 4, 2);
			//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , nCountEffect * 4�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferEffect->Unlock();

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDeviceEffect->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //�u�����h���@
	pDeviceEffect->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //
	pDeviceEffect->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //
}

//�G�t�F�N�g�̐ݒ菈��=========================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
//pos�c�ʒu col�c���_�J���[ fRadius�c�G�t�F�N�g�̔��a(�傫��) nLife�c�G�t�F�N�g�����ł���܂ł̎���
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	//LPDIRECT3DDEVICE9 pDeviceEffect; //�f�o�C�X�ւ̃|�C���^��錾
	//VERTEX_2D* pVertexEffect; //���_���ւ̃|�C���^
	int nCountEffect; //�G�t�F�N�g��  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	//pDeviceEffect = GetDevice();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	//g_pVertexBufferEffect->Lock(0, 0, (void**)&pVertexEffect, 0);

	for (nCountEffect = 0; nCountEffect < MAX_EFFECT; nCountEffect++)
	{
		if (g_aEffect[nCountEffect].bUse == false) //�g�p����Ă��Ȃ��G�t�F�N�g�݂̂ɍX�V������K�p����
		{
			g_aEffect[nCountEffect].pos = pos; //�ʒu
			g_aEffect[nCountEffect].col = col; //���_�J���[�̐ݒ�(�X�V)
			g_aEffect[nCountEffect].fRadius = fRadius; //���_���W�̐ݒ�(�X�V)
			g_aEffect[nCountEffect].nLife = nLife; //����(�G�t�F�N�g�����ł���܂ł̎���)
			g_aEffect[nCountEffect].bUse = true; //�g�p���Ă��邩�ǂ���

			break;
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	//g_pVertexBufferEffect->Unlock();
}

//�G�t�F�N�g�̏I������=========================================================
void UninitEffect(void)
{
	//�e�N�X�`���̔j���@
	if (g_pTextureEffect != NULL) //g_pTextureEffect�Ƀe�N�X�`�����ݒ肳��Ă���ꍇ�A
								   // �e�N�X�`����j�����鏈��
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferEffect != NULL)
	{
		g_pVertexBufferEffect->Release();
		g_pVertexBufferEffect = NULL;
	}
}