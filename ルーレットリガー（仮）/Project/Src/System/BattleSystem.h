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

	//�I�����j�b�g�̃��Z�b�g����
	void ResetSelectUnits(void);
	//�R�}���h�̌��ʑΏۂɂ���āA�Ώۂ𔻒f����
	void CheckSelectTarget(void);
	//���ۂɃA�N�V����������Ώۂ�I������
	bool SelectUnit(const bool& autom);

	//�R�}���h����
	void CmdProcess(void);

	//�I�����j�b�g���烉���_���Ɍ��߂�
	void SetRandUnit(void);


private:
	//�ΏۑI���܂ł̑ҋ@����
	const float STOP_WAIT_TIME_AIM = 0.8f;



	UnitBase* actUnit_;				//�s�����j�b�g
	Command* actCmd_;				//�����R�}���h
	std::vector<UnitBase*> units_;	//�S���j�b�g

	//�Ώۃi���o�[
	int targetNum_;

	//�I���ł��郆�j�b�g�����i�[
	std::vector<UnitBase*> selectedUnits_;	

	//�I�����j�b�g����A���ۂɑΏۂƂ��郆�j�b�g���i�[
	std::vector<UnitBase*> targetUnits_;

	//���v����
	float totalTime_;
	//�����_�����j�b�g
	int randUnit_;

	/// �Ώۂ̃��j�b�g�����擾����
	/// <param name="equal">true:�����Afalse:����</param>
	void SetTargetUnits(const bool& equal);
	//�Ώۂ����钆����A�I������
	bool SelectInTarget(const bool& autom);

	//�_���[�W����
	void ProcessDamege(void);
	//�񕜏���
	void ProcessHeal(void);

};

