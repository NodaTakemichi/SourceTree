#include<DxLib.h>
#include<math.h>
#include"../Application.h"
#include"../Utility/AsoUtility.h"
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"

#include"./Unit/Status/Command.h"

#include"../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"

#include "Roulette.h"

Roulette::Roulette()
{
}

Roulette::~Roulette()
{
}

void Roulette::Init(void)
{
	//初期化
	angle = 0.0;
	ResetRouSpin();

	//画像登録
	arrowImg_ = LoadGraph("./Data/Image/UI/arrow.png");
	rouletteImg_ = LoadGraph("./Data/Image/UI/roulette.png");
	rouFrame_ = LoadGraph("./Data/Image/UI/RouFrame.png");
	center_ = LoadGraph("./Data/Image/UI/center.png");

	//フォントの変更
	//fontHandle_=CreateFontToHandle("@ＭＳ 明朝", 22, 10, -1);
	fontHandle_=CreateFontToHandle("@Noto Serif JP Medium", 22, 10, -1);

}

void Roulette::Update(void)
{
	//ルーレットの回転処理
	RotateProcess();
}

void Roulette::Draw(void)
{
	int cx = Application::SCREEN_SIZE_X;
	int cy = Application::SCREEN_SIZE_Y;


	//矢印描画
	DrawGraph(cx / 2-50, 150.0f, arrowImg_, true);

	int rouPosX = cx / 2;
	int rouPosY = 530;


	//ルーレット枠描画
	int x, y;
	GetGraphSize(rouFrame_, &x, &y);
	DrawGraph(rouPosX-x/2, rouPosY-y/2, rouFrame_, true);

	//バイリニア補間モード
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//ルーレット描画
	DrawRotaGraph(rouPosX, rouPosY,
		1.0f, AsoUtility::Deg2RadF(angle), rouletteImg_, true, false);

	//各コマンド技の回転幅、相対回転
	auto rotSpan = AsoUtility::Deg2RadF(
		360.0f / static_cast<float>(cmdNames_.size()));
	auto rotReltive = rotSpan / 2;

	//コマンド技の回転描画
	int i = 0;
	for (auto& cmdName : cmdNames_)
	{
		auto name = cmdName->GetName().c_str();

		//コマンドネーム描画
		DrawRotaStringToHandle(
			rouPosX, rouPosY,		//座標
			1.0, 1.0,				//拡大率
			190.0, 10.0,			//回転の中心座標（相対座標）
			AsoUtility::Deg2RadF(angle) + (i * rotSpan) + rotReltive,	//角度
			0x220022, fontHandle_, 0x0,	//フォント
			true, name);

		//角度をずらす
		i++;
	}


	//ネアレストネイバー法
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//ルーレット中央
	GetGraphSize(center_, &x, &y);
	DrawGraph(rouPosX - x / 2, rouPosY - y / 2, center_, true);

}

void Roulette::Release(void)
{
	DeleteGraph(arrowImg_);
	DeleteGraph(rouletteImg_);

	cmdNames_.clear();

	//作成したフォントハンドルの削除
	DeleteFontToHandle(fontHandle_);
}

void Roulette::StopRoulette(const bool& autom)
{
	if (!isRouSpin_)return;		//既にブレーキ状態なら、処理をしない

	bool stop = false;
	//手動か自動か判断する
	if (autom)
	{
		//時間が来たらブレーキ状態にする
		stop = AsoUtility::OverTime(totalTime_, STOP_WAIT_TIME_ROU);
	}
	else
	{
		//左クリック検知時、ブレーキ状態にする
		auto& ins = InputManager::GetInstance();
		stop = ins.IsTrgMouseLeft();
	}

	if (stop)isRouSpin_ = false;
}

void Roulette::SetCommand(std::vector<Command*> cmd)
{
	cmdNames_ = cmd;
}

void Roulette::ResetRouSpin(void)
{
	//angle = 0.0;		//ルーレットの回転状態を戻さない
	rotPower_ = 0.0;
	isStop_ = false;
	isRouSpin_ = true;
	totalTime_ = 0.0f;
}

Command* Roulette::GetCmd(void)
{
	//回転量
	auto rotAmount = fmod(angle, 360.0) * -1;
	//コマンドの数
	int num = static_cast<double>(cmdNames_.size());
	//決定されたコマンドを判別する
	double angle = 0.0;
	double onwAngle = 360.0 / num;	//一個分の角度
	//角度からコマンドを取得する
	for (size_t i = 0; i <= num; i++)
	{
		//角度の以下以上
		if (angle < rotAmount && rotAmount <= angle + onwAngle)
		{
			//コマンドを返す
			return cmdNames_[i];
		}

		//角度を加算
		angle += onwAngle;
	}
}

void Roulette::RotateProcess(void)
{
	//停止までのブレーキ力
	const float stopSpeed = -ROT_SPEED_MAX / ROT_BRAKE;

	float brake = AsoUtility::Lerp(
		static_cast<float>(rotPower_), 0.0f, 0.1f)*-1.0f;

	//回転量の計算（回転かブレーキで速度変更）
	//回転状態：最高速度、ブレーキ状態：減速した値
	rotPower_ = isRouSpin_ ? ROT_SPEED_MAX : rotPower_ + stopSpeed;



	//停止状態か判断
	if (rotPower_ < 0.1f)
	{
		//回転量を加える
		angle += rotPower_;
	}
	else
	{
		//ルーレット停止状態にする
		isStop_ = true;
	}

}
