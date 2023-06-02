#pragma once
#include<vector>
#include<EffekseerForDXLib.h>
class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	void Init(void);

	void EffectLoad(void);

private:
	//使用エフェクトのハンドル
	std::vector<int>effectHandle_;

};

