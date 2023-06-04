#include<dxlib.h>
#include<cmath>
#include<algorithm>
#include<cassert>
#include<vector>
#include<functional>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//反射ベクトルを計算して返す
//入射ベクトル
// 法線ベクトル
//<returns>反射ベクトル</returns>
Vector3 ReflectVector(const Vector3& inVec, const Vector3& N)
{
	//反射ベクトル
	return inVec - N * 2.0f * (Dot(inVec, N));
}

//画像
int floorTexH = 0;

/// <summary>
/// 現在の床の色を座標のXYZの値を元に求める
/// </summary>
/// <param name="pos">座標</param>
/// <returns>床の色</returns>
Color GetColorByPos(const Position3& pos, Material mt, float& ref)
{
	Color floorColor = {};
	float addCol = 0.0f;

#pragma region 床の柄模様
	//なし
	if (mt.pattern == Pattern::none)
	{
		floorColor = mt.mainColor;
		ref = mt.reflectivity;
	}
	//チェック柄
	else if (mt.pattern == Pattern::checker)
	{
		auto sign = ((int)(pos.x / mt.patternCycle) + (int)(pos.z / mt.patternCycle)) % 2 == 0 ? 1 : -1;
		sign *= pos.x < 0.0f ? -1 : 1;
		sign *= pos.z < 0.0f ? -1 : 1;
		if (sign < 0)
		{
			floorColor = mt.mainColor;
			ref = mt.reflectivity;
		}
		else
		{
			floorColor = mt.subColor;
			ref = mt.reflectivity2;
		}
	}
	//画像
	else if (mt.pattern == Pattern::texture)
	{
		ref = mt.reflectivity;
		int w, h;
		int r, g, b ,a;
		//サイズを測り、範囲外を取得しないようにする
		GetSoftImageSize(mt.handle, &w, &h);
		int u = pos.x < 0 ? w - (int)fabsf(pos.x / 5) % w : (int)fabsf(pos.x / 5) & w;
		int v = pos.z < 0 ? h - (int)fabsf(pos.z / 5) % h : (int)fabsf(pos.z / 5) & h;

		//座標位置にある画像の色を取得
		GetPixelSoftImage(mt.handle,
			(int)fabsf(pos.x/5) % w, 
			(int)fabsf(pos.z/5) % h, 
			//u,v,
			&r, &g, &b, &a);

		floorColor.x=(float)r / 255.0f;
		floorColor.y=(float)g / 255.0f;
		floorColor.z=(float)b / 255.0f;
		if (a == 0)
		{
			floorColor = { 1,1,1 };
		}

	}
#pragma endregion

	return floorColor;
}

using Objects_t = std::vector<Object*>;
/// <summary>
/// １本のレイと全オブジェクトの交点を探索
/// </summary>
/// <param name="ray">光線オブジェクト</param>
/// <param name="light">ライトベクトル</param>
/// <param name="objects">全オブジェクト</param>
/// <param name="self">自分アドレス（最初はnullptr）</param>
/// <param name="retColor">交点の座標における色</param>
/// <returns>true:当たり、false:はずれ</returns>
bool Trace(const Ray& ray, const Vector3& light, const Objects_t& objects,
	const Object* self, Color& retColor, int limit = 5)
{
	bool isAnyHit = false;	//誰かに当たったらtrue

	//最も近い深度と,その関数のペア
	std::pair<float,std::function<Color(void)>>depthAndFunc=
	std::make_pair(std::numeric_limits<float>::max(),
		[]()->Color {
		return {0, 0, 0};
	});


	for (const auto& object : objects)
	{
		//自分自身の場合、除外する
		if (object==self)
		{
			continue;
		}

		float distance = 0.0f;
		//オブジェクトとの当たり判定
		if (object->IsHit(ray, distance))
		{
			if (depthAndFunc.first > distance)
			{
				depthAndFunc.first = distance;
			}
			else
			{
				continue;
			}

			//オブジェクトと衝突した
			isAnyHit = true;

			depthAndFunc.second = [&ray,distance,&objects,object,limit,&light]()->Color
			{
				Color retColor = {};
				auto hitPos = ray.start + ray.ray * distance;			//交点
				auto N = object->GetNormal(hitPos);//法線ベクトル
				//反射ベクトルを求める
				auto refRay = ReflectVector(ray.ray, N);
				//オブジェクトマテリアル
				const auto& mt = object->material;

				float  ref = 0.0f;
				auto col = GetColorByPos(hitPos, object->material, ref);
				//反射率 :リミットの数値で変化させる
				const float reflectivity = limit > 0 ? ref : 0.0f;

				float t = 0.0f;
				bool isHitNextObj = false; //他オブジェクトに当たったか
				Color nextColor = {};	 //他オブジェクトの色

				//反射ベクトルとオブジェクトの当たり判定
				Ray reflectRay = { hitPos,refRay };
				//反射率が０より大きければ再帰する
				if (ref > 0.0f)
				{
					isHitNextObj = Trace(reflectRay, light, objects, object, nextColor, limit - 1);
				}

				//反射しない球部分の色（玉からのレイが地面に当たらない）
				//光線ベクトルと（ー平行光線）の内積
				auto diffuse = std::clamp(Dot(N, -light), 0.0f, 1.0f);
				auto refVec = ReflectVector(light, N); //反射ベクトル
				//スペキュラー
				auto specular = powf(std::clamp(Dot(-ray.ray, refVec), 0.0f, 1.0f), mt.specularity) * mt.specular;

				//環境光（それ以下の暗さにならない）
				auto ambient = mt.ambient;
				//数字が多いき方を採用する（真っ暗の時は環境光を採用する）
				auto brightness = std::clamp(fmaxf(ambient, diffuse), 0.0f, 1.0f);
				//auto brightness = std::clamp(diffuse + specular, 0.0f, 1.0f);

				float lr = 1.0f, lg = 1.0f, lb = 1.0f;//ライトの色
				float dr = col.x;
				float dg = col.y;
				float db = col.z;	//ディフューズの色


				//リムライト
				//１と０を反転させる
				auto rim = 1.0f - std::clamp(Dot(-ray.ray, N), 0.0f, 1.0f);
				rim = pow(rim, object->material.rimPow);
				rim *= object->material.rim;

				const auto& difCol = object->material.mainColor;

				Color mainColor = {};
				mainColor.x = fminf(dr * brightness + lr * specular + rim, 1.0f);
				mainColor.y = fminf(dg * brightness + lg * specular + rim, 1.0f);
				mainColor.z = fminf(db * brightness + lb * specular + rim, 1.0f);

				Color blendedColor = mainColor;	//sphereColor：球体そのものの色
				//オブジェクトに当たっていたら、ブレンド調整を行う
				if (isHitNextObj)
				{
					//アルファブレンディング(線形補完)
					blendedColor = mainColor * (1.0f - reflectivity) +
						nextColor * reflectivity;
				}

				//オブジェクトカラー
				retColor = blendedColor;

				//影の判定
				Ray shadowRay = { hitPos,-light };
				for (const auto& obj : objects)
				{
					//自分自身を除外
					if (obj == object)
					{
						continue;
					}

					float dummy = 0.0f;
					//何かにでも当たれば、影とする
					if (obj->IsHit(shadowRay, dummy))
					{
						retColor *= 0.5f;
					}
				}
				return retColor;
			};

			//break;
		}
	}

	if (isAnyHit)
	{
		retColor = depthAndFunc.second();
	}

	//当たったかどうか
	return isAnyHit;
}

/// <summary>
/// レイトレーシング
/// </summary>
/// <param name="eye">視線座標</param>
/// <param name="objects">オブジェクト</param>
void RayTracing(const Position3& eye,const std::vector<Object*>& objects) {
	//平行光線
	auto light = Vector3(1, -1, -1); //ライトベクトル
	light.Normalize();	//分かりやすくするため正規化
	for (int y = 0; y < screen_height; ++y) {//スクリーン縦方向
		for (int x = 0; x < screen_width; ++x) {//スクリーン横方向
			int r = 0, g = 0, b = 0; //カラー蓄積値
			for (int j = 0; j < 2; ++j) {
				for (int i = 0; i < 2; ++i) {

					Position3 sPos(x - screen_width / 2, screen_height / 2 - y, 0);
					sPos.x += static_cast<float>(i) * 0.5f;
					sPos.y += static_cast<float>(j) * 0.5f;
					//①視点とスクリーン座標から視線ベクトルを作る
					Ray ray = { eye,sPos - eye };
					//②正規化しとく
					ray.ray.Normalize();
					//③IsHitRay関数がTrueだったら白く塗りつぶす
					//※塗りつぶしはDrawPixelという関数を使う。

					Color col = {};
					//レイトレ
					bool isAnyHit = Trace(ray,light,objects,nullptr,col);	//誰かに当たったらtrue

					r += col.x * 255.0f;
					g += col.y * 255.0f;
					b += col.z * 255.0f;

					////床の描画
					//if (object->IsHit(ray, distance))
					//{
					//	//交点の座標
					//	//P=P0+Vt
					//	auto hitPos = eye + ray.ray * distance;
					//	//床の色取得
					//	auto floorColor = GetColorByPos(hitPos, object->material);
					//	//影の表現
					//	float t = 0.0f;	//距離は見ない。そのためのダミー
					//	Ray sRay = { hitPos, -light };
					//	if (object->IsHit(sRay, t))
					//	{
					//		//画素値を下げる
					//		floorColor *= 0.25;
					//	}
					//r += floorColor.x * 255.0f;
					//g += floorColor.y * 255.0f;
					//b += floorColor.z * 255.0f;
					//}


					if (!isAnyHit)	//誰にも当たらなかったら背景表示
					{
						if (((x / 30) + (y / 30)) % 2 == 0)
						{
							r = 0;
							g = 0;
							b = 0;
						}
						else
						{
							r += 0;
							g += 0xff;
							b += 0;
						}
					}
				}
			}
			//平均値を求める
			r /= 4;
			g /= 4;
			b /= 4;
			DrawPixel(x,y,GetColor( r, g, b ));

		}
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetGraphMode(screen_width, screen_height, 32);
	SetMainWindowText(_T("2116224_野田武道"));
	DxLib_Init();
	//SetDrawScreen(DX_SCREEN_BACK);

	//画像のロード
	floorTexH=LoadSoftImage(L"floorTex.png");
	//ロードの失敗を検知する
	assert(floorTexH >= 0);

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Position3 eye{ 0.0f,10.0f,300.0f };
		Position3 center = { 0, -100, -100 };

		//y=0の平面
		Plane plane = { {0.0f,1.0f,0.0f},-100.0f };
		auto& pmt = plane.material;
		pmt = {};
		//平面の色
		pmt.mainColor = { 0.5f,1.0f,0.5f };
		pmt.subColor = { 0.5f,0.5f,1.0f };
		pmt.handle = floorTexH;
		pmt.pattern = Pattern::checker;
		pmt.ambient = 1.0f;
		pmt.specular = 0.0f;
		pmt.specularity = 0.0f;
		pmt.patternCycle = 30.0f;//チェッカーの幅
		pmt.rimPow = 4.0f;
		pmt.rim = 0.0f;
		pmt.reflectivity = 0.0f;
		pmt.reflectivity2 = 0.0f;

		//球
		Sphere sphere(100.0f, center);
		auto& smt = sphere.material;
		smt = {};
		//球の色
		smt.mainColor = { 0.0f,0.5f,0.5f };
		smt.pattern = Pattern::none;
		smt.specular = 1.0f;
		smt.specularity = 20.0f;
		smt.reflectivity = 0.5f;
		smt.rim = 1.0f;
		smt.rimPow = 3.0f;

		//球2
		Sphere sphere2(100.0f, { -200.0f, 0.0f, -50.0f });
		auto& smt2 = sphere2.material;
		smt2 = {};
		smt2.mainColor = { 0.0f,0.0f,0.5f };
		smt2.pattern = Pattern::none;
		smt2.specular = 1.0f;
		smt2.specularity = 20.0f;
		smt2.reflectivity = 0.5f;
		smt2.rim = 1.0f;
		smt2.rimPow = 3.0f;
		//球3
		Sphere sphere3(100.0f, { 200.0f, -50.0f, -150.0f });
		auto& smt3 = sphere3.material;
		smt3 = {};
		smt3.mainColor = { 0.5f,0.0f,0.0f };
		smt3.pattern = Pattern::none;
		smt3.specular = 1.0f;
		smt3.specularity = 20.0f;
		smt3.reflectivity = 0.5f;
		smt3.rim = 1.0f;
		smt3.rimPow = 3.0f;


		std::vector<Object*>objects;
		objects.push_back(&plane);
		objects.push_back(&sphere);
		objects.push_back(&sphere2);
		objects.push_back(&sphere3);
		//objects[0] = sphere
		//objects[1] = plane

		RayTracing(eye, objects);

	}
	WaitKey();
	DxLib_End();
}