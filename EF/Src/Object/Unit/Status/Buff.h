#pragma once
#include<vector>
//#include<array>
class Buff
{
public:
	//�o�t�̃^�C�v
	enum class BUFF_TYPE
	{
		NONE = 0,
		PALALYSIS,
		POISON,
		CONFUSION,
		AVOIDANCE,

		A_UP,
		A_DOWN,
		S_UP,
		S_DOWN,
		D_UP,
		D_DOWN,

		CMD_DOWN,
		CMD_BAN,
		END
	};


	Buff();
	~Buff();

	void Init(void);
	void Release(void);

	//�o�t�̐����֐�
	void CreateBuff(const BUFF_TYPE& buff);

	//��������
	const bool& IsAlive(void)const { return isAlive_; }

	//�o�t�̎擾�֐�
	const BUFF_TYPE& GetBuff(void) const{ return buff_; }

	//�o�t�̏��L�`�F�b�N
	bool CheckOwnBuff(const BUFF_TYPE& type);

	//�o�t�̎����^�[���v�Z
	bool DecBuffTurn(void);

	void SetAlive(bool alive) { isAlive_ = alive; }	//������Ԃ��Z�b�g����


private:
	//���L����
	bool isAlive_;

	//���L�o�t
	BUFF_TYPE buff_;

	//�����^�[����
	int turn_;

	//�o�t�̕t�^
	void CheckBuffTurn(const BUFF_TYPE& type);

};
