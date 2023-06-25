#pragma once
#include<vector>
#include<utility>
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
		int target;		//0:全体エフェクト　,1:単体エフェクト
	};

	EffectManager();
	~EffectManager();

	void Init(void);
	void Release(void);

	//使用エフェクトのロード
	std::string EffectLoad(std::string fileName);

	//エフェクトの生成
	void PlayEffect(const int& num,const Vector2& pos);
	void PlayEffect(const int& num,const Vector2& pos, const float& scale);

	//エフェクトが終了しているかどうか
	bool FinishEffect(void);

private:

	//エフェクト情報
	std::vector<EffectData> ef_;

	//エフェクト再生ハンドル（bool ：使用未使用）
	std::vector<std::pair<bool,int>> effectPlays_;

	//再生ハンドルの追加
	void CreatePlayHandle(void);

	//全体攻撃エフェクトの再生
	bool AllTargetEffectPlay(const EffectData& ef, const Vector2& pos);
	bool AllTargetEffectPlay(const EffectData& ef, const Vector2& pos, const float& scale);

};

