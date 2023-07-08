#pragma once
#include <string>
#include "ButtonUI.h"
class CmdButton :
    public ButtonUI
{
public:

    CmdButton();
    ~CmdButton();

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;

    //�{�^������
    void Create(const Vector2& pos, const Vector2& size, const int& cmdNum);

    //�{�^���̏�Ƀ}�E�X������Ă��邩�ǂ���
    bool MouseOnButton(void);

    //�R�}���h���̍ăZ�b�g
    void SetCmd(const int& cmdNum);


private:
    //�{�^���T�C�Y
    Vector2 size_;

    //�R�}���h��
    std::string cmdName_;
    //�t�H���g
    int fontHandle_;

    //�l�p�`��Ƀ}�E�X�����邩�̊m�F
    bool IsMouseInRect(
        const Vector2& inside, const Vector2& outside, const Vector2& size);

    //�R�}���h�{�^���V�F�[�_�[
    int psCmdBtn_;

};

