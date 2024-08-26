#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
							// ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-player1.h"

//�}�N����`
#define MAX_EXPLOSION (128) //�V���b�g�e�����̍ő吔

//�V���b�g�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXCOLOR col; //�F
	int nCounterAnimExplosion; //�A�j���[�V�����J�E���^�[
	int nPatternAnimExplosion; //�A�j���[�V�����p�^�[���̔ԍ�
	bool bUse; //�g�p���Ă��邩�ǂ���
} Explosion;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferExplosion = NULL; //���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION]; //�V���b�g�e�����̏��

//�V���b�g�e�����̏���������=======================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDeviceExplosion; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountExplosion; //�V���b�g�e������  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceExplosion = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDeviceExplosion,
							  "data\\TEXTURE\\explosion000.png",
							  &g_pTextureExplosion);

	//�V���b�g�e�����̏��̏�����
	for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		g_aExplosion[nCountExplosion].pos = D3DXVECTOR3(150.0f, 450.0f, 0.0f); //�V���b�g�e�����̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};
		g_aExplosion[nCountExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //�V���b�g�e�����̐F������������ {D3DXCOLOR(��, ��, ��, �����x)};
		g_aExplosion[nCountExplosion].bUse = false; //false�̏ꍇ�A�g�p���Ă��Ȃ���ԂɂȂ�

		//���_�o�b�t�@�̐���
		pDeviceExplosion->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_�� * �V���b�g�e�̍ő吔}
										     D3DUSAGE_WRITEONLY,
										     FVF_VERTEX_2D, //���_�t�H�[�}�b�g
										     D3DPOOL_MANAGED,
										     &g_pVertexBufferExplosion,
										     NULL);

		VERTEX_2D* pVertexExplosion; //���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
		g_pVertexBufferExplosion->Lock(0, 0, (void**)&pVertexExplosion, 0);

		for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
		{
			//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E

			//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
			pVertexExplosion[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
			pVertexExplosion[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexExplosion[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //2�Ԗڂ̒��_
			pVertexExplosion[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //3�Ԗڂ̒��_

			//rhw�̐ݒ�
			pVertexExplosion[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexExplosion[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexExplosion[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexExplosion[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

			//���_�J���[�̐ݒ�
			pVertexExplosion[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //0�Ԗڂ̒��_{D3DXCOLOR(��, ��, ��, �����x)};
			pVertexExplosion[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //1�Ԗڂ̒��_
			pVertexExplosion[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //2�Ԗڂ̒��_
			pVertexExplosion[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //3�Ԗڂ̒��_

			//�e�N�X�`�����W�̐ݒ�
			pVertexExplosion[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
			pVertexExplosion[1].tex = D3DXVECTOR2(0.125f, 0.0f); //1�Ԗڂ̒��_
			pVertexExplosion[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
			pVertexExplosion[3].tex = D3DXVECTOR2(0.125f, 1.0f); //3�Ԗڂ̒��_

			pVertexExplosion += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferExplosion->Unlock();
}

//�V���b�g�e�����̍X�V����=========================================================
void UpdateExplosion(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceExplosion; //�f�o�C�X�ւ̃|�C���^��錾
	VERTEX_2D* pVertexExplosion; //���_���ւ̃|�C���^
	int nCountExplosion; //�V���b�g�e��  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceExplosion = GetDevice();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferExplosion->Lock(0, 0, (void**)&pVertexExplosion, 0);

	for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if(g_aExplosion[nCountExplosion].bUse == true) //�g�p����Ă��锚���݂̂ɍX�V������K�p����
		{
			if ((g_aExplosion[nCountExplosion].nCounterAnimExplosion % 60) == 0) //��莞��(60F)�o�߂����ꍇ
			{
				g_aExplosion[nCountExplosion].nPatternAnimExplosion++; //�A�j���[�V�����p�^�[���̔ԍ����X�V(���Z)����

				//�A�j���[�V�����p�^�[���̔ԍ����X�V(���Z)����
				g_aExplosion[nCountExplosion].nPatternAnimExplosion = (g_aExplosion[nCountExplosion].nPatternAnimExplosion) % 9; //9�c���p�^�[����

				if (g_aExplosion[nCountExplosion].nPatternAnimExplosion > 9) //�A�j���[�V�����p�^�[���̑����𒴂����ꍇ
				{
					g_aExplosion[nCountExplosion].bUse == false; //�������g�p���Ă��Ȃ���Ԃɂ���
				}

				//�V���b�g�e�����̈ʒu�̍X�V
				//g_aExplosion[nCountExplosion].pos.y += g_aExplosion[nCountExplosion].move.y; //�v���C���[1�̌��݈ʒu��Y���W��Y�����̈ړ��ʂ����Z������

				//�V���b�g�e�����̒��_���W�̍X�V
				pVertexExplosion[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
				pVertexExplosion[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //1�Ԗڂ̒��_
				pVertexExplosion[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //2�Ԗڂ̒��_
				pVertexExplosion[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //3�Ԗڂ̒��_

				//�e�N�X�`�����W(UV)���X�V���鏈��
				pVertexExplosion[0].tex = D3DXVECTOR2(g_aExplosion[nCountExplosion].nPatternAnimExplosion * 0.0f, 1.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
				pVertexExplosion[1].tex = D3DXVECTOR2(g_aExplosion[nCountExplosion].nPatternAnimExplosion * 0.125f, 1.0f); //1�Ԗڂ̒��_
				pVertexExplosion[2].tex = D3DXVECTOR2(g_aExplosion[nCountExplosion].nPatternAnimExplosion * 0.0f, 1.0f); //2�Ԗڂ̒��_
				pVertexExplosion[3].tex = D3DXVECTOR2(g_aExplosion[nCountExplosion].nPatternAnimExplosion * 0.125f, 1.0f); //3�Ԗڂ̒��_
			
				//��ʒ[�̏����[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E

			}
		}
		pVertexExplosion += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferExplosion->Unlock();
}

//�V���b�g�e�����̕`�揈��=========================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDeviceExplosion; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountExplosion; //�V���b�g�e������  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceExplosion = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceExplosion->SetStreamSource(0, g_pVertexBufferExplosion, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferExplosion�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceExplosion->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDeviceExplosion->SetTexture(0, g_pTextureExplosion);

	for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if (g_aExplosion[nCountExplosion].bUse == true) //�g�p����Ă���V���b�g�e�݂̂ɕ`�揈����K�p����
		{
			//�|���S���̕`��
			pDeviceExplosion->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountExplosion * 4, 2);
			//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , nCountBullet * 4�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
		}
	}
}

//�V���b�g�e�����̐ݒ菈��=========================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceExplosion; //�f�o�C�X�ւ̃|�C���^��錾
	VERTEX_2D* pVertexExplosion; //���_���ւ̃|�C���^
	int nCountExplosion; //�V���b�g�e������  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceExplosion = GetDevice();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferExplosion->Lock(0, 0, (void**)&pVertexExplosion, 0);

	for (nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if (g_aExplosion[nCountExplosion].bUse == false) //�g�p����Ă��Ȃ������݂̂ɍX�V������K�p����
		{
			pVertexExplosion += 4 * nCountExplosion;

			g_aExplosion[nCountExplosion].pos = pos;

			g_aExplosion[nCountExplosion].nCounterAnimExplosion = 0; //�A�j���[�V�����J�E���^�[������������
			g_aExplosion[nCountExplosion].nPatternAnimExplosion = 0; //�A�j���[�V�����p�^�[���̔ԍ�������������

			//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
			pVertexExplosion[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
			pVertexExplosion[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 110.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexExplosion[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //2�Ԗڂ̒��_
			pVertexExplosion[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 10.0f, g_aExplosion[nCountExplosion].pos.y - 90.0f, 0.0f); //3�Ԗڂ̒��_

			//rhw�̐ݒ�
			pVertexExplosion[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexExplosion[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexExplosion[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexExplosion[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

			//���_�J���[�̐ݒ�
			pVertexExplosion[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //0�Ԗڂ̒��_{D3DXCOLOR(��, ��, ��, �����x)};
			pVertexExplosion[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //1�Ԗڂ̒��_
			pVertexExplosion[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //2�Ԗڂ̒��_
			pVertexExplosion[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //3�Ԗڂ̒��_

			//�e�N�X�`�����W�̐ݒ�
			pVertexExplosion[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
			pVertexExplosion[1].tex = D3DXVECTOR2(0.125f, 0.0f); //1�Ԗڂ̒��_
			pVertexExplosion[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
			pVertexExplosion[3].tex = D3DXVECTOR2(0.125f, 1.0f); //3�Ԗڂ̒��_

			break;
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferExplosion->Unlock();
}

//�V���b�g�e�̏I������=========================================================
void UninitExplosion(void)
{
	//�e�N�X�`���̔j���@
	if (g_pTextureExplosion != NULL) //g_pTextureExplosion�Ƀe�N�X�`�����ݒ肳��Ă���ꍇ�A
								     // �e�N�X�`����j�����鏈��
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferExplosion != NULL)
	{
		g_pVertexBufferExplosion->Release();
		g_pVertexBufferExplosion = NULL;
	}
}