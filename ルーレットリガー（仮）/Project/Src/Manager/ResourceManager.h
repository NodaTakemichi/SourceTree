#pragma once
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:

	// リソース名
	enum class SRC
	{

		// 背景画像
		
		// UI画像
		
		// ユニット画像
		
		// バフ画像
		
		// エフェクト
		
		// サウンド
		
		// フォントデータ
		
		// シェーダーデータ
		
	};

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static ResourceManager& GetInstance(void);

	// 初期化
	void Init(void);

	// 解放(シーン切替時に一旦解放)
	void Release(void);




	// リソースのロード
	Resource Load(SRC src);
private:

	// 静的インスタンス
	static ResourceManager* instance_;

	// リソース管理の対象
	std::map<SRC, Resource> resourcesMap_;

	// 読み込み済みリソース
	std::map<SRC, Resource*> loadedMap_;





	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);

	// デストラクタも同様
	~ResourceManager(void);

	// 内部ロード
	Resource* _Load(SRC src);

};

