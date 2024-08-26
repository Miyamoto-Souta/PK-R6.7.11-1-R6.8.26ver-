#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
//����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-enemy1.h"
#include "R6.7.11-1-explosion.h"
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-bullet.h"

//�}�N����`
#define NUM_ENEMY1 (4) //�G�̎�ނ̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureEnemy1[NUM_ENEMY1] = {}; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferEnemy1 = NULL; //���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy1[MAX_ENEMY1]; //�G�̏��
//D3DXVECTOR3 g_posEnemy1; //�G1�̈ʒu���Ǘ�����ϐ�
//D3DXVECTOR3 g_moveEnemy1; //�G1�̈ړ��ʂ��Ǘ�����ϐ�
int g_nCounterAnimEnemy1; //�A�j���[�V�����J�E���^�[
int g_nPatternAnimEnemy1; //�A�j���[�V�����p�^�[���̔ԍ�
int g_NumEnemy1 = 0; //�G1�̑������Ǘ�����ϐ�

//�G1���擾���鏈��============================================================
Enemy* GetEnemy1(void)
{
	return &g_aEnemy1[0]; //�G�̏��̐擪�A�h���X��Ԃ�
}


//�G1�̏���������==============================================================
void InitEnemy1(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceEnemy1; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountEnemy1; //�G��  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceEnemy1 = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDeviceEnemy1,
		"data\\TEXTURE\\big_fairy001.png",
		&g_apTextureEnemy1[0]);

	//�e�N�X�`���̓ǂݍ��݇A
	D3DXCreateTextureFromFile(pDeviceEnemy1,
		"data\\TEXTURE\\big_fairy002.png",
		&g_apTextureEnemy1[1]);

	//�e�N�X�`���̓ǂݍ��݇B
	D3DXCreateTextureFromFile(pDeviceEnemy1,
		"data\\TEXTURE\\big_fairy003.png",
		&g_apTextureEnemy1[2]);

	//�e�N�X�`���̓ǂݍ��݇C
	D3DXCreateTextureFromFile(pDeviceEnemy1,
		"data\\TEXTURE\\big_fairy004.png",
		&g_apTextureEnemy1[3]);

	//�e�퐔�l�̏�����
	//g_nCounterAnimEnemy1 = 0; //�A�j���[�V�����J�E���^�[������������
	//g_nPatternAnimEnemy1 = 0; //�A�j���[�V�����p�^�[���̔ԍ�������������
	g_NumEnemy1 = 0; //�G1�̑������Ǘ�����ϐ�������������

	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		g_aEnemy1[nCountEnemy1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�G1�̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};
		g_aEnemy1[nCountEnemy1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�G1�̈ړ��ʂ����������� {D3DXVECTOR3(X����, Y����, Z����)};
	}

	//�Ίp���̒������Z�o���鏈��
	//g_fLengthEnemy1 = sqrtf(ENEMY1_WIDTH * ENEMY1_WIDTH + ENEMY1_HEIGHT * ENEMY1_HEIGHT) / 2.0f; //sqrtf(�v���C���[1�̕� * �v���C���[1�̕� + �v���C���[1�̍��� * �v���C���[1�̍���)

	//�Ίp���̊p�x���Z�o���鏈��
	//g_fAngleEnemy1 = atan2f(ENEMY1_WIDTH, ENEMY1_HEIGHT); //atan2f(�v���C���[1�̕� ,�v���C���[1�̍���)

	//���_�o�b�t�@�̐���
	pDeviceEnemy1->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ENEMY1, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_�� �~ [NUM_ENEMY1]}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVertexBufferEnemy1,
		NULL);

	VERTEX_2D* pVertexEnemy1; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

	//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
		pVertexEnemy1[0].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
		pVertexEnemy1[1].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //1�Ԗڂ̒��_
		pVertexEnemy1[2].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //2�Ԗڂ̒��_
		pVertexEnemy1[3].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //3�Ԗڂ̒��_
		//��],�g��k�����g��Ȃ��ꍇ �� pVertexPlayer1[0].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};

		//rhw�̐ݒ�
		pVertexEnemy1[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexEnemy1[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexEnemy1[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexEnemy1[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

		//���_�J���[�̐ݒ�
		pVertexEnemy1[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
		pVertexEnemy1[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
		pVertexEnemy1[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
		pVertexEnemy1[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_

		//�e�N�X�`�����W�̐ݒ�
		pVertexEnemy1[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
		pVertexEnemy1[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1�Ԗڂ̒��_
		pVertexEnemy1[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
		pVertexEnemy1[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3�Ԗڂ̒��_
	}

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferEnemy1->Unlock();
}




//�G1�̍X�V����================================================================
void UpdateEnemy1(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	VERTEX_2D* pVertexEnemy1; //���_���ւ̃|�C���^
	int nCountEnemy1; //�G��  ���J�E���g���邽�߂̕ϐ�

	g_nCounterAnimEnemy1++; //�A�j���[�V�����J�E���^�[�����Z�����鏈��

	//�ړ��֘A�̏���-----------------------------------------------------------

	

	//�G1�̈ʒu���X�V���鏈�� �������͏����Ȃ�����!!��
	g_aEnemy1[0].pos.x += g_aEnemy1[0].move.x; //�G1�̌��݈ʒu��X���W��X�����̈ړ��ʂ����Z������
	g_aEnemy1[0].pos.y += g_aEnemy1[0].move.y; //�G1�̌��݈ʒu��Y���W��Y�����̈ړ��ʂ����Z������


	//���_���W�̍X�V�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

	//���_���W�̐ݒ�
	pVertexEnemy1[0].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
	pVertexEnemy1[1].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //1�Ԗڂ̒��_
	pVertexEnemy1[2].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //2�Ԗڂ̒��_
	pVertexEnemy1[3].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //3�Ԗڂ̒��_

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferEnemy1->Unlock();

	//�A�j���[�V�����֘A�̏���-------------------------------------------------
	
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

	if ((g_nCounterAnimEnemy1 % 10) == 0) //��莞��(12F)�o�߂����ꍇ
	{
		g_nPatternAnimEnemy1++; //�A�j���[�V�����p�^�[���̔ԍ����X�V(���Z)����

		//�ړ��ʂ��[����(���̏�ɗ��܂��Ă���)�ꍇ
		if (g_aEnemy1[nCountEnemy1].move.x >= -0.07f && g_aEnemy1[nCountEnemy1].move.x <= 0.07f && g_aEnemy1[nCountEnemy1].move.y >= -0.07f && g_aEnemy1[nCountEnemy1].move.y <= 0.07f)
		{
			g_nPatternAnimEnemy1--; //�A�j���[�V�����p�^�[���̔ԍ������Z����(���X�V���~�߂�����)
		}

		else //�ړ����Ă���ꍇ
		{
			/*if (g_nMoveDirection == 2) //�������Ɉړ����Ă���ꍇ
			{	//�e�N�X�`�����������ɂ����鏈��
				pVertexPlayer1[0].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
				pVertexPlayer1[1].pos = D3DXVECTOR3(g_posPlayer1.x + 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //1�Ԗڂ̒��_
				pVertexPlayer1[2].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y + 100.0f, 0.0f); //2�Ԗڂ̒��_
				pVertexPlayer1[3].pos = D3DXVECTOR3(g_posPlayer1.x + 75.0f, g_posPlayer1.y + 100.0f, 0.0f); //3�Ԗڂ̒��_
			}

			if (g_nMoveDirection == 2) //�E�����Ɉړ����Ă���ꍇ
			{	//�e�N�X�`�����E�����ɂ����鏈��
				pVertexPlayer1[0].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
				pVertexPlayer1[1].pos = D3DXVECTOR3(g_posPlayer1.x + 75.0f, g_posPlayer1.y - 100.0f, 0.0f); //1�Ԗڂ̒��_
				pVertexPlayer1[2].pos = D3DXVECTOR3(g_posPlayer1.x - 75.0f, g_posPlayer1.y + 100.0f, 0.0f); //2�Ԗڂ̒��_
				pVertexPlayer1[3].pos = D3DXVECTOR3(g_posPlayer1.x + 75.0f, g_posPlayer1.y + 100.0f, 0.0f); //3�Ԗڂ̒��_
			}*/

			/*//�A�j���[�V�����p�^�[���̔ԍ����X�V(���Z)����
			g_nPatternAnimEnemy1 = (g_nPatternAnimEnemy1) % 10; //10�c���p�^�[����

			if (g_nPatternAnimEnemy1 > 11) //�A�j���[�V�����p�^�[���̑����𒴂����ꍇ
			{
				g_nPatternAnimEnemy1 = 0; //�A�j���[�V�����p�^�[���̔ԍ��������l(0)�ɖ߂�
			}*/
		}

		//�e�N�X�`�����W(UV)���X�V���鏈��

		/*//�e�N�X�`�����W�̐ݒ�
		pVertexEnemy1[0].tex = D3DXVECTOR2(g_nPatternAnimEnemy1 * 0.2f, g_nPatternAnimEnemy1 / 5 * 0.5f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
		pVertexEnemy1[1].tex = D3DXVECTOR2(g_nPatternAnimEnemy1 * 0.2f + 0.2f, g_nPatternAnimEnemy1 / 5 * 0.5f); //1�Ԗڂ̒��_
		pVertexEnemy1[2].tex = D3DXVECTOR2(g_nPatternAnimEnemy1 * 0.2f, g_nPatternAnimEnemy1 / 5 * 0.5 + 0.5f); //2�Ԗڂ̒��_
		pVertexEnemy1[3].tex = D3DXVECTOR2(g_nPatternAnimEnemy1 * 0.2f + 0.2f, g_nPatternAnimEnemy1 / 5 * 0.5 + 0.5f); //3�Ԗڂ̒��_*/


		//else if (6 <= g_nPatternAnimPlayer2 <= 10)
		//{
			//pVertexPlayer2[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 0.5f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
			//pVertexPlayer2[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 0.5f); //1�Ԗڂ̒��_
			//pVertexPlayer2[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 1.0f); //2�Ԗڂ̒��_
			//pVertexPlayer2[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 1.0f); //3�Ԗڂ̒��_
		//}

		//�G�̏�Ԃɂ���čs���������鏈��
		for (nCountEnemy1 = 0; nCountEnemy1 < MAX_ENEMY1; nCountEnemy1++)
		{
			if (g_aEnemy1[nCountEnemy1].bUse == true) //�G���g�p����Ă���ꍇ
			{
				switch (g_aEnemy1[nCountEnemy1].state)
				{
				case ENEMYSTATE_NOMAL: //�G���ʏ��Ԃł���ꍇ
					
					/*if (��莞�Ԃ��o�߂�����)
					{
						SetBullet(g_aEnemy1[nCountEnemy1].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY); //SetBullet(�ʒu, �ړ���, �e�̎��);
					}*/
					break;
					
				case ENEMYSTATE_DAMAGE: //�G���_���[�W��Ԃł���ꍇ
					
					g_aEnemy1[nCountEnemy1].nCounterState--; //��ԊǗ��J�E���^�[��F�f�N�������g���Ă���

					if(g_aEnemy1[nCountEnemy1].nCounterState <= 0) //��ԊǗ��J�E���^�[�̐��l��0�ȉ��ɂȂ����ꍇ
					{ 
						g_aEnemy1[nCountEnemy1].state = ENEMYSTATE_NOMAL; //�G�̏�Ԃ�ʏ��Ԃɂ���

						//���_�J���[�̐ݒ�(�|���S����ʏ�F�ɖ߂�)
						pVertexEnemy1[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
						pVertexEnemy1[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
						pVertexEnemy1[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
						pVertexEnemy1[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_
					}
					break;					
				}
			}
		}

		//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
		g_pVertexBufferEnemy1->Unlock();
	}
}

//�G1�̕`�揈��========================================================
void DrawEnemy1(void)
{
	LPDIRECT3DDEVICE9 pDeviceEnemy1; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountEnemy1; //�G��  ���J�E���g���邽�߂̕ϐ�

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceEnemy1 = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceEnemy1->SetStreamSource(0, g_pVertexBufferEnemy1, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceEnemy1->SetFVF(FVF_VERTEX_2D);

	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		//�e�N�X�`���̐ݒ�
		pDeviceEnemy1->SetTexture(0, g_apTextureEnemy1[nCountEnemy1]);

		//�|���S���̕`��
		pDeviceEnemy1->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , 0�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
	}
}

//�G1�̐ݒ菈��(pos�c�o���ʒu int nType�c���)=================================
void SetEnemy1(D3DXVECTOR3 pos, int nType)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	int nCountEnemy1; //�G��  ���J�E���g���邽�߂̕ϐ�
	LPDIRECT3DDEVICE9 pDeviceEnemy1; //�f�o�C�X�ւ̃|�C���^��錾
	VERTEX_2D* pVertexEnemy1; //���_���ւ̃|�C���^

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceEnemy1 = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceEnemy1->SetStreamSource(0, g_pVertexBufferEnemy1, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferPolygon�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		pVertexEnemy1 += 4 * nCountEnemy1; //���_�f�[�^�̃|�C���^��4���i�߂�

		if (g_aEnemy1[nCountEnemy1].bUse == false) //�G���g�p����Ă��Ȃ��ꍇ
		{
			//�G�̏��̐ݒ�(�o��������ۂ̂���)
			
			//���_���W�̐ݒ�
			pVertexEnemy1[0].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
			pVertexEnemy1[1].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y - ENEMY1_HEIGHT / 2, 0.0f); //1�Ԗڂ̒��_
			pVertexEnemy1[2].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x - ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //2�Ԗڂ̒��_
			pVertexEnemy1[3].pos = D3DXVECTOR3(g_aEnemy1[nCountEnemy1].pos.x + ENEMY1_WIDTH / 2, g_aEnemy1[nCountEnemy1].pos.y + ENEMY1_HEIGHT / 2, 0.0f); //3�Ԗڂ̒��_

			g_aEnemy1[nCountEnemy1].bUse = true; //�G���g�p����Ă����Ԃɂ���
			g_aEnemy1[nCountEnemy1].pos = pos; //�G�̏o���ʒu��ݒ肷��
			g_aEnemy1[nCountEnemy1].nType = nType; //�G�̎�ނ�ݒ肷��
			g_aEnemy1[nCountEnemy1].state = ENEMYSTATE_NOMAL; //�G�̏�Ԃ�ݒ肷��
			g_aEnemy1[nCountEnemy1].nCounterState = 0; //��ԊǗ��J�E���^�[��ݒ肷��

			g_NumEnemy1++; //�G1�̑������Ǘ�����ϐ����C���N�������g(�J�E���g�A�b�v)����
			break;
		}
	}
	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferEnemy1->Unlock();
}

//�G1�̏I������-----------------------------------------------------------
void UninitEnemy1(void)
{
	int nCountEnemy1; //�G��  ���J�E���g���邽�߂̕ϐ�

	//�e�N�X�`���̔j��
	for (nCountEnemy1 = 0; nCountEnemy1 < NUM_ENEMY1; nCountEnemy1++)
	{
		if (g_apTextureEnemy1[nCountEnemy1] != NULL) //g_apTextureBackground[nCountBackGround]��
															 // �e�N�X�`�����ݒ肳��Ă���ꍇ�A�e�N�X�`����j�����鏈��
		{
			g_apTextureEnemy1[nCountEnemy1]->Release();
			g_apTextureEnemy1[nCountEnemy1] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferEnemy1 != NULL)
	{
		g_pVertexBufferEnemy1->Release();
		g_pVertexBufferEnemy1 = NULL;
	}
}

//�G1�̔�e����================================================================
inline void HitEnemy1(int nCountEnemy1, int nDamage)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceEnemy1; //�f�o�C�X�ւ̃|�C���^��錾
									 //int nCountEnemy1; //�G��  ���J�E���g���邽�߂̕ϐ�
	VERTEX_2D* pVertexEnemy1; //���_���ւ̃|�C���^

							  //�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceEnemy1 = GetDevice();

	g_aEnemy1[nCountEnemy1].nLife -= 1;

	if (g_aEnemy1[nCountEnemy1].nLife <= 0) //�G�̗̑͂�0�ȉ��ɂȂ����ꍇ
	{
		//�����̐ݒ�
		SetExplosion(g_aEnemy1[nCountEnemy1].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //�ʒu, �F

		g_aEnemy1[nCountEnemy1].bUse = false; //�G1���g�p���Ă��Ȃ���Ԃɂ���

		g_NumEnemy1--; //�G1�̑������Ǘ�����ϐ����C���N�������g(�J�E���g�_�E��)����

		if (g_NumEnemy1 <= 0) //�G�̑�����0�ȉ��ɂȂ����ꍇ
		{
			//���[�h�ݒ�(���U���g��ʂɈڍs����) �������ɒu���̂͐������Ȃ�!!
			SetMode(MODE_RESULT);
		}
	}

	else //�G�̗̑͂�0�𒴉߂��Ă���ꍇ
	{
		g_aEnemy1[nCountEnemy1].state = ENEMYSTATE_DAMAGE;
		g_aEnemy1[nCountEnemy1].nCounterState = 5; //�_���[�W��Ԃ�ێ����鎞�Ԃ�ݒ肷��

		pVertexEnemy1 += 4 * nCountEnemy1; //���_�f�[�^�̃|�C���^��4���i�߂�

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
		g_pVertexBufferEnemy1->Lock(0, 0, (void**)&pVertexEnemy1, 0);

		//���_�J���[�̐ݒ�(�|���S�����_���[�W�F�ɕύX����)
		pVertexEnemy1[0].col = D3DCOLOR_RGBA(255, 0, 0, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
		pVertexEnemy1[1].col = D3DCOLOR_RGBA(255, 0, 0, 255); //1�Ԗڂ̒��_
		pVertexEnemy1[2].col = D3DCOLOR_RGBA(255, 0, 0, 255); //2�Ԗڂ̒��_
		pVertexEnemy1[3].col = D3DCOLOR_RGBA(255, 0, 0, 255); //3�Ԗڂ̒��_

		//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
		g_pVertexBufferEnemy1->Unlock();
	}
}

//���݂̓G�̑������Ǘ����鏈��=================================================
int EnemyTotal()
{
	return g_NumEnemy1; //���݂̓G�̑�����Ԃ�
}