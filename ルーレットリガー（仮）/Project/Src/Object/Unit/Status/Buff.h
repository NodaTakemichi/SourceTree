#pragma once
#include<vector>
//#include<array>
class Buff
{
public:
	//バフのタイプ
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
		BUFF_TYPE type;		//バフの種類
		int turn;			//ターン数
	};

	Buff();
	~Buff();

	void Init(void);
	void Release(void);

	//バフの取得関数
	const std::vector<BuffData>& GetBuff(void) { return buff_; }

	//バフの付与
	void SetBuff(const BUFF_TYPE& type);

	//バフのチェック
	bool CheckOwnBuff(const BUFF_TYPE& type);

	//状態異常
	void AbnormalStatus(void);
	//ステータス変化
	void ChangeParameter(void);



private:

	//所有バフ
	std::vector<BuffData>buff_;


};

