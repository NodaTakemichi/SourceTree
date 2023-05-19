#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"
#include "EnemyBase.h"
EnemyBase::EnemyBase()
{
	//�V�F�[�_�[�̓o�^
	psHpShader_ = LoadPixelShader("./HpShader.pso");
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psHpShaderConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 4);

	MakeSquereVertex({ 0,0 });
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(void)
{
	SetParam();
	Update();
}

void EnemyBase::SetParam(void)
{
	// �g�p�������e�ʂƓǂݍ��ݎ��Ԃ̍팸�̂���
	// ���f���f�[�^����������������ɑ��݂����Ȃ�

	// �p�x�̐ݒ�
	rot_ = { 0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f };
	// �ʒu�̐ݒ�
	pos_ = { -320.0f, 30.0f, 75.0f };
	// �E�����Ɉړ�����
	dir_ = { 1.0f, 0.0f, 0.0f };
	// �����͐������
	SetAlive(true);

	// �Đ����̃A�j���[�V��������
	stepAnim_ = 0.0f;
	// �A�j���[�V�������x
	speedAnim_ = 30.0f;

	//���v����
	hpLerpTime_ = 0.0f;
	totalTime_ = 0.0f;

	//�L�����ʂɏ���������
	auto parInit = [&](std::string pass ,float scale,float speed,
		int animNo,int hp,float colRadius,float colLocalPos) {
		//���f���̓o�^
		modelId_ = MV1LoadModel(
			(Application::PATH_MODEL + pass.c_str()).c_str());

		// �傫���̐ݒ�
		scl_ = { scale, scale, scale };

		// �ړ��X�s�[�h
		speed_ = speed;

		// �A�j���[�V�������A�^�b�`����
		animAttachNo_ = MV1AttachAnim(modelId_, animNo);
		// �A�^�b�`���Ă���A�j���[�V�����̑��Đ����Ԃ��擾����
		animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

		// HP�̐ݒ�
		hp_ = hpMax_ = hpNow_ = hpBefore_ = hp;
		// �Փ˔���p�̋��̔��a
		collisionRadius_ = colRadius;
		// �Փ˔���p�̋��̒��S�̒������W
		collisionLocalPos_ = { 0.0f, colLocalPos, 0.0f };

	};

	switch (type_)
	{
	case EnemyBase::ENEMY_TYPE::SMALL:
		parInit("Enemy/Birb.mv1",0.3f, 1.5f, 10, 4, 35.0f, 50.0f);
		break;
	case EnemyBase::ENEMY_TYPE::MEDIUM:
		parInit("Enemy/Birb.mv1",0.3f, 1.2f, 10, 4, 40.0f, 50.0f);
		break;
	case EnemyBase::ENEMY_TYPE::BAT:
		break;
	case EnemyBase::ENEMY_TYPE::BIG:
		parInit("Enemy/Ghost.mv1",1.0f, 1.0f, 6, 6, 100.0f, 150.0f);
		break;
	default:
		break;
	}
}

void EnemyBase::Update(void)
{
	//������Ԃ���Ȃ���΁A���������Ȃ�
	if (!IsAlive())return;

	//���v����
	totalTime_ += SceneManager::GetInstance().GetDeltaTime();

	// �A�j���[�V�����Đ�
	// �o�ߎ��Ԃ̎擾
	float deltaTime = 1.0f / SceneManager::DEFAULT_FPS;
	// �A�j���[�V�������Ԃ̐i�s
	stepAnim_ += (speedAnim_ * deltaTime);
	if (stepAnim_ > animTotalTime_)
	{
		// ���[�v�Đ�
		stepAnim_ = 0.0f;
	}
	// �Đ�����A�j���[�V�������Ԃ̐ݒ�
	MV1SetAttachAnimTime(modelId_, animAttachNo_, stepAnim_);
	//�ړ���
	auto movePow = VScale(dir_, speed_);
	//�ړ�����
	pos_ = VAdd(pos_, movePow);


	//3D��{���̍X�V
	MV1SetScale(modelId_, scl_);
	MV1SetPosition(modelId_, pos_);
	MV1SetRotationXYZ(modelId_, rot_);

}

void EnemyBase::Draw(void)
{
#ifdef DEBUG
	DrawSphere3D(GetCollisionPos(), collisionRadius_, 10, 0xff0000, 0xff0000, false);
#endif // _DEBUG

	//���f���`��(���S���́A�\�����Ȃ�)
	if (IsAlive())	MV1DrawModel(modelId_);

	//HP�g
	int screenX = Application::SCREEN_SIZE_X;
	int screenY = Application::SCREEN_SIZE_Y;
	int dx = 300;
	int dy = 30;
	VECTOR pos = { screenX - 50 - dx, 50 };
	int offset = 3;
	DrawBox(pos.x - offset-30, pos.y - offset,
		pos.x + offset + dx, pos.y + offset + dy, 0x0, true);
	DrawString(pos.x - offset-20, pos.y - offset+10, "HP", 0xffffff);

#pragma region HP�V�F�[�_�[�̕`��
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psHpShader_);
	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psHpShaderConstBuf_;

	//�������̂݁AHP�̐��`��Ԃ��s��
	if (hp_ != hpBefore_)
	{
		//HP�̐��`���
		hpLerpTime_ += SceneManager::GetInstance().GetDeltaTime();
		auto t =  hpLerpTime_/ 0.3f;

		//�^�C���z��
		if (t >= 1.0f)
		{
			hpNow_ = hp_;
			hpLerpTime_ = 0.0f;
			hpBefore_ = hp_;
		}
		else
		{
			//HP�̐��`���
			hpNow_ = AsoUtility::Lerp(
				static_cast<float>(hpBefore_), 
				static_cast<float>(hp_), t);
		}
	}
	//HP�̊���
	auto ratio = hpNow_ / static_cast<float>(hpMax_);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = ratio;
	cbBuf->g = totalTime_;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);
	//�`��
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

#pragma endregion
}

void EnemyBase::Release(void)
{
	MV1DeleteModel(modelId_);

	//�V�F�[�_�[�̉��
	DeleteShader(psHpShader_);
	DeleteShaderConstantBuffer(psHpShaderConstBuf_);
}

void EnemyBase::SetEnemyType(ENEMY_TYPE type)
{
	type_ = type;
}

VECTOR EnemyBase::GetPos(void)
{
	return pos_;
}

void EnemyBase::SetPos(VECTOR pos)
{
	pos_ = pos;
}

bool EnemyBase::IsAlive(void)
{
	return isAlive_;
}

void EnemyBase::SetAlive(bool alive)
{
	isAlive_ = alive;
}

void EnemyBase::Damage(int damage)
{
	hpBefore_ = hp_;
	hp_ -= damage;
	if (hp_ <= 0)
	{
		SetAlive(false);
	}
}

VECTOR EnemyBase::GetCollisionPos(void)
{
	//�Փ˗p�̋��̏��
	auto pos= VAdd(collisionLocalPos_, pos_);
	return pos;
}

void EnemyBase::MakeSquereVertex(Vector2 pos)
{
	int screenX = Application::SCREEN_SIZE_X;
	int screenY = Application::SCREEN_SIZE_Y;

	int dx = 300;
	int dy = 30;
	
	VECTOR ePos = { screenX - 50 - dx, 50 };

	int cnt = 0;
	float sX = static_cast<float>(ePos.x);
	float sY = static_cast<float>(ePos.y);
	float eX = static_cast<float>(ePos.x + dx);
	float eY = static_cast<float>(ePos.y + dy);

	// �S���_�̏�����
	for (int i = 0; i < 4; i++)
	{
		mVertex[i].rhw = 1.0f;
		mVertex[i].dif = GetColorU8(255, 255, 255, 255);
		mVertex[i].spc = GetColorU8(255, 255, 255, 255);
		mVertex[i].su = 0.0f;
		mVertex[i].sv = 0.0f;
	}

	// ����
	mVertex[cnt].pos = VGet(sX, sY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// �E��
	mVertex[cnt].pos = VGet(eX, sY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// �E��
	mVertex[cnt].pos = VGet(eX, eY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 1.0f;
	cnt++;

	// ����
	mVertex[cnt].pos = VGet(sX, eY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 1.0f;

	// ���_�C���f�b�N�X
	cnt = 0;
	mIndex[cnt++] = 0;
	mIndex[cnt++] = 1;
	mIndex[cnt++] = 3;

	mIndex[cnt++] = 1;
	mIndex[cnt++] = 2;
	mIndex[cnt++] = 3;

}
