#pragma once
#include<vector>
#include<array>


//�o�g���f�[�^
struct BattleData {
	std::array<int, 3> pDeck;	//�v���C���[�f�b�L
	std::array<int, 3> eDeck;	//�G�l�~�[�f�b�L
	int bgNum;					//�w�i�摜�i���o�[
	int bgmNum;					//BGM�ԍ�
};

class BattleDataManager
{
public:
	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static BattleDataManager& GetInstance(void);

	// ������
	void Init(void);

	// ���
	void Release(void);

	//�o�g���f�[�^�̃Q�b�g�A�Z�b�g
	const  BattleData& GetBattleData(void) { return bData_; }
	void SetBattleData(const BattleData& data);

private:
	// �ÓI�C���X�^���X
	static BattleDataManager* instance_;

	//�o�g���f�[�^
	BattleData bData_;


	// �O�����琶���ł��Ȃ��l�ɂ���
	BattleDataManager(void);
	// �f�X�g���N�^�����l
	~BattleDataManager(void);


};

