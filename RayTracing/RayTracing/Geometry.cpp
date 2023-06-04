#include"Geometry.h"
#include<DxLib.h>
#include<cmath>


void
Rect::Draw() {
	DxLib::DrawBox(Left()*2, Top()*2, Right()*2, Bottom()*2, 0xffffffff, false);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBox((Left()+offset.x)*2, (Top()+offset.y)*2, (Right()+offset.x)*2, (Bottom()+offset.y)*2, 0xffffffff, false);
}

void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

Vector2
Vector2::operator*(float scale) {
	return Vector2(x*scale, y*scale);
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x + vb.x, va.y + vb.y);
}

Vector2 operator-(const Vector2& va, const Vector2 vb){
	return Vector2(va.x - vb.x, va.y - vb.y);
}

Vector2 operator*(const Vector2& va, const float vb)
{
	return Vector2(va.x * vb, va.y * vb);
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
}


void 
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}


Vector2
Vector2::Normalized() {
	float mag = Magnitude();
	return Vector2(x / mag,	y /mag);
}


///���ς�Ԃ�
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x*vb.x + va.y*vb.y;
}

///�O�ς�Ԃ�
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x*vb.y - vb.x*va.y;
}

///���ω��Z�q
float 
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///�O�ω��Z�q
float 
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}


void 
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void 
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}


//-------��������3D�̃^�[��------
void
Vector3::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

Vector3
Vector3::operator*(float scale)const {
	return Vector3(x*scale, y*scale,z*scale);
}

Vector3 operator+(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x + vb.x, va.y + vb.y,va.z+vb.z);
}

Vector3 operator-(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x - vb.x, va.y - vb.y,va.z-vb.z);
}

float
Vector3::Magnitude()const {
	return sqrt(x*x+y*y+z*z);
}


void
Vector3::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}


Vector3
Vector3::Normalized() {
	float mag = Magnitude();
	return Vector3(x / mag, y / mag,z/mag);
}


///���ς�Ԃ�
float
Dot(const Vector3& va, const Vector3& vb) {
	return va.x*vb.x + va.y*vb.y+va.z*vb.z;
}

///�O�ς�Ԃ�
Vector3
Cross(const Vector3& va, const Vector3& vb) {
	return Vector3(va.z*vb.y-va.y*vb.z,va.z*vb.x-va.x*vb.z,va.x*vb.y - vb.x*va.y);
}

///���ω��Z�q
float
operator*(const Vector3& va, const Vector3& vb) {
	return Dot(va, vb);
}

///�O�ω��Z�q
Vector3
operator%(const Vector3& va, const Vector3& vb) {
	return Cross(va, vb);
}


void
Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
void
Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

bool Sphere::IsHit(const Ray& ray, float& t) const
{
	auto C = pos - ray.start;

	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	//�ˉe
	auto dot = Dot(C, ray.ray); //�x�N�g�������ˉe

	//���C���}�C�i�X�̎��A�I������
	if (dot < 0.0f)
	{
		return false;
	}

	auto R = ray.ray * dot;

	auto vlen = (C - R).Magnitude();	//�����̒���
	auto isHit = vlen < radius;		//�������Ă邩�ǂ���
	//��_�܂ł̋������ˉe���[�㔼�a�̂Q��[�����̒����̂Q��

	if (isHit)
	{
		//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂܂�
		t = dot - sqrtf(radius * radius - vlen * vlen);
		return true;
	}
	else
	{
		return false;
	}
}

Vector3 Sphere::GetNormal(const Position3& p) const
{
	return (p - pos).Normalized();
}

bool Plane::IsHit(const Ray& ray, float& t) const
{
	auto vDot = Dot(ray.ray, N);	//����̓���

	//���ς��O�����������ꍇ�A�Ȃɂ��`�悹���A���ɐi��
	//�[�����Z��������邽�߂ɁA�O�������Ƃ��Ԃ�
	if (vDot >= 0.0f)return false;

	//��_�܂ł̋������v�Z
	auto pDot = Dot(ray.start, N);	//���q�̓���
	t = (d - pDot) / vDot;

	return true;
}

Vector3 Plane::GetNormal(const Position3& p) const
{
	return N;
}
