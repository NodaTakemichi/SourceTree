#pragma once
#include <vector>
#include "SceneBase.h"
#include "../Common/Vector2.h"

class UnitManager;
class Roulette;
class GameUI;

class BattleSystem;
class DeathStaging;
class EffectManager;

class GameScene : public SceneBase
{

public:

	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;



private:
	//�G�t�F�N�g�}�l�[�W���[
	EffectManager* efMng_;



	///�e�X�g
	Vector2 testPos;
	int testNum;
	float testScale;
	std::string path;

};
