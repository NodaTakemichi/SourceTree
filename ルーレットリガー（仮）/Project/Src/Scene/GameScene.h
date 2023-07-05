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
	enum class GAME_PHASE
	{
		BATTLE_START,
		RULLET_TIME,
		AIM,
		EFFECT,
		BATTLE,
		TURN_END,
		GAME_END
	};


	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void UpdateRouTime(void);
	void UpdateAIM(void);
	void UpdateEffect(void);
	void UpdateBattle(void);
	void UpdateTurnEnd(void);


private:
	//���j�b�g�}�l�[�W���[
	UnitManager* unitMng_;
	//���[���b�g
	Roulette* roulette_;
	//UI
	GameUI* GameUi_;

	//�Q�[���t�F�[�Y
	GAME_PHASE phase_;

	//���j�b�g�̃o�g���V�X�e��
	BattleSystem* battleSys_;
	//���j�b�g�̎��S���o
	DeathStaging* deathSta_;

	//�t���[��
	int frameImg_;
	int topFrameImg_;

	//�s�����j�b�g�̑��삪�������蓮�����f
	bool actUnitAoutm_;

	//�t�F�[�Y�ύX
	void ChangeGamePhase(GAME_PHASE phase);

};
