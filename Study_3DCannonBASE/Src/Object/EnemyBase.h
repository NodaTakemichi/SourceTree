#pragma once
#include <string>
#include <DxLib.h>
#include"../Common/Vector2.h"
class EnemyBase
{
public:
	//�G�̎��
	enum class ENEMY_TYPE
	{
		SMALL,
		MEDIUM,
		BAT,
		BIG,
		MAX
	};

	//�L�����p�����[�^
	struct Par
	{
		float speed;	//�ړ����x
		float scale;	//�傫��
		int maxHp;		//HP
		int animNo;		//�A�j���[�V�����ԍ�
	}; 


	// �R���X�g���N�^
	EnemyBase();
	// �f�X�g���N�^
	virtual ~EnemyBase(void);

	// ��������(�ŏ��̂P��̂ݎ��s)
	virtual void Init(void);
	// �p�����[�^�ݒ�(�������z�֐�)
	virtual void SetParam(void);
	// �X�V����(���t���[�����s)
	virtual void Update(void);
	// �`�揈��(���t���[�����s)
	virtual void Draw(void);
	// �������(�Ō�̂P��̂ݎ��s)
	virtual void Release(void);

	//�G�l�~�[�^�C�v�̃Z�b�g
	void SetEnemyType(ENEMY_TYPE type);

	// ���W�̎擾
	VECTOR GetPos(void);
	// ���W�̐ݒ�
	void SetPos(VECTOR pos);
	// ��������
	bool IsAlive(void);
	// ��������
	void SetAlive(bool alive);
	// �_���[�W��^����
	void Damage(int damage);

	// �Փ˗p�̒��S���W�̎擾
	VECTOR GetCollisionPos(void);
	// �Փ˗p�̋��̔��a�̎擾
	float GetCollisionRadius(void) {return collisionRadius_;}


protected:

	// ���ƂȂ�e�̃��f��ID
	int baseModelId_;
	// �e�̃��f��ID
	int modelId_;
	// �傫��
	VECTOR scl_;
	// �p�x
	VECTOR rot_;
	// �\�����W
	VECTOR pos_;
	// �ړ����x
	float speed_;
	// �ړ�����
	VECTOR dir_;

	// �̗�
	int hp_;
	// �̗͍ő�l
	int hpMax_;
	// �̗͂̌��ݕ\���l
	float hpNow_;
	// �̗͂̉ߋ��l
	int hpBefore_;
	// ��������
	bool isAlive_;
	//HP�̐��`��ԂɎg�p����^�C��
	float hpLerpTime_;

	//���v����
	float totalTime_;

	// �A�j���[�V�������A�^�b�`�ԍ�
	int animAttachNo_;
	// �A�j���[�V�����̑��Đ�����
	float animTotalTime_;
	// �Đ����̃A�j���[�V��������
	float stepAnim_;
	// �A�j���[�V�������x
	float speedAnim_;

	// �Փ˔���p�̋��̔��a
	float collisionRadius_;
	// �Փ˔���p�̋��̒��S�̒������W
	VECTOR collisionLocalPos_;

	//�L�����̎��
	ENEMY_TYPE type_;

	//���_���
	VERTEX2DSHADER mVertex[4];
	WORD mIndex[6];
	//�V�F�[�_�[
	int psHpShader_;
	int psHpShaderConstBuf_;
	//�`��p�̎l�p���_�̂̍쐬
	void MakeSquereVertex(Vector2 pos);

};