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


	Buff(const BUFF_TYPE& buff);
	~Buff();

	void Init(void);
	void Release(void);

	//生存判定
	const bool& IsAlive(void)const { return isAlive_; }

	//バフの取得関数
	const BUFF_TYPE& GetBuff(void) const{ return buff_; }

	//バフの所有チェック
	bool CheckOwnBuff(const BUFF_TYPE& type);

	//バフの持続ターン計算
	bool DecBuffTurn(void);

	void SetAlive(bool alive) { isAlive_ = alive; }	//生死状態をセットする


	//状態異常
	void AbnormalStatus(void);
	//ステータス変化
	void ChangeParameter(void);



private:
	//所有判定
	bool isAlive_;

	//所有バフ
	BUFF_TYPE buff_;

	//持続ターン数
	int turn_;

	//バフの付与
	void GiveBuff(const BUFF_TYPE& type);

};

