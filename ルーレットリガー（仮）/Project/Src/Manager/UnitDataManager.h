#pragma once
#include<string>
#include<vector>
#include<unordered_map>

//ユニットのデータ
struct UnitData
{
	int num;					//ユニット番号
	std::string name;			//名前
	std::string imgPath;		//画像パス・・・ハンドルに入れ替えてもいいかも
	int hp;						//体力
	int attack;					//攻撃力
	int speed;					//素早さ
	std::vector<int> cmdNum;	//コマンド番号
};

class UnitDataManager
{


public:
	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static UnitDataManager& GetInstance(void);

	// 初期化
	void Init(void);

	// 解放
	void Release(void);

	//ユニットデータのロード
	void LoadUnitData(void);

	//指定ユニットの取得（検索）
	const UnitData& GetUnitData(const int& num);

	//指定ユニットの画像取得
	const int& GetUnitImg(const int& num);
private:

	// 静的インスタンス
	static UnitDataManager* instance_;

	// リソース管理の対象
	std::unordered_map<int,UnitData> resMap_;

	// 読み込み済みリソース
	std::unordered_map<int,UnitData> loadedMap_;

	// 外部から生成できない様にする
	UnitDataManager(void);
	// デストラクタも同様
	~UnitDataManager(void);


};

