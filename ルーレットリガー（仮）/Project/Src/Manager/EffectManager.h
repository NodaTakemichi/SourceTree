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
	//�g�p�G�t�F�N�g�̃n���h��
	std::vector<int>effectHandle_;

};

