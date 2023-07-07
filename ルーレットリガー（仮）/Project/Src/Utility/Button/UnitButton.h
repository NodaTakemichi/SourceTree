#pragma once
#pragma <string>
#include "ButtonUI.h"
class UnitData;

class UnitButton :
    public ButtonUI
{
public:

    UnitButton();
    ~UnitButton();

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;

    //�{�^������
    void Create(Vector2 pos, int back, UnitData unit);

    //�{�^���̏�Ƀ}�E�X������Ă��邩�ǂ���
    bool MouseOnButton(void);


private:
    //�{�^���T�C�Y
    Vector2 size_;

    //�����摜

    //���j�b�g�摜�A���j�b�g��
    int unitImg_;
    std::string name_;

    //�t�H���g�n���h��
    int fontHandle_;


    //�V�F�[�_�[
    int psCardFrame_;
    //�g�̐F
    COLOR_F fColor_;


    //�l�p�`��Ƀ}�E�X�����邩�̊m�F
    bool IsMouseInRect(
        const Vector2& inside, const Vector2& outside, const Vector2& size);


};

