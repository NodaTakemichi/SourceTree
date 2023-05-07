#pragma once
#include <DxLib.h>
#include<string>
#include<vector>
#include"../../Common/Vector2.h"
#include "./Command.h"

class UnitUI;
class Par;

class UnitBase
{
public:

	//ユニットのタイプ
	enum class UNIT_TYPE
	{
		PLAYER,
		ENEMY,
		END
	};

	//バフのタイプ
	enum class CMD_TYPE
	{
		NONE = 0,
		PALALYSIS,
		POISON,
		CONFUSION,
		AVOIDANCE,

		P_UP,
		P_DOWN,
		S_UP,
		S_DOWN,
		D_UP,
		D_DOWN,

		CMD_DOWN,
		CMD_BAN,
		END
	};


	
	//ゲームシーンで描画するユニットのサイズ
	static constexpr int DRAWING_SIZE = 180;
	//ゲームシーンで描画するユニットのオフセット値
	static constexpr int DRAWING_OFFSET_X = 50;


	UnitBase();
	virtual ~UnitBase();

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);
	

	//スピードの取得関数
	const int& GetSpeed(void) { return speed_; }
	//攻撃力の取得関数
	const int& GetAttack(void) { return attack_; }
	//コマンド取得関数
	const std::vector<Command*> GetCommands(void) { return commands_; }
	//ユニットの順番取得関数
	const int& GetUnitNum(void) { return unitNum_; }
	//ユニットのタイプ取得関数
	const UNIT_TYPE& GetUnitType(void) { return type_; }

	const bool& IsActed(void) { return isActed_; }	//行動済みかどうか
	const bool& IsAlive(void) { return isAlive_; }	//生きているかどうか
	const bool& IsAct(void)   { return isAct_; }	//現在、行動状態かどうか
	const bool& IsTargeted(void)   { return isTargeted_; }	//現在、ロックオン状態かどうか

	void SetActed(bool acted) { isActed_ = acted; }	//行動状態をセットする
	void SetAlive(bool alive) { isAlive_ = alive; }	//生死状態をセットする
	void SetAct(bool act)	  { isAct_ = act; }		//現在の行動状態をセットする
	void SetTargeted(bool target) { isTargeted_ = target; }	//現在のロックオン状態をセットする

	void Damage(int dmg);		//ダメージ関数
	void Heal(int heal);		//回復関数

	bool CheckDead(void);		//死亡判定

protected:
	//ユニットのタイプ
	UNIT_TYPE type_;

	//ユニットデータがあるファイルパス
	std::string unitFile_;

	//ユニット画像
	int unitImg_;
	//ユニットの名前
	std::string name_;

	//ヒットポイント
	int hp_;
	int beforHp_;
	int maxHp_;
	//ユニット：攻撃力
	int attack_;
	//行動速度
	int speed_;

	//コマンド
	std::vector<Command*>commands_;

	//ユニットの順番
	int unitNum_;
	//表示座標
	Vector2 pos_;

	//ユニットUI
	UnitUI* unitUi_;

	//行動済みかどうかの判断
	bool isActed_;
	//生きているかどうかの判断
	bool isAlive_;
	//狙われているかどうか
	bool isTargeted_;

	//現在、行動状態かどうかの判断
	bool isAct_;

	//頂点情報
	VERTEX2DSHADER mVertex[4];
	WORD mIndex[6];
	
	//現在のシェーダーハンドル
	int nowPs_;
	//シェーダーハンドル
	int psTex_;
	int psTexConstBuf_;

	int psMonotone_;
	int psMonotoneConstBuf_;

	//描画用の四角頂点のの作成
	void MakeSquereVertex(Vector2 pos);

	//表示する座標のセット
	void SetDrawingPos(int posX);

	//ユニットデータの取得（xmlデータの読み込み）
	std::string LoadData(std::string fileName);


	//シェーダ―によるユニット描画
	void DrawUnitShader(const int& shader ,const float& revers);


private:


	//コマンドの生成
	void CreateCommand(Command::Par* par);

};



