#pragma once
#include<vector>
#include<array>

//�퓬�f�b�L�i�ő吔�F�R�́j
//using Deck = std::array<int, 3>;

class DeckManager
{
public:
	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static DeckManager& GetInstance(void);

	// ������
	void Init(void);

	// ���
	void Release(void);

	//�R�}���h�f�[�^�̃��[�h
	void LoadCmdData(void);

	//�f�b�L���̎擾
	const std::array<int, 3>& GetDeck(void) { return deck_; }
	//���j�b�g�v�[�����̎擾
	const std::vector<int>& GetUnitPool(void) { return unitPool_; }

	//�f�b�L���̃Z�b�g
	void SetDeck(std::array<int, 3> deck);

	//���j�b�g�̒ǉ�
	void AddUnit(const int& unitNum);

private:
	// �ÓI�C���X�^���X
	static DeckManager* instance_;

	//�f�b�L�J�[�h
	std::array<int, 3> deck_;

	//���j�b�g�v�[��
	std::vector<int>unitPool_;


	// �O�����琶���ł��Ȃ��l�ɂ���
	DeckManager(void);
	// �f�X�g���N�^�����l
	~DeckManager(void);

};

