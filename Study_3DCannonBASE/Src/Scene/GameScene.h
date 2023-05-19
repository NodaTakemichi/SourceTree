#pragma once
#include <vector>
#include "SceneBase.h"
class Stage;
class Cannon;
class EnemyBase;

class GameScene :
	public SceneBase
{
public:
	//�Q�[���I�[�o�[�n�_�Փ˔���p���̔��a
	static constexpr float OVER_COL_RADIOUS = 35.0f;

	//�E�F�[�u
	enum class Wave
	{
		FIRST,
		LAST,
		END
	};

	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	Stage* stage_;
	Cannon* cannnon_;

	//�G�̃��f��
	EnemyBase*  enemy_;

	// �Q�[���I�[�o�[�n�_
	VECTOR gameoverPoint_;
	// �Q�[���I�[�o�[����
	bool isGameover_;
	// �Q�[���I�[�o�[�摜
	int imgGameover_;

	// �Q�[���N���A�摜
	int imgGameclear_;
	// �l�N�X�g�E�F�[�u�摜
	int imgNextWave_;

	//��������G�̐�
	int enemyCount;
	//�G�����̎��ԊԊu
	float stepCreateDis;

	//�E�F�[�u�Ǘ�
	Wave wave_;
	void ChangeWave(Wave wave);

};

