#pragma once
#include<vector>

class UnitBase;
class Command;

class BattleSystem
{
public:

	BattleSystem();
	~BattleSystem();

	void Init(void);
	void Release(void);


	//�o�g���ɕK�v�ȏ����Z�b�g����
	void SetBattleData(UnitBase* unit, Command* cmd, 
		std::vector<UnitBase*> units);

	//�R�}���h�̌��ʑΏۂɂ���āA�Ώۂ𔻒f����
	void CheckSelectTarget(void);

	//���ۂɃA�N�V����������Ώۂ�I������
	bool SelectUnit(void);

private:

	UnitBase* actUnit_;				//�s�����j�b�g
	Command* actCmd_;				//�����R�}���h
	std::vector<UnitBase*> units_;	//�S���j�b�g

	//�Ώۃi���o�[
	int targetNum_;


	//�I���ł��郆�j�b�g�����i�[
	std::vector<UnitBase*> selectedUnits_;	

	//�I�����j�b�g����A���ۂɑΏۂƂ��郆�j�b�g���i�[
	std::vector<UnitBase*> targetUnits_;

	/// �Ώۂ̃��j�b�g�����擾����
	/// <param name="equal">true:�����Afalse:����</param>
	void SetTargetUnits(bool equal);

	//�Ώۂ����钆����A�I������
	bool SelectInTarget(void);

	//�Ώە�Update
	void None(void);
	void Self(void);
	void Enemy(void);
};

