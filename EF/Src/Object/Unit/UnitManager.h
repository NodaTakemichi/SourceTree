#pragma once
#include<vector>
#include<map>

class UnitBase;
class PlayerUnit;
class EnemyUnit;
class Command;


class UnitManager
{
public:
	////�C���X�^���X�̐���
	//static void CreateInstance(void);
	////�C���X�^���X�̎擾
	//static UnitManager& GetInstance(void);


	UnitManager();
	~UnitManager();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//�s�����̃��j�b�g�̃R�}���h�����擾
	std::vector<Command*> GetCommand(void);

	//�s�����j�b�g�̎擾
	UnitBase* GetActivUnit(void);
	//�S���j�b�g�̎擾
	std::vector <UnitBase*> GetUnits(void) { return units_; }

	//�s�����j�b�g��ύX����֐�
	void ChangeActivUnit(void);
	
	//���j�b�g���S�ł��ǂ������f
	bool IsAnniUnit(void);

private:
	//�ÓI�C���X�^���X
	static UnitManager* mInstance;
	
	//���j�b�g�̔z��
	std::vector<UnitBase*> units_;



	//�L�������̎擾
	void CreateUnit(void);

	//�X�s�[�h���������ɕ��ѕς���
	void SpeedSort(void);


	//�S���j�b�g���s�������j�b�g����͂���
	void NotActUnitAll(void);
};

