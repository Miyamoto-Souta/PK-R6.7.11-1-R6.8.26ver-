#include "R6.7.11-1-main.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
#include "R6.7.11-1-score.h" //����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferScore = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore; //�X�R�A�̈ʒu���Ǘ�����ϐ�
int g_nScore; //�X�R�A�̒l���Ǘ�����ϐ�

//�X�R�A�̏���������===========================================================
void InitScore(void)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceScore; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceScore = GetDevice();

	//�e�N�X�`���̓ǂݍ��݇@
	D3DXCreateTextureFromFile(pDeviceScore,
		"data\\TEXTURE\\Score000.png",
		&g_pTextureScore);

	//�e�퐔�l�̏�����
	g_posScore = D3DXVECTOR3(640.0f, 360.0f, 0.0f); //�X�R�A�̈ʒu������������ {D3DXVECTOR3(X���W, Y���W, Z���W)};

	g_nScore = 0; //�X�R�A�̒l������������

	//���_�o�b�t�@�̐���
	pDeviceScore->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_��}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVertexBufferScore,
		NULL);

	VERTEX_2D* pVertexScore; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferScore->Lock(0, 0, (void**)&pVertexScore, 0);

	//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
	pVertexScore[0].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH / 2, g_posScore.y - SCORE_HEIGHT / 2, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
	pVertexScore[1].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH / 2, g_posScore.y - SCORE_HEIGHT / 2, 0.0f); //1�Ԗڂ̒��_
	pVertexScore[2].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH / 2, g_posScore.y + SCORE_HEIGHT / 2, 0.0f); //2�Ԗڂ̒��_
	pVertexScore[3].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH / 2, g_posScore.y + SCORE_HEIGHT / 2, 0.0f); //3�Ԗڂ̒��_

	//rhw�̐ݒ�
	pVertexScore[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexScore[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexScore[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexScore[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

	//���_�J���[�̐ݒ�
	pVertexScore[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
	pVertexScore[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
	pVertexScore[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
	pVertexScore[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_

	//�e�N�X�`�����W�̐ݒ�
	pVertexScore[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
	pVertexScore[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1�Ԗڂ̒��_
	pVertexScore[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
	pVertexScore[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3�Ԗڂ̒��_

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferScore->Unlock();
}

//�X�R�A�̍X�V����=============================================================
void UpdateScore(void)
{
	//���݂̃X�R�A�܂ŃJ�E���g�A�b�v�����铙�̓�����t�������ꍇ�͂����ɏ�����ǉ�����
}

//�X�R�A�̕`�揈��=============================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDeviceScore; //�f�o�C�X�ւ̃|�C���^��錾
	int nCount; //�񐔂𑪂�

	VERTEX_2D* pVertexScore; //���_���ւ̃|�C���^

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceScore = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceScore->SetStreamSource(0, g_pVertexBufferScore, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceScore->SetFVF(FVF_VERTEX_2D);
	
	//�e�N�X�`���̐ݒ�(�K�v�Ȍ������`�悳����悤�ɂ��邱��)
	pDeviceScore->SetTexture(0, g_pTextureScore);
	
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferScore->Lock(0, 0, (void**)&pVertexScore, 0);

	for (nCount = 0; nCount < 8; nCount++) //8�c�ő包��
	{
		//�|���S���̕`��
		pDeviceScore->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , nCount * 4�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)

		//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
		pVertexScore[0].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH / 2, g_posScore.y - SCORE_HEIGHT / 2, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
		pVertexScore[1].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH / 2, g_posScore.y - SCORE_HEIGHT / 2, 0.0f); //1�Ԗڂ̒��_
		pVertexScore[2].pos = D3DXVECTOR3(g_posScore.x - SCORE_WIDTH / 2, g_posScore.y + SCORE_HEIGHT / 2, 0.0f); //2�Ԗڂ̒��_
		pVertexScore[3].pos = D3DXVECTOR3(g_posScore.x + SCORE_WIDTH / 2, g_posScore.y + SCORE_HEIGHT / 2, 0.0f); //3�Ԗڂ̒��_

		//rhw�̐ݒ�
		pVertexScore[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexScore[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexScore[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
		pVertexScore[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

		//���_�J���[�̐ݒ�
		pVertexScore[0].col = D3DCOLOR_RGBA(255, 255, 255, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
		pVertexScore[1].col = D3DCOLOR_RGBA(255, 255, 255, 255); //1�Ԗڂ̒��_
		pVertexScore[2].col = D3DCOLOR_RGBA(255, 255, 255, 255); //2�Ԗڂ̒��_
		pVertexScore[3].col = D3DCOLOR_RGBA(255, 255, 255, 255); //3�Ԗڂ̒��_

		//�e�N�X�`�����W�̐ݒ�
		pVertexScore[0].tex = D3DXVECTOR2(0.0f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
		pVertexScore[1].tex = D3DXVECTOR2(1.0f, 0.0f); //1�Ԗڂ̒��_
		pVertexScore[2].tex = D3DXVECTOR2(0.0f, 1.0f); //2�Ԗڂ̒��_
		pVertexScore[3].tex = D3DXVECTOR2(1.0f, 1.0f); //3�Ԗڂ̒��_
	}

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferScore->Unlock();
}

//�X�R�A�̏I������=============================================================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL) //g_pTextureScore�Ƀe�N�X�`�����ݒ肳��Ă���ꍇ�A
								 // �e�N�X�`����j�����鏈��
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferScore != NULL)
	{
		g_pVertexBufferScore->Release();
		g_pVertexBufferScore = NULL;
	}
}

//�X�R�A�̐ݒ菈��=============================================================
void SetScore(int nScore)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	int aPosTextureU[8]; //�e���̐������i�[����(���̏ꍇ�͍ő�8��)

	LPDIRECT3DDEVICE9 pDeviceScore; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountScore; //�񐔂𑪂�

	VERTEX_2D* pVertexScore; //���_���ւ̃|�C���^

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceScore = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceScore->SetStreamSource(0, g_pVertexBufferScore, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceScore->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�(�K�v�Ȍ������`�悳����悤�ɂ��邱��)
	pDeviceScore->SetTexture(0, g_pTextureScore);

	//??�̏���---------------------------------------------------------------------
	g_nScore = nScore; //

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferScore->Lock(0, 0, (void**)&pVertexScore, 0);

	aPosTextureU[0] = g_nScore % 100000000 / 10000000; //8���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[1] = g_nScore % 10000000 / 1000000; //7���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[2] = g_nScore % 1000000 / 100000; //6���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[3] = g_nScore % 100000 / 10000; //5���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[4] = g_nScore % 10000 / 1000; //4���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[5] = g_nScore % 1000 / 100; //3���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[6] = g_nScore % 100 / 10; //2���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[7] = g_nScore % 10 / 1; //1���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;

	//�e�N�X�`�����W�̐ݒ�
	for (nCountScore = 0; nCountScore < 8; nCountScore++) //8�c�ő包��
	{
		pVertexScore[0].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
		pVertexScore[1].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f + 0.1f, 0.0f); //1�Ԗڂ̒��_
		pVertexScore[2].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f, 1.0f); //2�Ԗڂ̒��_
		pVertexScore[3].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f + 0.1f, 1.0f); //3�Ԗڂ̒��_

		pVertexScore += 4; //
	}

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferScore->Unlock();
}

//�X�R�A�̉��Z����=============================================================
void AddScore(int nValue)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	int aPosTextureU[8]; //�e���̐������i�[����(���̏ꍇ�͍ő�8��)

	LPDIRECT3DDEVICE9 pDeviceScore; //�f�o�C�X�ւ̃|�C���^��錾
	int nCountScore; //�񐔂𑪂�

	VERTEX_2D* pVertexScore; //���_���ւ̃|�C���^

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceScore = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceScore->SetStreamSource(0, g_pVertexBufferScore, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceScore->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�(�K�v�Ȍ������`�悳����悤�ɂ��邱��)
	pDeviceScore->SetTexture(0, g_pTextureScore);

	//����---------------------------------------------------------------------
	g_nScore += nValue; //���݂̃X�R�A�̒l�ɉ��Z����l�𑫂�

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferScore->Lock(0, 0, (void**)&pVertexScore, 0);

	aPosTextureU[0] = g_nScore % 100000000 / 10000000; //8���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[1] = g_nScore % 10000000 / 1000000; //7���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[2] = g_nScore % 1000000 / 100000; //6���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[3] = g_nScore % 100000 / 10000; //5���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[4] = g_nScore % 10000 / 1000; //4���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[5] = g_nScore % 1000 / 100; //3���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[6] = g_nScore % 100 / 10; //2���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;
	aPosTextureU[7] = g_nScore % 10 / 1; //1���� �X�R�A % ���݋��߂�ʂ�1��̈� / ���݋��߂��;

	//�e�N�X�`�����W�̐ݒ�
	for (nCountScore = 0; nCountScore < 8; nCountScore++) //8�c�ő包��
	{
		pVertexScore[0].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR2(U���W, V���W)};
		pVertexScore[1].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f + 0.1f, 0.0f); //1�Ԗڂ̒��_
		pVertexScore[2].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f, 1.0f); //2�Ԗڂ̒��_
		pVertexScore[3].tex = D3DXVECTOR2(aPosTextureU[nCountScore] * 0.1f + 0.1f, 1.0f); //3�Ԗڂ̒��_

		pVertexScore += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N���鏈�� �����̏����͊e���_�ݒ�̒����ɒu�����Ɓ�
	g_pVertexBufferScore->Unlock();
}