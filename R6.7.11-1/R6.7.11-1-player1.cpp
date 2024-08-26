#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
//����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������
#include "R6.7.11-1-player1.h"
#include "R6.7.11-1-input.h"
#include "R6.7.11-1-bullet.h"
#include "R6.7.11-1-explosion.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferPlayer1 = NULL; //���_�o�b�t�@�ւ̃|�C���^
Player1 g_Player1; //�v���C���[1�̏����Ǘ�����ϐ�
int g_nCounterAnimPlayer1; //�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer1; //�A�j���[�V�����p�^�[���̔ԍ�
//D3DXVECTOR3 g_posPlayer1; //�v���C���[1�̈ʒu���Ǘ�����ϐ�
//D3DXVECTOR3 g_movePlayer1; //�v���C���[1�̈ړ��ʂ��Ǘ�����ϐ�
//D3DXVECTOR3 g_moveBulletPlayer1; //�v���C���[1�̃V���b�g�̈ړ��ʂ��Ǘ�����ϐ�
//D3DXVECTOR3 g_rotPlayer1; //�v���C���[1�̌������Ǘ�����ϐ�
//float g_fLengthPlayer1; //�v���C���[1�̑Ίp���̒���(�g��k���p)���Ǘ�����ϐ�
//float g_fAnglePlayer1; //�v���C���[1�̑Ίp���̊p�x(��]�p)���Ǘ�����ϐ�
int g_nMoveDirection; //�ړ������𔻕ʂ��邽�߂̕ϐ���錾

//�v���C���[1���擾���鏈��============================================================
Player1* GetPlayer1(void)
{
	return &g_Player1; //�v���C���[1�̏��̐擪�A�h���X��Ԃ�
}

//�v���C���[1�̏���������======================================================
void InitPlayer1(void)
{
	LPDIRECT3DDEVICE9 pDevicePlayer1; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDevicePlayer1 = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDevicePlayer1,
		"data\\TEXTURE\\runningman100.png",
		&g_pTexturePlayer1);

	//�e�퐔�l�̏�����
	g_nCounterAnimPlayer1 = 0; //�A�j���[�V�����J�E���^�[������������
	g_nPatternAnimPlayer1 = 0; //�A�j���[�V�����p�^�[���̔ԍ�������������
	g_Player1.pos = D3DXVECTOR3(150.0f, 450.0f, 0.0f); //�v���C���[1�̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};
	g_Player1.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�v���C���[1�̈ړ��ʂ����������� {D3DXVECTOR3(X����, Y����, Z����)};
	g_Player1.movebullet = D3DXVECTOR3(0.0f, 4.0f, 0.0f); //�v���C���[1�̃V���b�g�̈ړ��ʂ����������� {D3DXVECTOR3(X����, Y����, Z����)};
	g_Player1.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�v���C���[1�̌��������������� {D3DXVECTOR3(X����, Y����, Z����)};

	//�Ίp���̒������Z�o���鏈��
	g_Player1.Length = sqrtf(PLAYER1_WIDTH * PLAYER1_WIDTH + PLAYER1_HEIGHT * PLAYER1_HEIGHT) / 2.0f; //sqrtf(�v���C���[1�̕� * �v���C���[1�̕� + �v���C���[1�̍��� * �v���C���[1�̍���)

	//�Ίp���̊p�x���Z�o���鏈��
	g_Player1.Angle = atan2f(PLAYER1_WIDTH, PLAYER1_HEIGHT); //atan2f(�v���C���[1�̕� ,�v���C���[1�̍���)

	//���_�o�b�t�@�̐���
	pDevicePlayer1->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_��}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVertexBufferPlayer1,
		NULL);

	VERTEX_2D* pVertexPlayer1; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferPlayer1->Lock(0, 0, (void**)&pVertexPlayer1, 0);

	//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
	pVertexPlayer1[0].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z - (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0�Ԗڂ̒��_��X���W g_posPlayer1.x + sinf(���� + �p�x(���n�_ + �Ίp���̊p�x)) * ����
	pVertexPlayer1[0].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z - (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0�Ԗڂ̒��_��Y���W g_posPlayer1.y + cosf(���� + �p�x) * ����
	pVertexPlayer1[0].pos.z = 0.0f; //0�Ԗڂ̒��_��Z���W
	pVertexPlayer1[1].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0�Ԗڂ̒��_��X���W g_posPlayer1.x + sinf(���� + �p�x(���n�_ + �Ίp���̊p�x)) * ����
	pVertexPlayer1[1].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0�Ԗڂ̒��_��Y���W g_posPlayer1.y + cosf(���� + �p�x) * ����
	pVertexPlayer1[1].pos.z = 0.0f; //0�Ԗڂ̒��_��Z���W
	pVertexPlayer1[2].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (0.0f - g_Player1.Angle)) * g_Player1.Length; //2�Ԗڂ̒��_��X���W g_posPlayer1.x + sinf(���� + �p�x(���n�_ + �Ίp���̊p�x)) * ����
	pVertexPlayer1[2].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (0.0f - g_Player1.Angle)) * g_Player1.Length; //2�Ԗڂ̒��_��Y���W g_posPlayer1.y + cosf(���� + �p�x) * ����
	pVertexPlayer1[2].pos.z = 0.0f; //2�Ԗڂ̒��_��Z���W
	pVertexPlayer1[3].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (0.0f + g_Player1.Angle)) * g_Player1.Length; //3�Ԗڂ̒��_��X���W g_posPlayer1.x + sinf(���� + �p�x(���n�_ + �Ίp���̊p�x)) * ����
	pVertexPlayer1[3].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (0.0f + g_Player1.Angle)) * g_Player1.Length; //3�Ԗڂ̒��_��Y���W g_posPlayer1.y + cosf(���� + �p�x) * ����
	pVertexPlayer1[3].pos.z = 0.0f; //3�Ԗڂ̒��_��Z���W
	//��],�g��k�����g��Ȃ��ꍇ �� pVertexPlayer1[0].pos = D3DXVECTOR3(g_Player1.pos.x - 75.0f, g_Player1.pos.y - 100.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};

	//rhw�̐ݒ�
	pVertexPlayer1[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexPlayer1[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexPlayer1[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexPlayer1[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

	//���_�J���[�̐ݒ�
	pVertexPlayer1[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
	pVertexPlayer1[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
	pVertexPlayer1[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
	pVertexPlayer1[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_

	//�e�N�X�`�����W�̐ݒ�
	//pVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
	//pVertex[1].tex = D3DXVECTOR2(0.125f, 0.0f); //1�Ԗڂ̒��_
	//pVertex[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
	//pVertex[3].tex = D3DXVECTOR2(0.125f, 1.0f); //3�Ԗڂ̒��_

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferPlayer1->Unlock();
}

//�v���C���[1�̍X�V����========================================================
void UpdatePlayer1(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	VERTEX_2D* pVertexPlayer1; //���_���ւ̃|�C���^

	g_nCounterAnimPlayer1++; //�A�j���[�V�����J�E���^�[�����Z�����鏈��

	//�ړ��֘A�̏���-----------------------------------------------------------

	//��c1 �������c2 �E�����c3 ���c4 ��~�c5

	//g_movePlayer1 = D3DXVECTOR3(1.0f, 1.0f, 0.0f); //�v���C���[1�̈ړ��ʂ�ݒ肷�� {D3DXVECTOR3(X����, Y����, Z����)};

	//�v���C���[1��Y���W���|(��)�����Ɉړ�����
	if (GetKeyboardPress(DIK_W) || GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_NUMPAD8) == true) //W�L�[,���L�[,NUM�p�b�h��8�L�[�������ꂽ�ꍇ
	{
		//A�L�[,���L�[,NUM�p�b�h��4�L�[�������ɉ�����Ă���ꍇ
		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_NUMPAD4) == true)
		{ 
			g_Player1.move.x = sinf(-D3DX_PI * 0.75f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.75f) * 1.0f; //�v���C���[1��X,Y���W���|(����)�����Ɉړ�����
			g_nMoveDirection = 2;
		}

		//D�L�[,���L�[,NUM�p�b�h��6�L�[�������ɉ�����Ă���ꍇ
		else if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_NUMPAD6) == true)
		{
			g_Player1.move.x = sinf(D3DX_PI * 0.75f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.75f) * 1.0f; //�v���C���[1��X���W���{,Y���W���|(�E��)�����Ɉړ�����
			g_nMoveDirection = 3;
		}

		//S�L�[,���L�[,NUM�p�b�h��2�L�[�������ɉ�����Ă���ꍇ
		else if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_NUMPAD2) == true)
		{
			g_Player1.move.x = 0.0f, g_Player1.move.y = 0.0f; //���̏�ɗ��܂�
			g_nMoveDirection = 5;
		}

		//����ȊO(W�L�[,���L�[,NUM�p�b�h��8�L�[�݂̂�������Ă���ꍇ)
		else
		{
			g_Player1.move.y = cosf(D3DX_PI * 1.0) * 1.0f;
			g_nMoveDirection = 1;
		}

		//�L�[�̎�ނ�16�S�ē���邱��!!
	}

	//�v���C���[1��X���W���|(��)�����Ɉړ�����
	else if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_NUMPAD4) == true) //A�L�[,���L�[,NUM�p�b�h��4�L�[�������ꂽ�ꍇ
	{
		//S�L�[,���L�[,NUM�p�b�h��2�L�[�������ɉ�����Ă���ꍇ
		if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_NUMPAD2) == true)
		{
			g_Player1.move.x = sinf(-D3DX_PI * 0.25f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.25f) * 1.0f; //�v���C���[1��X���W���|,Y���W���{(����)�����Ɉړ�����
			g_nMoveDirection = 2;
		}

		//D�L�[,���L�[,NUM�p�b�h��6�L�[�������ɉ�����Ă���ꍇ
		else if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_NUMPAD6) == true)
		{
			g_Player1.move.x = 0.0f, g_Player1.move.y = 0.0f; //���̏�ɗ��܂�
			g_nMoveDirection = 5;
		}

		//����ȊO(A�L�[,���L�[,NUM�p�b�h��4�L�[�݂̂�������Ă���ꍇ)
		else
		{
			g_Player1.move.x = sinf(-D3DX_PI * 0.50) * 1.0f;
			g_nMoveDirection = 2;
		}
	}

	//�v���C���[1��X���W���{(�E)�����Ɉړ�����
	else if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_NUMPAD6) == true) //D�L�[,���L�[,NUM�p�b�h��6�L�[�������ꂽ�ꍇ
	{
		//S�L�[,���L�[,NUM�p�b�h��2�L�[�������ɉ�����Ă���ꍇ
		if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_NUMPAD2) == true)
		{
			g_Player1.move.x = sinf(D3DX_PI * 0.25f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.25f) * 1.0f; //�v���C���[1��X,Y���W���{(�E��)�����Ɉړ�����
			g_nMoveDirection = 3;
		}

		//����ȊO(D�L�[,���L�[,NUM�p�b�h��6�L�[�݂̂�������Ă���ꍇ)
		else
		{
			g_Player1.move.x = sinf(D3DX_PI * 0.50f) * 1.0f;
			g_nMoveDirection = 3;
		}
	}
	
	//�v���C���[1��Y���W���{(��)�����Ɉړ�����
	else if (GetKeyboardPress(DIK_S) || GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_NUMPAD2) == true) //S�L�[,���L�[,NUM�p�b�h��2�L�[�������ꂽ�ꍇ
	{
		g_Player1.move.y = cosf(D3DX_PI * 0.0) * 1.0f;
		g_nMoveDirection = 4;
	}

	//�v���C���[1��X,Y���W���|(����)�����Ɉړ�����
	else if (GetKeyboardPress(DIK_NUMPAD7) == true) //NUM�p�b�h��7�L�[�������ꂽ�ꍇ
	{
		g_Player1.move.x = sinf(-D3DX_PI * 0.75f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.75f) * 1.0f;
		g_nMoveDirection = 2;
	}

	//�v���C���[1��X���W���{,Y���W���|(�E��)�����Ɉړ�����
	else if (GetKeyboardPress(DIK_NUMPAD9) == true) //NUM�p�b�h��9�L�[�������ꂽ�ꍇ
	{
		g_Player1.move.x = sinf(D3DX_PI * 0.75f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.75f) * 1.0f;
		g_nMoveDirection = 3;
	}

	//�v���C���[1��X���W���|,Y���W���{(����)�����Ɉړ�����
	else if (GetKeyboardPress(DIK_NUMPAD1) == true) //NUM�p�b�h��1�L�[�������ꂽ�ꍇ
	{
		g_Player1.move.x = sinf(-D3DX_PI * 0.25f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.25f) * 1.0f;
		g_nMoveDirection = 2;
	}

	//�v���C���[1��X,Y���W���{(�E��)�����Ɉړ�����
	else if (GetKeyboardPress(DIK_NUMPAD3) == true) //NUM�p�b�h��3�L�[�������ꂽ�ꍇ
	{
		g_Player1.move.x = sinf(D3DX_PI * 0.25f) * 1.0f, g_Player1.move.y = cosf(D3DX_PI * 0.25f) * 1.0f;
		g_nMoveDirection = 3;
	}

	//�ړ��ʂ��[����(���̏�ɗ��܂��Ă���)�ꍇ
	else
	{
		g_nMoveDirection = 5;
	}

	//��ʒ[�̏����[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E

	//�v���C���[����ʂ̍��[�ɓ��������ꍇ
	if (g_Player1.pos.x <= 80)
	{
		g_Player1.move.x *= 0.0f; //����ȏ㍶�����Ɉړ��ł��Ȃ��Ȃ�
	}

	//�v���C���[����ʂ̏�[�ɓ��������ꍇ
	if (g_Player1.pos.y <= 80)
	{
		g_Player1.move.y *= 0.0f; //����ȏ������Ɉړ��ł��Ȃ��Ȃ�
	}
	//�v���C���[����ʂ̉E�[�ɓ��������ꍇ
	if (g_Player1.pos.x >= SCREEN_WIDTH - 80)
	{
		g_Player1.move.x *= 0.0f; //����ȏ�E�����Ɉړ��ł��Ȃ��Ȃ�
	}
	//�v���C���[����ʂ̉��[�ɓ��������ꍇ
	if (g_Player1.pos.y >= SCREEN_HEIGHT - 80)
	{
		g_Player1.move.y *= 0.0f; //����ȏ㉺�����Ɉړ��ł��Ȃ��Ȃ�
	}

	//��],�g��k���֘A�̏���--------------------------------------------------
	
	//�v���C���[1�����������ɉ�]����
	if (GetKeyboardPress(DIK_Q) == true) //Q�L�[�������ꂽ�ꍇ
	{
		//E�L�[�������ɉ�����Ă���ꍇ
		if (GetKeyboardPress(DIK_E) == true)
		{
			g_Player1.rot.z += 0.0f;
		}

		//����ȊO(Q�L�[�݂̂�������Ă���ꍇ)
		else
		{
			g_Player1.rot.z += 0.01f;
		}
	}

	//�v���C���[1���E�������ɉ�]����
	else if (GetKeyboardPress(DIK_E) == true) //E�L�[�݂̂�������Ă���ꍇ
	{
		g_Player1.rot.z -= 0.01f;
	}

	//�v���C���[1���g�傷��
	if (GetKeyboardPress(DIK_R) == true) //R�L�[�������ꂽ�ꍇ
	{
		//X�L�[�������ɉ�����Ă���ꍇ
		if (GetKeyboardPress(DIK_F) == true)
		{
			g_Player1.Length += 0.0f;
		}

		//����ȊO(Z�L�[�݂̂�������Ă���ꍇ)
		else
		{
			g_Player1.Length += 0.3f;
		}
	}

	//�v���C���[1���k������
	else if (GetKeyboardPress(DIK_F) == true) //F�L�[�݂̂�������Ă���ꍇ
	{
		g_Player1.Length -= 0.3f;
	}

	//�v���C���[1�̈ʒu,��],�g������Z�b�g����
	else if (GetKeyboardPress(DIK_T) == true) //T�L�[�݂̂�������Ă���ꍇ
	{
		InitPlayer1();
	}

	//�V���b�g�֘A�̏���-------------------------------------------------------

	//�V���b�g������
	else if (GetKeyboardRepeat(DIK_Z) == true) //Z�L�[�݂̂�������Ă���ꍇ
	{
		SetBullet(g_Player1.pos, g_Player1.move, MAX_LIFE, BULLETTYPE_PLAYER1); //SetBullet(�ʒu, �ړ���, �e�����ł���܂ł̎��� ,�e�̎��);
	}

	//�����̏����[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[
	if (GetKeyboardPress(DIK_C) == true) //C�L�[�������ꂽ�ꍇ
	{ //�ړ��ʂ��X�V(����)������
		g_Player1.move.x += 0.1f;
		g_Player1.move.y += -0.02f;
	}

	//�v���C���[1�̈ʒu���X�V���鏈�� �������͏����Ȃ�����!!��
	g_Player1.pos.x += g_Player1.move.x; //�v���C���[1�̌��݈ʒu��X���W��X�����̈ړ��ʂ����Z������
	g_Player1.pos.y += g_Player1.move.y; //�v���C���[1�̌��݈ʒu��Y���W��Y�����̈ړ��ʂ����Z������

	//�ړ��ʂ��X�V(����)������
	g_Player1.move.x += (0.0f - g_Player1.move.x) * 0.05f; //X�����̈ړ��� += (�ړI��(�����܂Ō�����������)�l - ���݂̒l) * �����W��
	g_Player1.move.y += (0.0f - g_Player1.move.y) * 0.05f; //Y�����̈ړ��� += (�ړI��(�����܂Ō�����������)�l - ���݂̒l) * �����W��

	//���_���W�̍X�V�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferPlayer1->Lock(0, 0, (void**)&pVertexPlayer1, 0);

	//���_���W�̐ݒ�
	pVertexPlayer1[0].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z - (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0�Ԗڂ̒��_��X���W g_Player1.pos.x + sinf(���� + �p�x(���n�_ + �Ίp���̊p�x)) * ����
	pVertexPlayer1[0].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z - (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0�Ԗڂ̒��_��Y���W g_Player1.pos.y + cosf(���� + �p�x) * ����
	pVertexPlayer1[0].pos.z = 0.0f; //0�Ԗڂ̒��_��Z���W
	pVertexPlayer1[1].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0�Ԗڂ̒��_��X���W g_Player1.pos.x + sinf(���� + �p�x(���n�_ + �Ίp���̊p�x)) * ����
	pVertexPlayer1[1].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (D3DX_PI - g_Player1.Angle)) * g_Player1.Length; //0�Ԗڂ̒��_��Y���W g_Player1.pos.y + cosf(���� + �p�x) * ����
	pVertexPlayer1[1].pos.z = 0.0f; //0�Ԗڂ̒��_��Z���W
	pVertexPlayer1[2].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (0.0f - g_Player1.Angle)) * g_Player1.Length; //2�Ԗڂ̒��_��X���W g_Player1.pos.x + sinf(���� + �p�x(���n�_ + �Ίp���̊p�x)) * ����
	pVertexPlayer1[2].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (0.0f - g_Player1.Angle)) * g_Player1.Length; //2�Ԗڂ̒��_��Y���W g_Player1.pos.y + cosf(���� + �p�x) * ����
	pVertexPlayer1[2].pos.z = 0.0f; //2�Ԗڂ̒��_��Z���W
	pVertexPlayer1[3].pos.x = g_Player1.pos.x + sinf(g_Player1.rot.z + (0.0f + g_Player1.Angle)) * g_Player1.Length; //3�Ԗڂ̒��_��X���W g_Player1.pos.x + sinf(���� + �p�x(���n�_ + �Ίp���̊p�x)) * ����
	pVertexPlayer1[3].pos.y = g_Player1.pos.y + cosf(g_Player1.rot.z + (0.0f + g_Player1.Angle)) * g_Player1.Length; //3�Ԗڂ̒��_��Y���W g_Player1.pos.y + cosf(���� + �p�x) * ����
	pVertexPlayer1[3].pos.z = 0.0f; //3�Ԗڂ̒��_��Z���W

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferPlayer1->Unlock();

	//�A�j���[�V�����֘A�̏���-------------------------------------------------
	
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferPlayer1->Lock(0, 0, (void**)&pVertexPlayer1, 0);

	if ((g_nCounterAnimPlayer1 % 10) == 0) //��莞��(12F)�o�߂����ꍇ
	{
		g_nPatternAnimPlayer1++; //�A�j���[�V�����p�^�[���̔ԍ����X�V(���Z)����

		//�ړ��ʂ��[����(���̏�ɗ��܂��Ă���)�ꍇ
		if (g_Player1.move.x >= -0.07f && g_Player1.move.x <= 0.07f && g_Player1.move.y >= -0.07f && g_Player1.move.y <= 0.07f)
		{
			g_nPatternAnimPlayer1--; //�A�j���[�V�����p�^�[���̔ԍ������Z����(���X�V���~�߂�����)
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

			//�A�j���[�V�����p�^�[���̔ԍ����X�V(���Z)����
			g_nPatternAnimPlayer1 = (g_nPatternAnimPlayer1) % 10; //10�c���p�^�[����

			if (g_nPatternAnimPlayer1 > 11) //�A�j���[�V�����p�^�[���̑����𒴂����ꍇ
			{
				g_nPatternAnimPlayer1 = 0; //�A�j���[�V�����p�^�[���̔ԍ��������l(0)�ɖ߂�
			}
		}

		//�e�N�X�`�����W(UV)���X�V���鏈��

		//�e�N�X�`�����W�̐ݒ�
		pVertexPlayer1[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 / 5 * 0.5f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
		pVertexPlayer1[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 / 5 * 0.5f); //1�Ԗڂ̒��_
		pVertexPlayer1[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 / 5 * 0.5f + 0.5f); //2�Ԗڂ̒��_
		pVertexPlayer1[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 / 5 * 0.5f + 0.5f); //3�Ԗڂ̒��_


		//else if (6 <= g_nPatternAnimPlayer2 <= 10)
		//{
			//pVertexPlayer2[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 0.5f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
			//pVertexPlayer2[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 0.5f); //1�Ԗڂ̒��_
			//pVertexPlayer2[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f, 1.0f); //2�Ԗڂ̒��_
			//pVertexPlayer2[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer2 * 0.2f + 0.2f, 1.0f); //3�Ԗڂ̒��_
		//}

		//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
		g_pVertexBufferPlayer1->Unlock();
	}

	//��Ԋ֘A�̏���-----------------------------------------------------------
	switch (g_Player1.state)
	{
	case PLAYER1STATE_NORMAL: //�v���C���[1���ʏ��Ԃł���ꍇ
	
		break;
	

	case PLAYER1STATE_DAMAGE: //�v���C���[1���_���[�W��Ԃł���ꍇ
	
		g_Player1.nCounterState--; //��ԊǗ��J�E���^�[��F�f�N�������g���Ă���

		if (g_Player1.nCounterState <= 0) //��ԊǗ��J�E���^�[�̐��l��0�ȉ��ɂȂ����ꍇ
		{
			g_Player1.state = PLAYER1STATE_NORMAL; //�G�̏�Ԃ�ʏ��Ԃɂ���

			//���_�J���[�̐ݒ�(�|���S����ʏ�F�ɖ߂�)
			pVertexPlayer1[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
			pVertexPlayer1[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
			pVertexPlayer1[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
			pVertexPlayer1[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_
		}
		break;

	case PLAYER1STATE_DEATH: //�v���C���[1�����S��Ԃł���ꍇ

		g_Player1.nCounterState--; //��ԊǗ��J�E���^�[��F�f�N�������g���Ă���

		if (g_Player1.nCounterState <= 0) //��ԊǗ��J�E���^�[�̐��l��0�ȉ��ɂȂ����ꍇ
		{
			SetMode(MODE_RESULT); //���[�h�ݒ�(���U���g��ʂɈړ�����)

			return;
		}
		break;

	}
}

//�v���C���[1�̕`�揈��========================================================
void DrawPlayer1(void)
{
	LPDIRECT3DDEVICE9 pDevicePlayer1; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDevicePlayer1 = GetDevice();

	if (g_Player1.bDisp == true) //�v���C���[���\������Ă��鎞�݂̂Ɋ��ʓ��̏������s��
								 // (�v���C���[����\���ł���ꍇ�͂��̏������s��Ȃ��悤�ɂ��邽��)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevicePlayer1->SetStreamSource(0, g_pVertexBufferPlayer1, 0, sizeof(VERTEX_2D));
		//g_pVertexBufferPolygon�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevicePlayer1->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevicePlayer1->SetTexture(0, g_pTexturePlayer1);

		//�|���S���̕`��
		pDevicePlayer1->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , 0�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)
	}
}

//�v���C���[1�̏I������========================================================
void UninitPlayer1(void)
{
	//�e�N�X�`���̔j���@
	if (g_pTexturePlayer1 != NULL) //g_pTexturePlayer1�Ƀe�N�X�`�����ݒ肳��Ă���ꍇ�A
								   // �e�N�X�`����j�����鏈��
	{
		g_pTexturePlayer1->Release();
		g_pTexturePlayer1 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferPlayer1 != NULL)
	{
		g_pVertexBufferPlayer1->Release();
		g_pVertexBufferPlayer1 = NULL;
	}
}

//�v���C���[1�̔�e����========================================================
void HitPlayer1(int nDamage)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	VERTEX_2D* pVertexPlayer1; //���_���ւ̃|�C���^
	int nCountPlayer1; //�v���C���[1��  ���J�E���g���邽�߂̕ϐ�

	g_Player1.nLife -= nDamage;

	if (g_Player1.nLife <= 0) //�v���C���[1�̗̑͂�0�ȉ��ɂȂ����ꍇ
	{
		//�����̐ݒ�
		SetExplosion(g_Player1.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); //�ʒu, �F

		g_Player1.bDisp = false; //�v���C���[1���\���ɂ���

		g_Player1.state = PLAYER1STATE_DEATH; //�v���C���[1�����S��Ԃɂ���

		g_Player1.nCounterState = 60; //
	}

	else //�G�̗̑͂�0�𒴉߂��Ă���ꍇ
	{
		g_Player1.state = PLAYER1STATE_DAMAGE;
		g_Player1.nCounterState = 5; //�_���[�W��Ԃ�ێ����鎞�Ԃ�ݒ肷��

		pVertexPlayer1 += 4 * nCountPlayer1; //���_�f�[�^�̃|�C���^��4���i�߂�

										   //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
		g_pVertexBufferPlayer1->Lock(0, 0, (void**)&pVertexPlayer1, 0);

		//���_�J���[�̐ݒ�(�|���S�����_���[�W�F�ɕύX����)
		pVertexPlayer1[0].col = D3DCOLOR_RGBA(255, 0, 0, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
		pVertexPlayer1[1].col = D3DCOLOR_RGBA(255, 0, 0, 255); //1�Ԗڂ̒��_
		pVertexPlayer1[2].col = D3DCOLOR_RGBA(255, 0, 0, 255); //2�Ԗڂ̒��_
		pVertexPlayer1[3].col = D3DCOLOR_RGBA(255, 0, 0, 255); //3�Ԗڂ̒��_

															  //���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
		g_pVertexBufferPlayer1->Unlock();
	}
}