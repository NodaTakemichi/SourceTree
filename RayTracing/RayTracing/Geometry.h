#pragma once


//�T�C�Y��\���\����
struct Size {
	float w;//��
	float h;//����
};

//2D���W�E�x�N�g����\���\����
struct Vector2 {
	Vector2():x(0),y(0){}
	Vector2(float inx,float iny):x(inx),y(iny){}
	float x, y;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;
	
	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector2 Normalized();

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scale);
	Vector2 operator*(float scale);
	Vector2 operator-() {
		return Vector2(-x, -y);
	}
};

Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator-(const Vector2& va, const Vector2 vb);
Vector2 operator*(const Vector2& va, const float vb);

///���ς�Ԃ�
float Dot(const Vector2& va, const Vector2& vb);

///�O�ς�Ԃ�
float Cross(const Vector2& va, const Vector2& vb);

///���ω��Z�q
float operator*(const Vector2& va, const Vector2& vb);

///�O�ω��Z�q
float operator%(const Vector2& va, const Vector2& vb);

//�Ƃ肠�����u���W�v���ĈӖ����ƃx�N�^���
//Position�̂ق����悭�ˁH���ė��R�ł��̖��O
typedef Vector2 Position2;


//3D���W�E�x�N�g����\���\����
struct Vector3 {
	Vector3() :x(0), y(0) ,z(0){}
	Vector3(float inx, float iny,float inz) :x(inx), y(iny) ,z(inz){}
	float x, y,z;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector3 Normalized();

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale)const;
	Vector3 operator-()const {
		return Vector3(-x, -y,-z);
	}
};
Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);

///���ς�Ԃ�
float Dot(const Vector3& va, const Vector3& vb);

///�O�ς�Ԃ�
Vector3 Cross(const Vector3& va, const Vector3& vb);

///���ω��Z�q
float operator*(const Vector3& va, const Vector3& vb);

///�O�ω��Z�q
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

//�F�̐��`�⊮�̍쐬
using Color = Vector3;


///�~��\���\����
struct Circle {
	float radius;//���a
	Position2 pos; //���S���W
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};


///��`��\���\����
struct Rect {
	Position2 pos; //���S���W
	int w, h;//��,����
	Rect() : pos(0, 0), w(0), h(0) {}
	Rect(float x, float y, int inw, int inh) :
		pos(x, y), w(inw), h(inh) {}
	Rect(Position2& inpos, int inw, int inh) :
		pos(inpos), w(inw), h(inh)
	{}
	void SetCenter(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	void SetCenter(const Position2& inpos) {
		pos.x = inpos.x;
		pos.y = inpos.y;
	}
	Vector2 Center() {
		return pos;
	}
	float Left() { return pos.x - w / 2; }
	float Top() { return pos.y - h / 2; }
	float Right() { return pos.x + w / 2; }
	float Bottom() { return pos.y + h / 2; }
	void Draw();//�����̋�`��`�悷��
	void Draw(Vector2& offset);//�����̋�`��`�悷��(�I�t�Z�b�g�t��)
};

//���C�g�����ʂ̃��C��\��
struct Ray
{
	Position3 start;//�J�n�n�_
	Vector3 ray;	//���C�x�N�g���i��{�͐��K������Ă�j
	//�n�_�ƏI�_�̃��C�����
	void InitRayStartEnd(const Position3& s, const Position3& e)
	{
		start = s;
		ray = (e - s).Normalized();
	}
};

/// <summary>
/// ���̕\�ʂɒ�����͗l�̎��
/// </summary>
enum class Pattern
{
	none,	//��F
	hstripe,//�c��
	vstripe,//����
	checker,//�Y���Y�͗l
	texture	//�e�N�X�`���g�p
};

/// <summary>
/// �}�e���A���\���́i���̂̕\�ʂ̐F�����߂�j
/// </summary>
struct Material
{
	Color mainColor;	//���C���J���[
	Color subColor;		//�T�u�J���[
	float specular;		//�X�y�L�����x����
	float specularity;	//�X�y�L�����搔
	float ambient;		//�f�B�t�F�[�Y�̌��ʂɂǂꂭ�炢�̉��ʂ��͂����邩
	float reflectivity;	//���˗�
	float reflectivity2;	//���˗�
	Pattern pattern;	//�͗l�̎��
	float patternCycle;	//�͗l�̎���
	int handle;			//�e�N�X�`���͗l�̎��̃n���h��
	float rim;			//�����x�����i�O�F�S�R�łȂ��A�P�F�߂�����o��j
	float rimPow;		//�����搔
};//52byte

/// <summary>
/// �������ʂ��ꏏ�����ɂ����ʊT�O�u�I�u�W�F�N�g�v
/// </summary>
struct Object
{
	/// <summary>
	/// ���C�ƃI�u�W�F�N�g�������������ǂ�����Ԃ�
	/// </summary>
	/// <param name="ray">����</param>
	/// <param name="t">�������Ă�������Łu��_�܂ł̋����v������</param>
	/// <returns>true:�������Ă�,false:�������Ă��Ȃ�</returns>
	virtual bool IsHit(const Ray& ray, float& t)const = 0;

	//�F
	Material material;

	/// <summary>
	/// ����̏ꏊ�ɂ�����@���x�N�g����Ԃ�
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	virtual Vector3 GetNormal(const Position3& p)const = 0;

};


///����\���\����
struct Sphere :public Object
{
	float radius;//���a
	Position3 pos; //���S���W
	Sphere() :radius(0), pos(0, 0, 0) {}

	Sphere(float r, const Position3& p) :radius(r), pos(p) {}
	virtual bool IsHit(const Ray& ray, float& t)const override;
	Vector3 GetNormal(const Position3& p)const;
};

//���ʂ̍\����
struct Plane :public Object
{
	Vector3 N;	//���ʂ̖@���x�N�g��
	float d;	//�I�t�Z�b�g�l�i���_���痣��Ă��鋗���j

	Plane(const Vector3& n, float offset) :N(n), d(offset) {};
	virtual bool IsHit(const Ray& ray, float& t)const override;
	Vector3 GetNormal(const Position3& p)const;

};

