#pragma once
#include "UnitUI.h"
class EnemyUI :
    public UnitUI
{
public:
	EnemyUI(Vector2 pos, std::string* name);
	~EnemyUI();

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

