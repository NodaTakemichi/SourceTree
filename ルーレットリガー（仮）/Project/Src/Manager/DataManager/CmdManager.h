#pragma once
#include<string>
#include<vector>
#include<unordered_map>

struct Parameter
{
	//コマンド名
	std::string name;
	//コマンドタイプ(キャスト前)
	std::string type;
	//ターゲット(キャスト前)
	std::string target;

	//技：倍率
	float times;

	//バフタイプ(キャスト前)
	std::string buff;

	//エフェクト番号
	int efNum;
};

class CmdManager
{

public:
	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static CmdManager& GetInstance(void);

	// 初期化
	void Init(void);

	// 解放
	void Release(void);

	//コマンドデータのロード
	void LoadCmdData(void);

	//指定コマンドの取得（検索）
	const Parameter& GetCmdData(const int& num);

private:
	// 静的インスタンス
	static CmdManager* instance_;

	//ファイル名
	std::string fileName_;
	// コマンドデータ（番号をキー値とする）
	std::unordered_map<int, Parameter> cmdDataMap_;


	// 外部から生成できない様にする
	CmdManager(void);
	// デストラクタも同様
	~CmdManager(void);

};

