#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
							// ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-enemy1.h"

//�}�N����`
#define MAX_BULLET (128) //�V���b�g�e�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferBullet = NULL; //���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET]; //�V���b�g�e�̏��

//�e���擾���鏈��============================================================
Bullet* GetBullet(void)
{
	return &g_aBullet[0]; //�e�̏��̐擪�A�h���X��Ԃ�
}

//�V���b�g�e�̏���������=======================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDeviceBullet; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountBullet; //�V���b�g�e��  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceBullet = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDeviceBullet,
							  "data\\TEXTURE\\bullet000.png",
							  &g_pTextureBullet);

	//�V���b�g�e�̏��̏�����
	for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		g_aBullet[nCountBullet].pos = D3DXVECTOR3(150.0f, 450.0f, 0.0f); //�V���b�g�e�̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};
		g_aBullet[nCountBullet].move = D3DXVECTOR3(0.0f, -4.0f, 0.0f); //�V���b�g�e�̈ړ��ʂ����������� {D3DXVECTOR3(X���W, Y���W, Z���W)};
		g_aBullet[nCountBullet].nLife = MAX_LIFE; //�V���b�g�e�����ł���܂ł̎��Ԃ�ݒ肷��
		g_aBullet[nCountBullet].bUse = false; //false�̏ꍇ�A�g�p���Ă��Ȃ���ԂɂȂ�

		//���_�o�b�t�@�̐���
		pDeviceBullet->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_�� * �V���b�g�e�̍ő吔}
										  D3DUSAGE_WRITEONLY,
										  FVF_VERTEX_2D, //���_�t�H�[�}�b�g
										  D3DPOOL_MANAGED,
										  &g_pVertexBufferBullet,
										  NULL);

		VERTEX_2D* pVertexBullet; //���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
		g_pVertexBufferBullet->Lock(0, 0, (void**)&pVertexBullet, 0);

		for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
		{
			//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E

			//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
			pVertexBullet[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
			pVertexBullet[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexBullet[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //2�Ԗڂ̒��_
			pVertexBullet[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //3�Ԗڂ̒��_

			//rhw�̐ݒ�
			pVertexBullet[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexBullet[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexBullet[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
			pVertexBullet[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

			//���_�J���[�̐ݒ�
			pVertexBullet[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //0�Ԗڂ̒��_{D3DXCOLOR(��, ��, ��, �����x)};
			pVertexBullet[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //1�Ԗڂ̒��_
			pVertexBullet[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //2�Ԗڂ̒��_
			pVertexBullet[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //3�Ԗڂ̒��_

			//�e�N�X�`�����W�̐ݒ�
			pVertexBullet[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
			pVertexBullet[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexBullet[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
			pVertexBullet[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3�Ԗڂ̒��_

			pVertexBullet += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferBullet->Unlock();	
}

//�V���b�g�e�̍X�V����=========================================================
void UpdateBullet(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceBullet; //�f�o�C�X�ւ̃|�C���^��錾
	VERTEX_2D* pVertexBullet; //���_���ւ̃|�C���^
	int nCountBullet; //�V���b�g�e��  ���J�E���g���邽�߂̕ϐ�
	int nCountExplosion; //�V���b�g�e������  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceBullet = GetDevice();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferBullet->Lock(0, 0, (void**)&pVertexBullet, 0);

	for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		if(g_aBullet[nCountBullet].bUse == true) //�g�p����Ă���V���b�g�e�݂̂ɍX�V������K�p����
		{
			//�V���b�g�e�̈ʒu�̍X�V
			g_aBullet[nCountBullet].pos.y += g_aBullet[nCountBullet].move.y; //�v���C���[1�̌��݈ʒu��Y���W��Y�����̈ړ��ʂ����Z������

			//�V���b�g�e�̒��_���W�̍X�V
			pVertexBullet[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
			pVertexBullet[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexBullet[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //2�Ԗڂ̒��_
			pVertexBullet[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //3�Ԗڂ̒��_

			Player1* pPlayer1; //�v���C���[1�̏��ւ̃|�C���^
			Enemy* pEnemy1; //�G�̏��ւ̃|�C���^
			int nCountEnemy1; //�G��  ���J�E���g���邽�߂̕ϐ�

			pPlayer1 = GetPlayer1(); //�v���C���[1���擾����
								     //�v���C���[1�̏��ւ̐擪�A�h���X����������
			pEnemy1 = GetEnemy1(); //�G���擾����
								   //�G�̏��ւ̐擪�A�h���X����������

			for (nCountEnemy1 = 0; nCountEnemy1 < MAX_ENEMY1; nCountEnemy1++, pEnemy1++)
			{
				if (pEnemy1->bUse == true) //�G���g�p����Ă���ꍇ
				{
					if (g_aBullet[nCountBullet].type == BULLETTYPE_PLAYER1) //���̒e���v���C���[1�̒e�ł���ꍇ
					{
						if (g_aBullet[nCountBullet].pos.x >= (pEnemy1->pos.x - (ENEMY1_WIDTH / 2)) && g_aBullet[nCountBullet].pos.x <= (pEnemy1->pos.x + (ENEMY1_WIDTH / 2)) && g_aBullet[nCountBullet].pos.y >= (pEnemy1->pos.y - (ENEMY1_HEIGHT / 2)) && g_aBullet[nCountBullet].pos.y <= (pEnemy1->pos.y + (ENEMY1_HEIGHT / 2))) //�V���b�g�e���G�ɓ��������ꍇ
							  // ���Ēe��X���W >= �G�̍��[ && ���Ēe��X���W <= �G�̉E�[ && ���Ēe��Y���W >= �G�̏�[ && ���Ēe��Y���W <= �G�̉��[
						{
							//�G�̔�e����
							HitEnemy1(nCountEnemy1, 1); //�G����e�����Ƃ���nDamage�̒l��1���炷

							//�����̐ݒ�
							SetExplosion(g_aBullet[nCountBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //�ʒu, �F

							pEnemy1->bUse = false; //�G���g�p���Ă��Ȃ���Ԃɂ���
							g_aBullet[nCountBullet].bUse = false; //�V���b�g�e���g�p���Ă��Ȃ���Ԃɂ���
						}
					}

					else if (g_aBullet[nCountBullet].type == BULLETTYPE_ENEMY) //���̒e���G�̒e�ł���ꍇ
					{
						if (g_aBullet[nCountBullet].pos.x >= (pPlayer1->pos.x - (PLAYER1_WIDTH / 2)) && g_aBullet[nCountBullet].pos.x <= (pPlayer1->pos.x + (PLAYER1_WIDTH / 2)) && g_aBullet[nCountBullet].pos.y >= (pPlayer1->pos.y - (PLAYER1_HEIGHT / 2)) && g_aBullet[nCountBullet].pos.y <= pPlayer1->pos.y + ((PLAYER1_HEIGHT / 2))) //�G�e���v���C���[1�ɓ��������ꍇ
							  // �G�e��X���W >= �v���C���[1�̍��[ && �G�e��X���W <= �v���C���[1�̉E�[ && �G�e��Y���W >= �v���C���[1�̏�[ && �G�e��Y���W <= �v���C���[1�̉��[
						{
							//�����̐ݒ�
							SetExplosion(g_aBullet[nCountBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //�ʒu, �F

							g_aBullet[nCountBullet].bUse = false; //�V���b�g�e���g�p���Ă��Ȃ���Ԃɂ���
						}
					}
				}
			}

			//�V���b�g�e���g�p���Ă��Ȃ���Ԃɂ��鏈��-------------------------------------
			
			//��ʒ[�̏����[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E

			//�V���b�g�e����ʂ̏�[�ɓ��������ꍇ
			if (g_aBullet[nCountBullet].pos.y <= 20)
			{
				g_aBullet[nCountBullet].bUse = false; //�V���b�g�e���g�p���Ă��Ȃ���Ԃɂ���
			}

			//�V���b�g�e����ʂ̍��[�ɓ��������ꍇ
			else if (g_aBullet[nCountBullet].pos.x <= 20)
			{
				g_aBullet[nCountBullet].bUse = false; //�V���b�g�e���g�p���Ă��Ȃ���Ԃɂ���
			}

			//�V���b�g�e����ʂ̉E�[�ɓ��������ꍇ
			else if (g_aBullet[nCountBullet].pos.x >= SCREEN_WIDTH - 20)
			{
				g_aBullet[nCountBullet].bUse = false; //�V���b�g�e���g�p���Ă��Ȃ���Ԃɂ���
			}

			//�V���b�g�e����ʂ̉��[�ɓ��������ꍇ
			else if (g_aBullet[nCountBullet].pos.y >= SCREEN_HEIGHT - 20)
			{
				g_aBullet[nCountBullet].bUse = false; //�V���b�g�e���g�p���Ă��Ȃ���Ԃɂ���
			}

			//�V���b�g�e����������Ă���̎��Ԃ��v������
			g_aBullet[nCountBullet].nLife--;

			if (g_aBullet[nCountBullet].nLife < 0) //�V���b�g�e�����ł���܂ł̎��Ԃ𒴉߂����ꍇ
			{
				//�V���b�g�e�����̐ݒ�
				SetExplosion(g_aBullet[nCountBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //�ʒu,�F

				g_aBullet[nCountBullet].bUse = false; //�V���b�g�e���g�p���Ă��Ȃ���Ԃɂ���
			}
		}
		pVertexBullet += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferBullet->Unlock();
}

//�V���b�g�e�̕`�揈��=========================================================
void DrawBullet(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceBullet; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountBullet; //�V���b�g�e��  ���J�E���g���邽�߂̕ϐ�

	VERTEX_2D* pVertexBullet; //���_���ւ̃|�C���^

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceBullet = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceBullet->SetStreamSource(0, g_pVertexBufferBullet, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceBullet->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDeviceBullet->SetTexture(0, g_pTextureBullet);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferBullet->Lock(0, 0, (void**)&pVertexBullet, 0);

	for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == true) //�g�p����Ă���V���b�g�e�݂̂ɕ`�揈����K�p����
		{
			//�|���S���̕`��
			pDeviceBullet->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountBullet * 4, 2);
			//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , nCountBullet * 4�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferBullet->Unlock();
}

//�V���b�g�e�̐ݒ菈��=========================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
//pos�c���ˈʒu move�c�ړ��� nLife�c�e�����ł���܂ł̎��� type�c�e�̎��
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceBullet; //�f�o�C�X�ւ̃|�C���^��錾
	VERTEX_2D* pVertexBullet; //���_���ւ̃|�C���^
	int nCountBullet; //�V���b�g�e��  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceBullet = GetDevice();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferBullet->Lock(0, 0, (void**)&pVertexBullet, 0);

	for (nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == false) //�g�p����Ă��Ȃ��V���b�g�e�݂̂ɍX�V������K�p����
		{
			pVertexBullet += 4 * nCountBullet;

			g_aBullet[nCountBullet].pos = pos;

			//���_���W�̐ݒ�
			pVertexBullet[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
			pVertexBullet[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 110.0f, 0.0f); //1�Ԗڂ̒��_
			pVertexBullet[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //2�Ԗڂ̒��_
			pVertexBullet[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10.0f, g_aBullet[nCountBullet].pos.y - 90.0f, 0.0f); //3�Ԗڂ̒��_
			g_aBullet[nCountBullet].move = move;
			g_aBullet[nCountBullet].nLife = MAX_LIFE; //�V���b�g�e�����ł���܂ł̎���
			g_aBullet[nCountBullet].bUse = true; //true�̏ꍇ�A�g�p���Ă����ԂɂȂ�

			break;
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferBullet->Unlock();
}

//�V���b�g�e�̏I������=========================================================
void UninitBullet(void)
{
	//�e�N�X�`���̔j���@
	if (g_pTextureBullet != NULL) //g_pTexturePolygon1�Ƀe�N�X�`�����ݒ肳��Ă���ꍇ�A
								   // �e�N�X�`����j�����鏈��
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferBullet != NULL)
	{
		g_pVertexBufferBullet->Release();
		g_pVertexBufferBullet = NULL;
	}
}