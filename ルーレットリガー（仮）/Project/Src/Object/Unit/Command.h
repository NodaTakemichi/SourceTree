#pragma once
#include<vector>
#include<string>
class Command
{
public:

	//技のタイプ
	enum class CMD_TYPE
	{
		NONE = 0, 
		MISS,
		ATTACK,
		HEAL,
		BUFF,
		CMD_UP,
		END
	};


	//技の対象
	enum class CMD_TARGET
	{
		NONE = 0,
		ENEMY,
		ENEMY_ALL,
		ENEMY_RAND,
		SELF,
		PLAYER,
		PLAYER_ALL,
		END
	};

	struct Par
	{
		//コマンド名
		std::string name_;
		//コマンドタイプ(キャスト前)
		std::string type_;
		//ターゲット(キャスト前)
		std::string target_;
	
		//技：倍率
		float times_;

	};

	Command(Par* par);
	~Command();

	void Init(void);
	//void Update(void);
	//void Draw(void);
	void Release(void);

	//名前の取得
	const std::string& GetName(void) { return par_.name_; }

	//倍率の取得
	const float& GetTimes(void) { return par_.times_; }

	//コマンドタイプの取得
	const CMD_TYPE& GetCmdType(void) { return type_; }

	//ターゲットの取得
	const CMD_TARGET& GetCmdTarget(void) { return target_; }

private:
	//情報
	Par par_;

	//コマンドタイプ
	CMD_TYPE type_;
	//std::vector<CMD_TYPE>types_;


	//ターゲット
	CMD_TARGET target_;


	//スキルタイプ、ターゲットをキャストする
	void CastCmdType(std::string type);
	void CastCmdTarget(std::string target);




};

