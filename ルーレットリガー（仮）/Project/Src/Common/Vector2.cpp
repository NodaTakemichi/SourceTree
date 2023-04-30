#include "Vector2.h"

// �R���X�g���N�^
Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}

// �R���X�g���N�^
Vector2::Vector2(int vX, int vY)
{
	x = vX;
	y = vY;
}


Vector2::~Vector2(void)
{
}

void Vector2::Add(int v)
{
	x += v;
	y += v;
}

void Vector2::Sub(int v)
{
	x -= v;
	y -= v;
}

void Vector2::Scale(int v)
{
	x *= v;
	y *= v;
}
