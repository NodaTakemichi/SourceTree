#pragma once
#include<vector>
#include<string>

class Vector2;
class EffectManager
{
public:

	//エフェクト情報
	
	
	struct EffectData
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
	std::string EffectLoad(std::string fileName);

	//エフェクトの生成
	void PlayEffect(const int& num,const Vector2& pos);

	//エフェクトが終了しているかどうか
	bool FinishEffect(void);

private:
	//使用エフェクトのハンドル
	int effectHandle_;
	int effectHandle1_;

	//エフェクト情報
	std::vector<EffectData> ef_;

	//再生エフェクト
	int effectPlay_;
	int effectPlay1_;

};

