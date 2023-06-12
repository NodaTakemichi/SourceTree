#include <algorithm>
#include "../../Manager/SceneManager.h"
#include "../../Utility/AsoUtility.h"


#include "../../Common/GetAttr.h"
#include "./UI/UnitUI.h"

#include"../../_debug/_DebugConOut.h"

#include "UnitBase.h"

UnitBase::UnitBase()
{
}

UnitBase::~UnitBase()
{
}

void UnitBase::Init(void)
{
	//������ԁA�s����ԁA���ݍs����Ԃ��Z�b�g����
	SetAlive(true);
	SetActed(false);
	SetAct(false);
	SetTargeted(false);

	//�e�N�X�`���\�V�F�[�_�[�̓o�^
	//psHpColor_ = LoadPixelShader("./Data/Shader/HpShader.cso");
	psTex_ = LoadPixelShader("./x64/Debug/Texture.cso");
	psMonotone_ = LoadPixelShader("./x64/Debug/Monotone.cso");
	psBayerDithe_ = LoadPixelShader("./x64/Debug/BayerDithe.cso");

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psTexConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 4);

	//���݂̃V�F�[�_�[
	nowPs_ = psTex_;

	//���v����
	totalTime_ = 0.0f;

	//�h�ꕝ
	shakeX_ = 0.0f;
	shakeValue_ = 0.0f;
	movePow_ = 0.0f;

}

void UnitBase::Update(void)
{



}

void UnitBase::Draw(void)
{
	//�s�������j�b�g
	if (IsAct())unitUi_->DrawActUnit();

	//�_���Ă��郆�j�b�g
	if (IsTargeted())unitUi_->DrawRockOn();

}

void UnitBase::Release(void)
{
	//���
	unitUi_->Release();

	//�摜�̉��
	DeleteGraph(unitImg_);

	//�V�F�[�_�[�̉��
	DeleteShader(psTex_);
	DeleteShader(psMonotone_);
	DeleteShader(psBayerDithe_);
	//�V�F�[�_�[�̒萔�o�b�t�@�̉��
	DeleteShaderConstantBuffer(psTexConstBuf_);
	DeleteShaderConstantBuffer(psMonotoneConstBuf_);
	DeleteShaderConstantBuffer(psBayerDitheConstBuf_);
}

bool UnitBase::DecHpProcess(void)
{
	//HP�ω������鎞�A����HP���O�ȏ�̎��̂�
	if (nowHp_ != hp_ && nowHp_ >= 0)
	{
		auto changeTime = 1.0f;		//��������

		//�o�ߎ���
		totalTime_ += SceneManager::GetInstance().GetDeltaTime();
		//�o�߁@���i�������鎞�ԁ[�o�ߎ��ԁj/�������鎞��
		auto progress = 1.0f - (changeTime - totalTime_) / changeTime;

		//�_���[�W��ƃ_���[�W�O�̐��`��Ԃ��s��
		nowHp_ = AsoUtility::Lerp(beforHp_, hp_, progress);

		//�摜��h�炷
		if (hp_ < nowHp_)UnitImgShake(progress);

		//���߂��Ă���A��������HP������HP�ɒǂ�������
		if (progress >= 1.0f || nowHp_ == hp_)
		{
			//�_���[�W�\�L���\������
			unitUi_->SetDmg(false, 0);
			//�o�ߎ��Ԃ̃��Z�b�g
			totalTime_ = 0.0f;

			//HP�����F�I��
			return true;
		}
		//HP�����F���I��
		return false;
	}
	//HP�����F����
	return true;
}

void UnitBase::TurnEndProcess(void)
{
	for (auto& buff : buffs_)
	{
		if (!buff->IsAlive())continue;

		//�Ń_���[�W�̏���
		if (buff->CheckOwnBuff(Buff::BUFF_TYPE::POISON))
		{
			TRACE("�Ń_���[�W\n");

			//�ő�HP�� 1/8 �̃_���[�W
			int dmg = maxHp_ / 8;
			Damage(dmg);
		}

		//�o�t�̃^�[������������
		if (buff->DecBuffTurn())
		{
			//�����^�[�����I��������A�o�t�𖳌���Ԃɂ���
			buff->SetAlive(false);
		}
	}
}

const int& UnitBase::GetSpeed(void)
{
	//�o�t���݂̃X�s�[�h�v�Z
	auto nowSpeed = CalcBuffStatus(
		speed_, Buff::BUFF_TYPE::S_UP, Buff::BUFF_TYPE::S_DOWN);

	return nowSpeed;
}

const int& UnitBase::GetAttack(void)
{
	//�o�t���݂̍U���͌v�Z
	auto nowAttack = CalcBuffStatus(
		attack_, Buff::BUFF_TYPE::A_UP, Buff::BUFF_TYPE::A_DOWN);

	return nowAttack;
}

int UnitBase::CalcBuffStatus(const int& status, const Buff::BUFF_TYPE& up, const Buff::BUFF_TYPE& down)
{
	float value = static_cast<float>(status);

	//�o�t�̌v�Z
	for (auto buff : buffs_)
	{
		if (!buff->IsAlive())continue;

		//�X�e�[�^�X�A�b�v
		if (buff->CheckOwnBuff(up))value *= 1.2;
		//�X�e�[�^�X�_�E��
		if (buff->CheckOwnBuff(down))value *= 0.8;
	}

	return static_cast<int>(floor(value));
}

void UnitBase::Damage(const int& dmg)
{
	TRACE(name_.c_str());
	TRACE("\n�U���l�F%d ||", dmg);

	//�o�t���݂̃_���[�W�v�Z
	auto calcDmg = CalcBuffStatus(
		dmg, Buff::BUFF_TYPE::D_DOWN, Buff::BUFF_TYPE::D_UP);

	//�_���[�W�̗����v�Z
	float randNum = static_cast<float>(
		SceneManager::GetInstance().GetRand(90, 100)) / 100.0f;
	calcDmg = AsoUtility::Round(static_cast<float>(calcDmg) * randNum);

	TRACE("��_���l�F%d\n", calcDmg);

	//���OHP�̕ێ�
	beforHp_ = hp_;

	//�_���[�W�v�Z
	hp_ -= calcDmg;

	//�c��̗�
	TRACE("�c��̗�:%d\n\n",hp_);

	//�_���[�W�\�L��\������
	unitUi_->SetDmg(true, calcDmg);

	//�摜�̗h�ꕝ�̌���
	shakeValue_ = 50.0f;
	movePow_ = 20.0f;


	//���S����
	if (CheckDead())
	{
		TRACE("���S���܂���\n");

		//�V�F�[�_�[�̕ύX
		nowPs_ = psMonotone_;

		//���S��Ԃɂ���
		SetAlive(false);
	}
}

void UnitBase::Heal(const int& heal)
{
	//���OHP�̋L��
	beforHp_ = hp_;

	//HP�v�Z(HP�������)
	hp_ += heal;
	hp_ = (std::min)(hp_, maxHp_);
}

void UnitBase::GiveBuff(const Buff::BUFF_TYPE& type)
{
	//�o�t�̐���
	CreateBuff(type);

	//UI�Ƀo�t�̓o�^
	unitUi_->SetBuff(buffs_);
}

bool UnitBase::CheckDead(void)
{
	//���S����
	if (hp_ <= 0)
	{
		return true;
	}
	return false;
}

bool UnitBase::CheckOwnBuff(const Buff::BUFF_TYPE& type)
{
	for (auto& buff : buffs_)
	{
		if (!buff->IsAlive())continue;

		//�w��o�t�����L���Ă���
		if (buff->CheckOwnBuff(type))return true;
	}
	return false;
}

std::string UnitBase::LoadData(std::string fileName)
{
	//�h�L�������g��ۑ�����ϐ�
	rapidxml::xml_document<> actDoc;
	//�t�@�C���̃I�[�v��
	rapidxml::file<>xmlFile = fileName.c_str();
	//��͍\�����āA�ϐ��Ƀf�[�^���i�[
	actDoc.parse<0>(xmlFile.data());

	//tmx�̏����擾�i���g�ɃA�N�Z�X�j
	auto unit = actDoc.first_node("Unit");
	if (unit == nullptr)return std::string();

	//�A�g���r���[�g�擾�֐�
	auto getAttr = GetAttr();
	
	//�摜�̃\�[�X�p�X
	std::string source;

	//���j�b�g�̃f�[�^�̎擾
#pragma region ���j�b�g�̊�{���
	auto data = unit->first_node();
	if (data == nullptr)return std::string();
	//���j�b�g�̖��O�擾
	if (!getAttr(data, "name", name_))return std::string();
	//���j�b�g�̉摜�p�X�擾
	if (!getAttr(data, "source", source))return std::string();
	//���j�b�g��HP�擾
	if (!getAttr(data, "hp", hp_))return std::string();
	//���j�b�g�̍U���͎擾
	if (!getAttr(data, "attack", attack_))return std::string();
	//���j�b�g�̃X�s�[�h�擾
	if (!getAttr(data, "speed", speed_))return std::string();
	//���j�b�g�̃X�s�[�h�擾
	if (!getAttr(data, "speed", speed_))return std::string();
#pragma endregion

	

	//���j�b�g�̃R�}���h�Z�擾
	std::string name, type, target,buff;
	double times = 0.0;
	int efNum = 0;

	auto cmd = unit->first_node("Cmd");


	if (cmd == nullptr)return std::string();
	for (auto skill = cmd->first_node();
		skill != nullptr;
		skill = skill->next_sibling())
	{
		//�Z�̖��O�擾
		if (!getAttr(skill, "name", name))name = std::string();
		//�Z�̃^�C�v�擾
		if (!getAttr(skill, "type", type))type = std::string();
		//�Z�̋Z�Ώێ擾
		if (!getAttr(skill, "target", target))target = std::string();
		//�Z�̔{���擾
		if (!getAttr(skill, "times", times))times = 0.0;

		//�o�t�̎�ގ擾
		if (!getAttr(skill, "buff", buff))buff = "NONE";

		//�G�t�F�N�g�ԍ��擾
		if (!getAttr(skill, "efNum", efNum))efNum = 0;


		//�R�}���h�̐���
		Command::Par par = {
			name,
			type,
			target,
			static_cast<float>(times),
			buff,
			efNum
		};
		CreateCommand(&par);
	}


	//HP�֘A�̏�����
	maxHp_ = beforHp_= nowHp_ = hp_;

	//�摜�̓o�^
	unitImg_ = LoadGraph(source.c_str());
	return std::string();

}

void UnitBase::DrawUnitShader(const int& shader, const float& revers)
{
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(shader);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, unitImg_);

	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psTexConstBuf_;

	auto time = SceneManager::GetInstance().GetTotalTime();

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = revers;
	cbBuf->g = time;

	//�`����W
	Vector2 shakePos = { pos_.x + static_cast<int>(shakeX_),pos_.y };
	MakeSquereVertex(shakePos);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


}

void UnitBase::UnitImgShake(const float& leap)
{
	if (leap >= 0.6f)
	{
		shakeX_ = 0.0f;
		return;
	}

	//�摜���W�̐U���l���Z
	shakeX_ += movePow_;

	// �l���ő�l�܂��͍ŏ��l�𒴂����ꍇ�A���]������
	if (shakeValue_ <= shakeX_ || (shakeValue_ * -1) >= shakeX_)
	{
		//���]
		movePow_ *= -0.8;

		//�U���l������������
		shakeValue_ *= (1.0f - leap);

		auto i = 1;
		if ((shakeValue_ * -1) >= shakeX_)i = -1;
		shakeX_=shakeValue_* i + movePow_;
	}
}

void UnitBase::CreateCommand(Command::Par* par)
{
	//�R�}���h�̐���
	auto cmd = new Command(par);
	cmd->Init();
	commands_.push_back(cmd);
}

void UnitBase::CreateBuff(const Buff::BUFF_TYPE& type)
{
	//�����������o�t�̏ꍇ�A�Ώ��ł�����
	for (auto& buff : buffs_)
	{
		//����ł�����A���������Ȃ�
		if (!buff->IsAlive())continue;

		//�d�����Ă����ꍇ�A�ǉ����Ȃ�
		if (buff->GetBuff() == type)return;

		auto checkBuff = [&](Buff::BUFF_TYPE get, Buff::BUFF_TYPE give) {
			if (buff->GetBuff() == get)
			{
				if (type == give)
				{
					//����
					buff->SetAlive(false);

					//���������ɁA�������I��
					return true;
				}
			}
			return false;
		};

		//�����������o�t
		if (checkBuff(Buff::BUFF_TYPE::A_UP, Buff::BUFF_TYPE::A_DOWN))return;
		if (checkBuff(Buff::BUFF_TYPE::A_DOWN, Buff::BUFF_TYPE::A_UP))return;
		if (checkBuff(Buff::BUFF_TYPE::D_UP, Buff::BUFF_TYPE::D_DOWN))return;
		if (checkBuff(Buff::BUFF_TYPE::D_DOWN, Buff::BUFF_TYPE::D_UP))return;
		if (checkBuff(Buff::BUFF_TYPE::S_UP, Buff::BUFF_TYPE::S_DOWN))return;
		if (checkBuff(Buff::BUFF_TYPE::S_DOWN, Buff::BUFF_TYPE::S_UP))return;
	}

	//�o�t�̐���
	auto buff = GetValidBuff();
	buff->CreateBuff(type);

}

Buff* UnitBase::GetValidBuff(void)
{
	//�g���Ă��Ȃ��o�t��������A�ė��p
	size_t size = buffs_.size();
	for (int i = 0; i < size; i++)
	{
		if (buffs_[i]->IsAlive())continue;
		//���p�ł���o�t��Ԃ�
		return buffs_[i];
	}

	//�V�����o�t�𐶐�
	Buff* buff = new Buff();
	buffs_.push_back(buff);

	return buff;
}

void UnitBase::MakeSquereVertex(Vector2 pos)
{
	//�O�p�`�̃|���S����2����āA�������Ă���

	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + DRAWING_SIZE - 1);
	float eY = static_cast<float>(pos.y + DRAWING_SIZE - 1);

	// �S���_�̏�����
	for (int i = 0; i < 4; i++)
	{
		vertex_[i].rhw = 1.0f;
		vertex_[i].dif = GetColorU8(255, 255, 255, 255);
		vertex_[i].spc = GetColorU8(255, 255, 255, 255);
		vertex_[i].su = 0.0f;
		vertex_[i].sv = 0.0f;
	}

	// ����
	vertex_[cnt].pos = VGet(sX, sY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// �E��
	vertex_[cnt].pos = VGet(eX, sY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// �E��
	vertex_[cnt].pos = VGet(eX, eY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 1.0f;
	cnt++;

	// ����
	vertex_[cnt].pos = VGet(sX, eY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 1.0f;

	// ���_�C���f�b�N�X
	cnt = 0;
	index_[cnt++] = 0;
	index_[cnt++] = 1;
	index_[cnt++] = 3;

	index_[cnt++] = 1;
	index_[cnt++] = 2;
	index_[cnt++] = 3;

}

void UnitBase::SetDrawingPos(int x)
{
	
	auto topY = 40;
	auto spanY = 180;

	if (unitNum_ == 1)pos_ = { x, topY + spanY };
	else if (unitNum_ == 2)pos_ = { x,topY };
	else if (unitNum_ == 3)pos_ = { x,topY + spanY * 2 };

	MakeSquereVertex(pos_);
	
	return;
}
