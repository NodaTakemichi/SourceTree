#pragma once
#include <DxLib.h>
#include<string>
#include<vector>
#include"../../Common/Vector2.h"
#include "./Status/Command.h"
#include "./Status/Buff.h"

class UnitUI;


class UnitBase
{
public:
	//ゲームシーンで描画するユニットのサイズ
	static constexpr int DRAWING_SIZE = 180;
	//ゲームシーンで描画するユニットのオフセット値
	static constexpr int DRAWING_OFFSET_X = 100;

	//ユニットのタイプ
	enum class UNIT_TYPE
	{
		PLAYER,
		ENEMY,
	};

	UnitBase(const int& dataNum,const int& unitNum);
	virtual ~UnitBase();

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);
	
	
	bool DecHpProcess(void);	//ダメージ減少処理
	void TurnEndProcess(void);	//行動終了後の処理

	//バフによるステータスの計算
	int CalcBuffStatus(const int& status, const Buff::BUFF_TYPE& up, const Buff::BUFF_TYPE& down);

	//スピードの取得関数
	const int& GetSpeed(void);
	//攻撃力の取得関数
	const int& GetAttack(void);
	//ユニットの順番取得関数
	const int& GetUnitNum(void) const { return unitNum_; }
	//ユニットの名前取得関数
	const std::string& GetUnitName(void) const { return name_; }
	//ユニットの座標取得関数
	const Vector2& GetUnitPos(void) const { return pos_; }
	//ユニットのタイプ取得関数
	const UNIT_TYPE& GetUnitType(void) const { return type_; }
	//コマンド取得関数
	const std::vector<Command*> GetCommands(void) const { return commands_; }
	//バフ取得関数
	const std::vector<Buff*> GetBuffs(void) const{ return buffs_; }


	const bool& IsActed(void) { return isActed_; }	//行動済みかどうか
	const bool& IsAlive(void) { return isAlive_; }	//生きているかどうか
	const bool& IsAct(void)   { return isAct_; }	//現在、行動状態かどうか
	const bool& IsTargeted(void)   { return isTargeted_; }	//現在、ロックオン状態かどうか

	void SetActed(bool acted) { isActed_ = acted; }	//行動状態をセットする
	void SetAlive(bool alive) { isAlive_ = alive; }	//生死状態をセットする
	void SetAct(bool act)	  { isAct_ = act; }		//現在の行動状態をセットする
	void SetTargeted(bool target) { isTargeted_ = target; }	//現在のロックオン状態をセットする

	void Damage(const int& dmg);				//ダメージ関数
	void Heal(const int& heal);					//回復関数
	void GiveBuff(const Buff::BUFF_TYPE& type);	//バフ付与関数

	bool CheckDead(void);		//死亡判定
	bool CheckOwnBuff(const Buff::BUFF_TYPE& type);	//指定のバフを所有してるかどうか

	//バフシェーダーを再生する
	void PlayBuffShader(void);


protected:
	//ユニットUI
	UnitUI* unitUi_;

	//ユニットのデータ番号
	const int& dataNum_;
	//ユニットの順番
	const int& unitNum_;


	//ユニットのタイプ
	UNIT_TYPE type_;

	//ユニット画像
	int unitImg_;
	//ユニットの名前
	std::string name_;

	//ヒットポイント
	int hp_;
	int beforHp_;
	int changeHp_;
	int maxHp_;
	//ユニット：攻撃力
	int attack_;
	//行動速度
	int speed_;


	//コマンド
	std::vector<Command*>commands_;
	//バフ
	std::vector <Buff*> buffs_;

	//表示座標
	Vector2 pos_;


	bool isActed_;		//行動済みかどうかの判断
	bool isAlive_;		//生きているかどうかの判断
	bool isTargeted_;	//狙われているかどうか
	bool isAct_;		//現在、行動状態かどうかの判断

	//経過時間
	float totalTime_;

	//画像の揺れ幅
	float shakeX_;
	//振幅度
	float shakeValue_;
	//振動による移動値
	float movePow_;





	//シェーダー関連
	//現在のシェーダーハンドル
	int nowPs_;
	//シェーダーハンドル
	//通常描画
	int psTex_;
	int psTexConstBuf_;

	//モノクロ描画
	int psMonotone_;
	int psMonotoneConstBuf_;

	//ベイヤーディザ描画
	int psBayerDithe_;
	int psBayerDitheConstBuf_;

	//ステータスアップ
	int psStatusUp_;
	//ステータスダウン
	int psStatusDown_;
	//麻痺
	int psParalysis_;
	//毒
	int psPoison_;
	//回避
	int psAvoidance_;




	//表示する座標のセット
	void SetDrawingPos(int posX);

	//ユニットデータの取得（xmlデータの読み込み）
	void LoadData(void);

	//シェーダ―によるユニット描画
	void DrawUnitShader(const float& revers);


private:

	//ユニットの画像の振動
	void UnitImgShake(const float& leap);

	//コマンドの生成
	void CreateCommand(const int& num);

	//バフの生成
	void CreateBuff(const Buff::BUFF_TYPE& type);
	//有効なバフを取得
	Buff* GetValidBuff(void);

};



