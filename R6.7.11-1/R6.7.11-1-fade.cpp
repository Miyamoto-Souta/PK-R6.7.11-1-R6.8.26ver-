#include "R6.7.11-1-fade.h" //PC���̃��C�u�������g�������ꍇ�́u<�Z�Z.h>�v,
							// ����̃w�b�_�[�t�@�C�����g�������ꍇ�́u"�Z�Z.h"�v�ƋL������

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferFade = NULL; //���_�o�b�t�@�ւ̃|�C���^
FADE g_fade; //�t�F�[�h�̏�Ԃ��Ǘ�����
MODE g_ModeNext; //���̉��(���[�h)
D3DXVECTOR3 g_posFade; //�|���S��(�t�F�[�h)�̈ʒu���Ǘ�����ϐ�
D3DXCOLOR g_colorFade; //�|���S��(�t�F�[�h)�̐F���Ǘ�����ϐ�

//�t�F�[�h��ʂ̏���������=====================================================
void InitFade(MODE ModeNext)
{
	//�ϐ���錾����Ƃ���-----------------------------------------------------
	LPDIRECT3DDEVICE9 pDeviceFade; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceFade = GetDevice();

	g_fade = FADE_IN; //�t�F�[�h�C����Ԃɂ���

	g_ModeNext = ModeNext; //���̉��(���[�h)��ݒ肷��

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); //�|���S���̐F��^����(�s����)�ɂ���

	//���_�o�b�t�@�̐���
	pDeviceFade->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�m�ۂ���o�b�t�@�̃T�C�Y{sizeof(VERTEX_2D) �~ �K�v�Ȓ��_��}
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D, //���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVertexBufferFade,
		NULL);

	VERTEX_2D* pVertexFade; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾���鏈�� �����̏����͊e���_�ݒ�̒���ɒu�����Ɓ�
	g_pVertexBufferFade->Lock(0, 0, (void**)&pVertexFade, 0);

	//pVertex�̐ݒ�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[�E�[

	//���_���W�̐ݒ� ���K���E���ɂȂ�悤�ɐݒ肷�邱��!!��
	pVertexFade[0].pos = D3DXVECTOR3(g_posFade.x - FADE_WIDTH / 2, g_posFade.y - FADE_HEIGHT / 2, 0.0f); //0�Ԗڂ̒��_{D3DXVECTOR3(X���W, Y���W, Z���W)};
	pVertexFade[1].pos = D3DXVECTOR3(g_posFade.x + FADE_WIDTH / 2, g_posFade.y - FADE_HEIGHT / 2, 0.0f); //1�Ԗڂ̒��_
	pVertexFade[2].pos = D3DXVECTOR3(g_posFade.x - FADE_WIDTH / 2, g_posFade.y + FADE_HEIGHT / 2, 0.0f); //2�Ԗڂ̒��_
	pVertexFade[3].pos = D3DXVECTOR3(g_posFade.x + FADE_WIDTH / 2, g_posFade.y + FADE_HEIGHT / 2, 0.0f); //3�Ԗڂ̒��_

	//rhw�̐ݒ�
	pVertexFade[0].rhw = 1.0f; //0�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexFade[1].rhw = 1.0f; //1�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexFade[2].rhw = 1.0f; //2�Ԗڂ̒��_(�l��1.0f�ŌŒ�)
	pVertexFade[3].rhw = 1.0f; //3�Ԗڂ̒��_(�l��1.0f�ŌŒ�)

	//���[�h�̐ݒ�
	SetMode(g_ModeNext);
}

//�t�F�[�h��ʂ̍X�V����=======================================================
void UpdateFade(void)
{
	VERTEX_2D* pVertexFade; //���_���ւ̃|�C���^

	if (g_fade != FADE_NONE) //
	{
		if (g_fade != FADE_IN) //�t�F�[�h�C�����
		{
			g_colorFade.a -= 0.1f; //�����x�̒l�������Ă���(�|���S���𓧖��ɂ��Ă���)

			if (g_colorFade.a <= 0.0f) //�����x�̒l��0.0f�ȉ��ɂȂ����ꍇ
			{
				g_colorFade.a = 0.0f; //�����x�̒l��0.0f�ɌŒ肷��

				g_fade = FADE_NONE; //�t�F�[�h�̏�Ԃ��������Ă��Ȃ���Ԃɂ���
			}
		}

		else if (g_fade == FADE_OUT) //�t�F�[�h�A�E�g���
		{
			g_colorFade.a += 0.1f; //�����x�̒l���グ�Ă���(�|���S����s�����ɂ��Ă���)

			if (g_colorFade.a >= 1.0f) //�����x�̒l��1.0f�𒴉߂����ꍇ
			{
				g_colorFade.a = 1.0f; //�����x�̒l��1.0f�ɌŒ肷��

				g_fade = FADE_IN; //�t�F�[�h�C�����

				//���[�h�ݒ�(���̉�ʂɈڍs����)
				SetMode(g_ModeNext);
			}
		}
		//���_�J���[�̐ݒ�
		pVertexFade[0].col = D3DCOLOR_RGBA(0, 0, 0, 255); //0�Ԗڂ̒��_{D3DCOLOR_RGBA(��, ��, ��, �����x)};
		pVertexFade[1].col = D3DCOLOR_RGBA(0, 0, 0, 255); //1�Ԗڂ̒��_
		pVertexFade[2].col = D3DCOLOR_RGBA(0, 0, 0, 255); //2�Ԗڂ̒��_
		pVertexFade[3].col = D3DCOLOR_RGBA(0, 0, 0, 255); //3�Ԗڂ̒��_
	}
}

//�t�F�[�h��ʂ̕`�揈��=======================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDeviceFade; //�f�o�C�X�ւ̃|�C���^��錾

	//�f�o�C�X�̎擾(�Q�b�^�[)����
	pDeviceFade = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDeviceFade->SetStreamSource(0, g_pVertexBufferFade, 0, sizeof(VERTEX_2D));
	//g_pVertexBufferTitle�c���_�o�b�t�@�ւ̃|�C���^ VERTEX_2D�c���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDeviceFade->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDeviceFade->SetTexture(0, NULL); //�e�N�X�`�����g�p���Ȃ����́uNULL�v�Ƃ���

	//�|���S���̕`��
	pDeviceFade->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//(D3DPT_TRIANGLESTRIP�c�v���~�e�B�u�̎�� , 0�c�`�悷��ŏ��̒��_�C���f�b�N�X , 2�c�`�悷��v���~�e�B�u(�|���S��)�̐�)

}

//�t�F�[�h��ʂ̏I������=======================================================
void UninitFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVertexBufferFade != NULL)
	{
		g_pVertexBufferFade->Release();
		g_pVertexBufferFade = NULL;
	}
}

//�t�F�[�h��Ԃ̐ݒ菈��(1F�����Ăяo���悤�ɂ���)=============================
void SetGameState(MODE ModeNext)
{
	g_fade = FADE_OUT; //�t�F�[�h�A�E�g��Ԃɂ���

	g_ModeNext = ModeNext; //���̉��(���[�h)��ݒ肷��

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f); //�|���S���̐F��^����(�s����)�ɂ��Ă���
}

//�t�F�[�h��Ԃ̎擾����=======================================================
FADE GetFade(void)
{
	return g_fade;
}