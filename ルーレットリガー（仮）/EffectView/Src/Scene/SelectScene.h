#pragma once
#include "SceneBase.h"
class SelectScene :
    public SceneBase
{
public:

	enum class select
	{
		NONE,
		GAME,
		DECK_EDIT,
		EXIT
	};

	// コンストラクタ
	SelectScene(void);

	// デストラクタ
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:


	//背景画像

	//ルーレット画像

	//ルーレット角度
};

