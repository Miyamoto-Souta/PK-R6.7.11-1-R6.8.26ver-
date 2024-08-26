#ifndef _ENEMY1_H_ //���̃}�N����`������Ă��Ȃ������ꍇ��1�s�ڂɕK���������Ɓ�

#define _ENEMY1_H_ //���d�C���N���[�h(�ǂݍ���)�h�~�p�̃}�N����`

#include <math.h>
#include "R6.7.11-1-main.h"

//�}�N����`
#define MAX_ENEMY1 (128) //�G�̍ő吔
#define ENEMY1_WIDTH (64) //�G1�̕�
#define ENEMY1_HEIGHT (53) //�G1�̍���

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 movebullet; //�G�e�̈ړ���
	int nType; //���
	ENEMYSTATE state; //���
	int nCounterState; //��ԊǗ��J�E���^�[
	int nLife = 5; //�̗�
	bool bUse; //�g�p���Ă��邩�ǂ���
} Enemy;

//�G�̏��
typedef enum
{
	ENEMYSTATE_NOMAL = 0, //�ʏ���
	ENEMYSTATE_DAMAGE, //�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�v���g�^�C�v�錾
void InitEnemy1(void); //�G1�̏���������
void UninitEnemy1(void); //�G1�̏I������
void UpdateEnemy1(void); //�G1�̍X�V����
void DrawEnemy1(void); //�G1�̕`�揈��
void SetEnemy1(D3DXVECTOR3 pos, int nType); //�G1�̐ݒ菈�� pos�c�o���ʒu int nType�c���
Enemy* GetEnemy1(void); //�G1���擾���鏈��
inline void HitEnemy1(int nCountEnemy1, int nDamage); //�G1�̔�e����
int EnemyTotal(); //���݂̓G�̑������Ǘ����鏈��

//�O���[�o���ϐ��錾

#endif //���ŉ��s�ɕK���������Ɓ�