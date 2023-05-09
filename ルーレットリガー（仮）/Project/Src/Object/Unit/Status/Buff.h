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

		P_UP,
		P_DOWN,
		S_UP,
		S_DOWN,
		D_UP,
		D_DOWN,

		CMD_DOWN,
		CMD_BAN,
		END
	};

	struct BuffData
	{
		BUFF_TYPE type;		//�o�t�̎��
		int turn;			//�^�[����
	};

	Buff();
	~Buff();

	void Init(void);
	void Release(void);

	//�o�t�̎擾�֐�
	const std::vector<BuffData>& GetBuff(void) { return buff_; }

	//�o�t�̕t�^
	void SetBuff(const BUFF_TYPE& type);

	//�o�t�̃`�F�b�N
	bool CheckOwnBuff(const BUFF_TYPE& type);

	//��Ԉُ�
	void AbnormalStatus(void);
	//�X�e�[�^�X�ω�
	void ChangeParameter(void);



private:

	//���L�o�t
	std::vector<BuffData>buff_;


};

