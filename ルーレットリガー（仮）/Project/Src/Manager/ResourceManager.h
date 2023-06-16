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
		START_LOGO,

		//
		// 背景画像
		// UI画像
		// ユニット画像
		// バフ画像
		// 
		// エフェクト
		// 
		// サウンド
		// 
		// フォントデータ
		// シェーダーデータ
		//
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
	//キー値、タイプ、Path
	Resource Load(
		std::string key, Resource::TYPE type, std::string path);

	// リソースの複製ロード(モデル用)
	int LoadModelDuplicate(SRC src);

private:

	// 静的インスタンス
	static ResourceManager* instance_;

	// リソース管理の対象
	//std::map<SRC, Resource> mResourcesMap;
	std::map<std::string, Resource> resourcesMap_;

	// 読み込み済みリソース
	//std::map<SRC, Resource*> mLoadedMap;
	std::map<std::string, Resource*> loadedMap_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);

	// デストラクタも同様
	~ResourceManager(void);

	// 内部ロード
	//Resource* _Load(SRC src);
	Resource* _Load(std::string key);

};

