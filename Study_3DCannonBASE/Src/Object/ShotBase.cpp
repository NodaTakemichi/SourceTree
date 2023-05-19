#include "../Manager/SceneManager.h"
#include "ShotBase.h"

ShotBase::ShotBase(int baseModelId, int* blastImgs, int blastAnimNum)
{
    baseModelId_ = baseModelId;
    blastImgs_ = blastImgs;
    blastAnimNum_ = blastAnimNum;
}

ShotBase::~ShotBase(void)
{
}

void ShotBase::CreateShot(VECTOR pos, VECTOR dir)
{
    // �g�p�������e�ʂƓǂݍ��ݎ��Ԃ̍팸�̂���
    // ���f���f�[�^����������������ɑ��݂����Ȃ�
    modelId_ = MV1DuplicateModel(baseModelId_);
    // �e�̑傫����ݒ�
    scl_ = { 0.8f, 0.8f, 0.8f };
    // �e�̊p�x��ݒ�
    rot_ = { 0.0f, 0.0f, 0.0f };
    // �e�̔��ˈʒu��ݒ�
    pos_ = pos;
    // �e�̔��˕����̐ݒ�
    dir_ = dir;
    // �e�̑��x
    speed_ = 8.0f;
    // �e�̐�������
    isAlive_ = true;

    //�d��
    gravityPow_ = 0.0f;

    // �����̃A�j���[�V�����p�J�E���^
    blastCntAnim_ = 0;
    // �����̃A�j���[�V�������x
    blastSpeedAnim_ = 0.3f;
    // ��ԑJ��
    ChangeState(STATE::SHOT);

}

void ShotBase::Update(void)
{
    //����ł���ꍇ�A���������Ȃ�
    if (!IsAlive())return;

    switch (state_)
    {
    case ShotBase::STATE::SHOT:
        UpdateShot();
        break;
    case ShotBase::STATE::BLAST:
        UpdateBlast();
        break;
    case ShotBase::STATE::END:
        UpdateEnd();
        break;
    }

}

void ShotBase::UpdateShot(void)
{
    //�ړ���
    VECTOR movePow = VScale(dir_, speed_);

    //�ړ�����
    pos_ = VAdd(pos_, movePow);

    //�����x�I�ɏd�͂�������
    gravityPow_ += SceneManager::GRAVITY / SceneManager::DEFAULT_FPS;
    pos_ = VAdd(pos_, VScale({ 0.0f,-1.0f,0.0f }, gravityPow_));

    // �傫���̐ݒ�
    MV1SetScale(modelId_, scl_);
    // �p�x�̐ݒ�
    MV1SetRotationXYZ(modelId_, rot_);
    // �ʒu�̐ݒ�
    MV1SetPosition(modelId_, pos_);
}

void ShotBase::UpdateBlast(void)
{
    //�����A�j���[�V��������
    //blastCntAnim_ += blastSpeedAnim_;
    blastIdxAnim_++;

    //�����A�j���[�V�����I������
    if (blastIdxAnim_ + 1 >= blastAnimNum_)
    {
        ChangeState(STATE::END);
    }

}

void ShotBase::UpdateEnd(void)
{
    //�������Ȃ�
}

void ShotBase::Draw()
{
    //����ł���ꍇ�A���������Ȃ�
    if (!IsAlive())return;

    switch (state_)
    {
    case ShotBase::STATE::SHOT:
        DrawShot();
        break;
    case ShotBase::STATE::BLAST:
        DrawBlast();
        break;
    case ShotBase::STATE::END:
        DrawEnd();
        break;
    }
}

void ShotBase::DrawShot(void)
{
    MV1DrawModel(modelId_);
}

void ShotBase::DrawBlast(void)
{
    DrawBillboard3D(
        pos_, 0.5f, 0.5f, 80.0f,0.0f, blastImgs_[blastIdxAnim_], true);
}

void ShotBase::DrawEnd(void)
{
    //�������Ȃ�
}

void ShotBase::Release(void)
{
    MV1DeleteModel(modelId_);

}

bool ShotBase::IsAlive(void)
{
    return state_ != STATE::END;
}

bool ShotBase::IsShot(void)
{
    return state_ == STATE::SHOT;
}

void ShotBase::Blast(void)
{
    ChangeState(STATE::BLAST);
}

void ShotBase::ChangeState(STATE state)
{
    state_ = state;

    switch (state_)
    {
    case ShotBase::STATE::NONE:
        break;
    case ShotBase::STATE::SHOT:
        break;
    case ShotBase::STATE::BLAST:
        break;
    case ShotBase::STATE::END:
        blastIdxAnim_ = 0;
        break;
    default:
        break;
    }
}
