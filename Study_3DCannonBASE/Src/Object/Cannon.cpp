#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "./ShotBase.h"
#include "Cannon.h"

Cannon::Cannon()
{
}

Cannon::~Cannon()
{
}

void Cannon::Init(void)
{
	//�����G�t�F�N�g�ǂݍ���
	LoadDivGraph((Application::PATH_IMAGE + "Blast.png").c_str(),
		BLAST_ANIM_NUM, 4,4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImgs_, true);

	//3D��{���̏�����
	//�y��
	standModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Stand.mv1").c_str());
	standScl_ = { 0.8f, 0.8f, 0.8f };
	standRot_ = { 0.0f, 0.0f, 0.0f };
	standPos_ = { 0.0f, 10.0f, -200.0f };

	//���΍��W
	barrelLocalos_ = { 0.0f, 100.0f, 0.0f };
	//�C�g
	barrelModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Barrel.mv1").c_str());
	barrelScl_ = { 0.8f, 0.8f, 0.8f };
	barrelRot_ = { 0.0f, 0.0f, 0.0f };
	barrelPos_ = VAdd(standPos_, barrelLocalos_);

	//�e
	shotModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Shot.mv1").c_str());
	stepShotDelay_ = 0.0f;

	//�����ݒ�����f���ɔ��f
	Update();
}

void Cannon::Update(void)
{
	//�C�g�̉�]����
	ProcessRot();

	//����
	ProcessShot();

	//�y��
	MV1SetScale(standModelId_, standScl_);
	MV1SetPosition(standModelId_, standPos_);
	MV1SetRotationXYZ(standModelId_, standRot_);

	//�C�g
	MV1SetScale(barrelModelId_, barrelScl_);
	MV1SetPosition(barrelModelId_, barrelPos_);
	MV1SetRotationXYZ(barrelModelId_, barrelRot_);

}

void Cannon::Draw(void)
{
	MV1DrawModel(standModelId_);
	MV1DrawModel(barrelModelId_);

#ifdef DEBUG


	// �e�̔��ˈʒu
	VECTOR pos = barrelPos_;
	// �C�g����̑��΍��W
	VECTOR localPos = { 0.0f, 25.0f, 30.0f };

	MATRIX matRot = MGetIdent();
	matRot = MMult(matRot, MGetRotX(barrelRot_.x));
	matRot = MMult(matRot, MGetRotY(barrelRot_.y));
	matRot = MMult(matRot, MGetRotZ(barrelRot_.z));
	VECTOR localRotPos = VTransform(localPos, matRot);

	// ���[�J�����W���烏�[���h���W�֕ϊ�
	pos = VAdd(pos, localRotPos);
	// �e�̔��ˈʒu�ڈ�
	DrawSphere3D(pos, 10.0f, 10, 0x00ff00, 0x00ff00, true);
	// �C��̃��f���`��
	MV1DrawModel(standModelId_);
	// �C�g�̃��f���`��(�ꎞ�I�ɔ������ɂ���)
	MV1SetMaterialDifColor(barrelModelId_, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.5f));
	MV1DrawModel(barrelModelId_);
#endif // _DEBUG

}

void Cannon::Release(void)
{
	MV1DeleteModel(standModelId_);
	MV1DeleteModel(barrelModelId_);
	MV1DeleteModel(shotModelId_);

	for (auto shot : shots_)
	{
		shot->Release();
		delete shot;
	}

	for (int i = 0; i < BLAST_ANIM_NUM; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}
}

void Cannon::ProcessRot(void)
{
	auto& ins = InputManager::GetInstance();

	//��]��
	auto rotPow = 1.0f * DX_PI_F / 180.0f;

	//���E
	if (ins.IsNew(KEY_INPUT_LEFT))standRot_.y -= rotPow;
	if (ins.IsNew(KEY_INPUT_RIGHT))standRot_.y += rotPow;
	barrelRot_.y = standRot_.y;

	//�㉺
	if ((barrelRot_.x <= MAX_ANGLE_X) && (ins.IsNew(KEY_INPUT_DOWN)))barrelRot_.x += rotPow;
	if ((barrelRot_.x > MN_ANGLE_X) && (ins.IsNew(KEY_INPUT_UP)))barrelRot_.x -= rotPow;
}

void Cannon::ProcessShot(void)
{
	auto& ins = InputManager::GetInstance();

	//�C�g�̕���
#pragma region �s��
	//�@��]�s������
	//�P�ʍs��
	MATRIX matRot = MGetIdent();

	///���ꂼ��̎��̍s������A����ɍs�����������
	matRot = MMult(matRot, MGetRotX(barrelRot_.x));
	matRot = MMult(matRot, MGetRotY(barrelRot_.y));
	matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

	//�A��������]������
	//��]�s����g�p���āA�x�N�g������]������
	VECTOR dir = VTransform({ 0.0f,0.0f,1.0f }, matRot);

	// �e�̔��ˈʒu
	VECTOR pos = barrelPos_;
	// �C�g����̑��΍��W
	VECTOR localPos = { 0.0f, 25.0f, 30.0f };
	VECTOR localRotPos = VTransform(localPos, matRot);
	// ���[�J�����W���烏�[���h���W�֕ϊ�
	pos = VAdd(pos, localRotPos);
#pragma endregion


	//����
	if (ins.IsNew(KEY_INPUT_Z) && stepShotDelay_ <= 0.0f)
	{
		// �L���Ȓe���擾����
		ShotBase* shot = GetValidShot();
		// �e�𐶐�
		shot->CreateShot(pos, dir);
		// �e���ˌ�̍d�����ԃZ�b�g
		stepShotDelay_ = SHOT_DELAY;
	}

	// �e���ˌ�̍d�����Ԃ����炵�Ă���
	if (stepShotDelay_ > 0.0f) {
		stepShotDelay_ -= 1.0f / SceneManager::DEFAULT_FPS;
	}
}

ShotBase* Cannon::GetValidShot(void)
{
	//�g���Ă��Ȃ��e����������A�ė��p����
	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		if (!shots_[i]->IsAlive())
		{
			return shots_[i];
		}
	}

	//�g���Ă��Ȃ��e���Ȃ��ꍇ�A�V�������
	ShotBase* shot = new ShotBase(shotModelId_, blastImgs_, BLAST_ANIM_NUM);
	shots_.push_back(shot);
	return shot;
}

std::vector<ShotBase*> Cannon::GetShots(void)
{
	return shots_;
}
