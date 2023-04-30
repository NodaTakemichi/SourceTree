#pragma once
#include<vector>
#include<string>
class Command;

class Roulette
{
public:
	//回転速度
	const float ROT_SPEED_MAX = -16.0f;

	Roulette();
	~Roulette();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//ルーレットにコマンド技をセットする
	void SetCommand(std::vector<Command*> cmd);

	//ルーレットの回転状況をリセットする
	void ResetRouSpin(void);

	//ルーレットの停止状態の取得関数
	bool GetRouStop(void) { return isStop_; }

	//決定したコマンドの取得
	Command* GetCmd(void);

private:

	//ルーレット画像
	int rouletteImg_;
	//矢印画像
	int arrowImg_;

	//回転角度
	double angle;
	//回転量
	double rotPower_;

	//ルーレットの回転状況
	bool isRouSpin_;
	//ルーレットが停止状態か判断
	bool isStop_;


	//フォントハンドル
	int fontHandle_;

	//コマンド技
	std::vector<Command*>cmdNames_;

	//ルーレットの回転処理
	void RotateProcess(void);


};

