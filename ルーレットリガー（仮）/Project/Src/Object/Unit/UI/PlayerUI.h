#pragma once
#include "UnitUI.h"
class PlayerUI :
    public UnitUI
{
public:
	PlayerUI(Vector2 pos, std::string* name);
	~PlayerUI();

	void Init(void);
	void Draw(void);
	void Release(void);

	//�s�����̃��j�b�g�̕\��
	void DrawActUnit(void);

	//���b�N�I��
	void DrawRockOn(void);

private:
	//���j�b�g���W
	Vector2 unitPos_;
	//���j�b�g�l�[��
	std::string* name_;

};

