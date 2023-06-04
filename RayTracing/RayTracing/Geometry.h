#pragma once


//サイズを表す構造体
struct Size {
	float w;//幅
	float h;//高さ
};

//2D座標・ベクトルを表す構造体
struct Vector2 {
	Vector2():x(0),y(0){}
	Vector2(float inx,float iny):x(inx),y(iny){}
	float x, y;
	///ベクトルの大きさを返します
	float Magnitude()const;
	
	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
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

///内積を返す
float Dot(const Vector2& va, const Vector2& vb);

///外積を返す
float Cross(const Vector2& va, const Vector2& vb);

///内積演算子
float operator*(const Vector2& va, const Vector2& vb);

///外積演算子
float operator%(const Vector2& va, const Vector2& vb);

//とりあえず「座標」って意味だとベクタより
//Positionのほうがよくね？って理由でこの名前
typedef Vector2 Position2;


//3D座標・ベクトルを表す構造体
struct Vector3 {
	Vector3() :x(0), y(0) ,z(0){}
	Vector3(float inx, float iny,float inz) :x(inx), y(iny) ,z(inz){}
	float x, y,z;
	///ベクトルの大きさを返します
	float Magnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
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

///内積を返す
float Dot(const Vector3& va, const Vector3& vb);

///外積を返す
Vector3 Cross(const Vector3& va, const Vector3& vb);

///内積演算子
float operator*(const Vector3& va, const Vector3& vb);

///外積演算子
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

//色の線形補完の作成
using Color = Vector3;


///円を表す構造体
struct Circle {
	float radius;//半径
	Position2 pos; //中心座標
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};


///矩形を表す構造体
struct Rect {
	Position2 pos; //中心座標
	int w, h;//幅,高さ
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
	void Draw();//自分の矩形を描画する
	void Draw(Vector2& offset);//自分の矩形を描画する(オフセット付き)
};

//レイトレ共通のレイを表す
struct Ray
{
	Position3 start;//開始地点
	Vector3 ray;	//レイベクトル（基本は正規化されてる）
	//始点と終点のレイを作る
	void InitRayStartEnd(const Position3& s, const Position3& e)
	{
		start = s;
		ray = (e - s).Normalized();
	}
};

/// <summary>
/// 物体表面に着ける模様の種類
/// </summary>
enum class Pattern
{
	none,	//一色
	hstripe,//縦縞
	vstripe,//横縞
	checker,//炭次郎模様
	texture	//テクスチャ使用
};

/// <summary>
/// マテリアル構造体（物体の表面の色を決める）
/// </summary>
struct Material
{
	Color mainColor;	//メインカラー
	Color subColor;		//サブカラー
	float specular;		//スペキュラ度合い
	float specularity;	//スペキュラ乗数
	float ambient;		//ディフェーズの結果にどれくらいの下駄をはかせるか
	float reflectivity;	//反射率
	float reflectivity2;	//反射率
	Pattern pattern;	//模様の種類
	float patternCycle;	//模様の周期
	int handle;			//テクスチャ模様の時のハンドル
	float rim;			//リム度合い（０：全然でない、１：めっちゃ出る）
	float rimPow;		//リム乗数
};//52byte

/// <summary>
/// 球も平面も一緒くたにする上位概念「オブジェクト」
/// </summary>
struct Object
{
	/// <summary>
	/// レイとオブジェクトが当たったかどうかを返す
	/// </summary>
	/// <param name="ray">光線</param>
	/// <param name="t">当たってたら内部で「交点までの距離」が入る</param>
	/// <returns>true:当たってる,false:当たっていない</returns>
	virtual bool IsHit(const Ray& ray, float& t)const = 0;

	//色
	Material material;

	/// <summary>
	/// 特定の場所における法線ベクトルを返す
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	virtual Vector3 GetNormal(const Position3& p)const = 0;

};


///球を表す構造体
struct Sphere :public Object
{
	float radius;//半径
	Position3 pos; //中心座標
	Sphere() :radius(0), pos(0, 0, 0) {}

	Sphere(float r, const Position3& p) :radius(r), pos(p) {}
	virtual bool IsHit(const Ray& ray, float& t)const override;
	Vector3 GetNormal(const Position3& p)const;
};

//平面の構造体
struct Plane :public Object
{
	Vector3 N;	//平面の法線ベクトル
	float d;	//オフセット値（原点から離れている距離）

	Plane(const Vector3& n, float offset) :N(n), d(offset) {};
	virtual bool IsHit(const Ray& ray, float& t)const override;
	Vector3 GetNormal(const Position3& p)const;

};

