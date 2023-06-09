#pragma once
#include<vector>
#include<EffekseerForDXLib.h>

class Vector2;
class EffectManager
{
public:

	//エフェクト情報
	struct Effect
	{
		int num;		//エフェクトナンバー
		int handle;		//エフェクトハンドル
		float scale;	//大きさ
		Vector2 offset;	//オフセット座標
	};

	EffectManager();
	~EffectManager();

	void Init(void);
	void Release(void);

	//使用エフェクトのロード
	void EffectLoad(void);

	//エフェクトの生成
	void PlayEffect(const int& num,const Vector2& pos);

	//エフェクトが終了しているかどうか
	bool FinishEffect(void);

private:
	//使用エフェクトのハンドル
	int effectHandle_;

	//エフェクト情報
	std::vector<Effect> ef_;

	//再生エフェクト
	int effectPlay_;

};

