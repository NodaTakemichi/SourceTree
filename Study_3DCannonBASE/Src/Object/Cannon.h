#pragma once
#include<vector>
#include<DxLib.h>
class ShotBase;

class Cannon
{
public:
	//�C�g��X��]�����i�ő�j
	static constexpr float MAX_ANGLE_X = 15.0f * DX_PI_F / 180.0f;
	//�C�g��X��]�����i�Œ�j
	static constexpr float MN_ANGLE_X = -30.0f * DX_PI_F / 180.0f;

	//�e���ˌ�̍d������
	static constexpr float SHOT_DELAY = 1.0f;

	//�����̃T�C�Y
	static constexpr float BLAST_SIZE_X = 32;
	static constexpr float BLAST_SIZE_Y = 32;
	//�����̃A�j���[�V������
	static constexpr int BLAST_ANIM_NUM = 16;


	Cannon();
	~Cannon();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//�e�̎擾
	std::vector<ShotBase*> GetShots(void);

private:
	//3D��{���
	//�y��
	VECTOR standScl_;
	VECTOR standRot_;
	VECTOR standPos_;
	int standModelId_;

	//�C�g
	VECTOR barrelScl_;
	VECTOR barrelRot_;
	VECTOR barrelPos_;
	int barrelModelId_;

	//���΍��W
	VECTOR barrelLocalos_;

	//�����̉摜
	int blastImgs_[BLAST_ANIM_NUM];

	// �V���b�g(�|�C���^)
	std::vector<ShotBase*> shots_;
	// �e�̃��f��ID
	int shotModelId_;
	// �e���ˌ�̍d�����Ԍv�Z�p
	float stepShotDelay_;
	// ��]����
	void ProcessRot(void);
	// ���ˑ���
	void ProcessShot(void);
	// �L���Ȓe���擾����
	ShotBase* GetValidShot(void);
};

