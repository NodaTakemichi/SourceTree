#include<dxlib.h>
#include<cmath>
#include<algorithm>
#include<cassert>
#include<vector>
#include<functional>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//���˃x�N�g�����v�Z���ĕԂ�
//���˃x�N�g��
// �@���x�N�g��
//<returns>���˃x�N�g��</returns>
Vector3 ReflectVector(const Vector3& inVec, const Vector3& N)
{
	//���˃x�N�g��
	return inVec - N * 2.0f * (Dot(inVec, N));
}

//�摜
int floorTexH = 0;

/// <summary>
/// ���݂̏��̐F�����W��XYZ�̒l�����ɋ��߂�
/// </summary>
/// <param name="pos">���W</param>
/// <returns>���̐F</returns>
Color GetColorByPos(const Position3& pos, Material mt, float& ref)
{
	Color floorColor = {};
	float addCol = 0.0f;

#pragma region ���̕��͗l
	//�Ȃ�
	if (mt.pattern == Pattern::none)
	{
		floorColor = mt.mainColor;
		ref = mt.reflectivity;
	}
	//�`�F�b�N��
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
	//�摜
	else if (mt.pattern == Pattern::texture)
	{
		ref = mt.reflectivity;
		int w, h;
		int r, g, b ,a;
		//�T�C�Y�𑪂�A�͈͊O���擾���Ȃ��悤�ɂ���
		GetSoftImageSize(mt.handle, &w, &h);
		int u = pos.x < 0 ? w - (int)fabsf(pos.x / 5) % w : (int)fabsf(pos.x / 5) & w;
		int v = pos.z < 0 ? h - (int)fabsf(pos.z / 5) % h : (int)fabsf(pos.z / 5) & h;

		//���W�ʒu�ɂ���摜�̐F���擾
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
/// �P�{�̃��C�ƑS�I�u�W�F�N�g�̌�_��T��
/// </summary>
/// <param name="ray">�����I�u�W�F�N�g</param>
/// <param name="light">���C�g�x�N�g��</param>
/// <param name="objects">�S�I�u�W�F�N�g</param>
/// <param name="self">�����A�h���X�i�ŏ���nullptr�j</param>
/// <param name="retColor">��_�̍��W�ɂ�����F</param>
/// <returns>true:������Afalse:�͂���</returns>
bool Trace(const Ray& ray, const Vector3& light, const Objects_t& objects,
	const Object* self, Color& retColor, int limit = 5)
{
	bool isAnyHit = false;	//�N���ɓ���������true

	//�ł��߂��[�x��,���̊֐��̃y�A
	std::pair<float,std::function<Color(void)>>depthAndFunc=
	std::make_pair(std::numeric_limits<float>::max(),
		[]()->Color {
		return {0, 0, 0};
	});


	for (const auto& object : objects)
	{
		//�������g�̏ꍇ�A���O����
		if (object==self)
		{
			continue;
		}

		float distance = 0.0f;
		//�I�u�W�F�N�g�Ƃ̓����蔻��
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

			//�I�u�W�F�N�g�ƏՓ˂���
			isAnyHit = true;

			depthAndFunc.second = [&ray,distance,&objects,object,limit,&light]()->Color
			{
				Color retColor = {};
				auto hitPos = ray.start + ray.ray * distance;			//��_
				auto N = object->GetNormal(hitPos);//�@���x�N�g��
				//���˃x�N�g�������߂�
				auto refRay = ReflectVector(ray.ray, N);
				//�I�u�W�F�N�g�}�e���A��
				const auto& mt = object->material;

				float  ref = 0.0f;
				auto col = GetColorByPos(hitPos, object->material, ref);
				//���˗� :���~�b�g�̐��l�ŕω�������
				const float reflectivity = limit > 0 ? ref : 0.0f;

				float t = 0.0f;
				bool isHitNextObj = false; //���I�u�W�F�N�g�ɓ���������
				Color nextColor = {};	 //���I�u�W�F�N�g�̐F

				//���˃x�N�g���ƃI�u�W�F�N�g�̓����蔻��
				Ray reflectRay = { hitPos,refRay };
				//���˗����O���傫����΍ċA����
				if (ref > 0.0f)
				{
					isHitNextObj = Trace(reflectRay, light, objects, object, nextColor, limit - 1);
				}

				//���˂��Ȃ��������̐F�i�ʂ���̃��C���n�ʂɓ�����Ȃ��j
				//�����x�N�g���Ɓi�[���s�����j�̓���
				auto diffuse = std::clamp(Dot(N, -light), 0.0f, 1.0f);
				auto refVec = ReflectVector(light, N); //���˃x�N�g��
				//�X�y�L�����[
				auto specular = powf(std::clamp(Dot(-ray.ray, refVec), 0.0f, 1.0f), mt.specularity) * mt.specular;

				//�����i����ȉ��̈Â��ɂȂ�Ȃ��j
				auto ambient = mt.ambient;
				//�����������������̗p����i�^���Â̎��͊������̗p����j
				auto brightness = std::clamp(fmaxf(ambient, diffuse), 0.0f, 1.0f);
				//auto brightness = std::clamp(diffuse + specular, 0.0f, 1.0f);

				float lr = 1.0f, lg = 1.0f, lb = 1.0f;//���C�g�̐F
				float dr = col.x;
				float dg = col.y;
				float db = col.z;	//�f�B�t���[�Y�̐F


				//�������C�g
				//�P�ƂO�𔽓]������
				auto rim = 1.0f - std::clamp(Dot(-ray.ray, N), 0.0f, 1.0f);
				rim = pow(rim, object->material.rimPow);
				rim *= object->material.rim;

				const auto& difCol = object->material.mainColor;

				Color mainColor = {};
				mainColor.x = fminf(dr * brightness + lr * specular + rim, 1.0f);
				mainColor.y = fminf(dg * brightness + lg * specular + rim, 1.0f);
				mainColor.z = fminf(db * brightness + lb * specular + rim, 1.0f);

				Color blendedColor = mainColor;	//sphereColor�F���̂��̂��̂̐F
				//�I�u�W�F�N�g�ɓ������Ă�����A�u�����h�������s��
				if (isHitNextObj)
				{
					//�A���t�@�u�����f�B���O(���`�⊮)
					blendedColor = mainColor * (1.0f - reflectivity) +
						nextColor * reflectivity;
				}

				//�I�u�W�F�N�g�J���[
				retColor = blendedColor;

				//�e�̔���
				Ray shadowRay = { hitPos,-light };
				for (const auto& obj : objects)
				{
					//�������g�����O
					if (obj == object)
					{
						continue;
					}

					float dummy = 0.0f;
					//�����ɂł�������΁A�e�Ƃ���
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

	//�����������ǂ���
	return isAnyHit;
}

/// <summary>
/// ���C�g���[�V���O
/// </summary>
/// <param name="eye">�������W</param>
/// <param name="objects">�I�u�W�F�N�g</param>
void RayTracing(const Position3& eye,const std::vector<Object*>& objects) {
	//���s����
	auto light = Vector3(1, -1, -1); //���C�g�x�N�g��
	light.Normalize();	//������₷�����邽�ߐ��K��
	for (int y = 0; y < screen_height; ++y) {//�X�N���[���c����
		for (int x = 0; x < screen_width; ++x) {//�X�N���[��������
			int r = 0, g = 0, b = 0; //�J���[�~�ϒl
			for (int j = 0; j < 2; ++j) {
				for (int i = 0; i < 2; ++i) {

					Position3 sPos(x - screen_width / 2, screen_height / 2 - y, 0);
					sPos.x += static_cast<float>(i) * 0.5f;
					sPos.y += static_cast<float>(j) * 0.5f;
					//�@���_�ƃX�N���[�����W���王���x�N�g�������
					Ray ray = { eye,sPos - eye };
					//�A���K�����Ƃ�
					ray.ray.Normalize();
					//�BIsHitRay�֐���True�������甒���h��Ԃ�
					//���h��Ԃ���DrawPixel�Ƃ����֐����g���B

					Color col = {};
					//���C�g��
					bool isAnyHit = Trace(ray,light,objects,nullptr,col);	//�N���ɓ���������true

					r += col.x * 255.0f;
					g += col.y * 255.0f;
					b += col.z * 255.0f;

					////���̕`��
					//if (object->IsHit(ray, distance))
					//{
					//	//��_�̍��W
					//	//P=P0+Vt
					//	auto hitPos = eye + ray.ray * distance;
					//	//���̐F�擾
					//	auto floorColor = GetColorByPos(hitPos, object->material);
					//	//�e�̕\��
					//	float t = 0.0f;	//�����͌��Ȃ��B���̂��߂̃_�~�[
					//	Ray sRay = { hitPos, -light };
					//	if (object->IsHit(sRay, t))
					//	{
					//		//��f�l��������
					//		floorColor *= 0.25;
					//	}
					//r += floorColor.x * 255.0f;
					//g += floorColor.y * 255.0f;
					//b += floorColor.z * 255.0f;
					//}


					if (!isAnyHit)	//�N�ɂ�������Ȃ�������w�i�\��
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
			//���ϒl�����߂�
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
	SetMainWindowText(_T("2116224_��c����"));
	DxLib_Init();
	//SetDrawScreen(DX_SCREEN_BACK);

	//�摜�̃��[�h
	floorTexH=LoadSoftImage(L"floorTex.png");
	//���[�h�̎��s�����m����
	assert(floorTexH >= 0);

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Position3 eye{ 0.0f,10.0f,300.0f };
		Position3 center = { 0, -100, -100 };

		//y=0�̕���
		Plane plane = { {0.0f,1.0f,0.0f},-100.0f };
		auto& pmt = plane.material;
		pmt = {};
		//���ʂ̐F
		pmt.mainColor = { 0.5f,1.0f,0.5f };
		pmt.subColor = { 0.5f,0.5f,1.0f };
		pmt.handle = floorTexH;
		pmt.pattern = Pattern::checker;
		pmt.ambient = 1.0f;
		pmt.specular = 0.0f;
		pmt.specularity = 0.0f;
		pmt.patternCycle = 30.0f;//�`�F�b�J�[�̕�
		pmt.rimPow = 4.0f;
		pmt.rim = 0.0f;
		pmt.reflectivity = 0.0f;
		pmt.reflectivity2 = 0.0f;

		//��
		Sphere sphere(100.0f, center);
		auto& smt = sphere.material;
		smt = {};
		//���̐F
		smt.mainColor = { 0.0f,0.5f,0.5f };
		smt.pattern = Pattern::none;
		smt.specular = 1.0f;
		smt.specularity = 20.0f;
		smt.reflectivity = 0.5f;
		smt.rim = 1.0f;
		smt.rimPow = 3.0f;

		//��2
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
		//��3
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