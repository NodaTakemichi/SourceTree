#pragma once
class Vector2
{
public:

	int x;
	int y;

	// �R���X�g���N�^
	Vector2(void);

	// �R���X�g���N�^
	Vector2(int vX, int vY);

	// �f�X�g���N�^
	~Vector2(void);


	void Add(int v);
	void Sub(int v);
	void Scale(int v);

};

