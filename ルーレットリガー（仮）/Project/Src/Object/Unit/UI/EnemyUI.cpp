#include "EnemyUI.h"

EnemyUI::EnemyUI(Vector2 pos, std::string& name, int& hp, int& maxHp, int& beforHp) :
	unitPos_(pos), name_(name), hp_(hp), maxHp_(maxHp), beforHp_(beforHp)
{
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::Init(void)
{
	//������
	UnitUI::Init();


	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	//HP�\�����W
	Vector2 pos = { unitPos_.x + unitSize - 10, unitPos_.y + 20 };
	//�l�p�`�|���S���̐���(HP�p)
	MakeSquereVertex(pos);

	nowHp_ = hp_;

}

void EnemyUI::Draw(void)
{
	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);


	//���O�`��
	DrawName(name_, unitPos_);




	//HP��0�ȉ��̎��AHP�Q�[�W��`�悵�Ȃ�
	if (hp_ <= 0)return;

	//HP�g�̕\��
	Vector2 pos = { unitPos_.x + unitSize - 10,unitPos_.y + 20 };
	auto frame = 2;
	DrawBox(pos.x - frame, pos.y - frame,
		pos.x + HP_GAUGE_X + frame, pos.y + HP_GAUGE_Y + frame,
		0xffffff, true);


	auto test = 1.0f;
	//HP�ω�������Ƃ��̂�
	if (nowHp_ > hp_)
	{
		//�i�������鎞�ԁ[�o�ߎ��ԁj/�����鎞��
		auto delet = SceneManager::GetInstance().GetDeltaTime();
		totalTime_ += delet;
		test = (1.5f - totalTime_) / 1.5f;
		if (test >= 1.0f)
		{
			test = 1.0f;
			totalTime_ = 0.0f;
			nowHp_ = hp_;
		}
		//BeforHP������
		nowHp_ = AsoUtility::Lerp(hp_, beforHp_, test);

	}
	else
	{
		test = 1.0f;
		totalTime_ = 0.0f;
		nowHp_ = hp_;
	}

	//HP�̊���
	float ratio = static_cast<float>(nowHp_) / static_cast<float>(maxHp_);

	//HP�V�F�[�_�[
	COLOR_F color = { 0.8f,0.4f,0.4f,1.0f };
	DrawHpShader(ratio, color);

}

void EnemyUI::DrawActUnit(void)
{
	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 pos = { unitPos_.x - 20,unitPos_.y + unitSize / 2 };
	DrawCircle(pos.x, pos.y, 12, 0xff8888, true);
}

void EnemyUI::DrawRockOn(void)
{
	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 pos = { unitPos_.x - 20,unitPos_.y + unitSize / 2 + 20 };
	DrawCircle(pos.x, pos.y, 12, 0x8888ff, true);

}
