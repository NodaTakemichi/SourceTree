#pragma once
#include <vector>
#include "SceneBase.h"
#include "../Common/Vector2.h"

class UnitManager;
class Roulette;
class GameUI;

class BattleSystem;
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
	//�G�t�F�N�g�}�l�[�W���[
	EffectManager* efMng_;

	//�Q�[���t�F�[�Y
	GAME_PHASE phase_;

	//���j�b�g�̃o�g���V�X�e��
	BattleSystem* battleSys_;

	//�}�E�X
	int mouseImg_;
	//�w�i�摜
	int bgImg_;
	//�t���[��
	int frameImg_;

	//�^�[�������A�F
	std::string turnString_;
	int turnCol_;

	//�o�ߑ�����
	float mTotalTime;

	//�s�����j�b�g�̑��삪�������蓮�����f
	bool actUnitAoutm_;

	//�t�F�[�Y�ύX
	void ChangeGamePhase(GAME_PHASE phase);

	///�e�X�g
	Vector2 testPos;
	int testNum;
	float testScale;

};
