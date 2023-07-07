#pragma once
#include<vector>
#include<array>

//戦闘デッキ（最大数：３体）
//using Deck = std::array<int, 3>;

class DeckManager
{
public:
	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static DeckManager& GetInstance(void);

	// 初期化
	void Init(void);

	// 解放
	void Release(void);

	//コマンドデータのロード
	void LoadCmdData(void);

	//デッキ情報の取得
	const std::array<int, 3>& GetDeck(void) { return deck_; }
	//ユニットプール情報の取得
	const std::vector<int>& GetUnitPool(void) { return unitPool_; }

	//デッキ情報のセット
	void SetDeck(std::array<int, 3> deck);

	//ユニットの追加
	void AddUnit(const int& unitNum);

private:
	// 静的インスタンス
	static DeckManager* instance_;

	//デッキカード
	std::array<int, 3> deck_;

	//ユニットプール
	std::vector<int>unitPool_;


	// 外部から生成できない様にする
	DeckManager(void);
	// デストラクタも同様
	~DeckManager(void);

};

