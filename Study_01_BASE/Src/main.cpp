#include <chrono>
#include <math.h>
#include <string>
#include <DxLib.h>
#include "main.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_X, SCREEN_Y, 32, 60);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		// �G���[�����������璼���ɏI��
		return -1;
	}

	// ������
	Init();
	// ���s
	Run();
	// ���
	Release();
	// �c�w���C�u�����̌�n��
	DxLib_End();
	// �\�t�g�̏I��
	return 0;
}

void Init(void)
{

	// �`��Ɏg�p����摜�̓ǂݍ���
	texDragon = LoadGraph("Data/Dragon.png");

	// �`��Ɏg�p����摜�̓ǂݍ���
	texDragonNor = LoadGraph("Data/Dragon_n.png");

	// �`��Ɏg�p����摜�̓ǂݍ���
	texFire = LoadGraph("Data/Fire.png");

	// �`��Ɏg�p����摜�̓ǂݍ���
	texNoize = LoadGraph("Data/Noise128.png");

	// �`��Ɏg�p����摜�̓ǂݍ���
	texWhite = LoadGraph("Data/White.png");

	// �`��Ɏg�p����摜�̓ǂݍ���
	texCircle = LoadGraph("Data/mainTex.png");
	// �`��Ɏg�p����摜�̓ǂݍ���
	texCircleMask = LoadGraph("Data/loadMask.png");



	//�s�N�Z���V�F�[�_�[�̃��[�h
	psSimpleColor = LoadPixelShader(
		(PATH_SHADER + "SimpleColor.cso").c_str());

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psCustomColor = LoadPixelShader(
		(PATH_SHADER + "CustomColor.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psCustomColorConstBuf = CreateShaderConstantBuffer(sizeof(float) * 4);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psCircleColor = LoadPixelShader(
		(PATH_SHADER + "CircleColor.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psCircleColorConstBuf = CreateShaderConstantBuffer(sizeof(float) * 4);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psTexture = LoadPixelShader(
		(PATH_SHADER + "Texture.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psTextureConstBuf = CreateShaderConstantBuffer(sizeof(float) * 4);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psAlphaBlend = LoadPixelShader(
		(PATH_SHADER + "AlphaBlend.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psAlphaBlendConstBuf = CreateShaderConstantBuffer(sizeof(float) * 4);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psDithering = LoadPixelShader(
		(PATH_SHADER + "Dithering.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psDitheringConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psBayerDithe = LoadPixelShader(
		(PATH_SHADER + "BayerDithe.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psBayerDitheConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psMonotone = LoadPixelShader(
		(PATH_SHADER + "Monotone.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psMonotoneConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psSimleSepia = LoadPixelShader(
		(PATH_SHADER + "SimleSepia.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psSimleSepiaConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psNoise = LoadPixelShader(
		(PATH_SHADER + "Noise.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psNoiseConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psMosaic = LoadPixelShader(
		(PATH_SHADER + "Mosaic.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psMosaicConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psCrayon = LoadPixelShader(
		(PATH_SHADER + "Crayon.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psCrayonConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psScroll = LoadPixelShader(
		(PATH_SHADER + "Scroll.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psScrollConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psRotate = LoadPixelShader(
		(PATH_SHADER + "Rotate.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psRotateConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psSwirl = LoadPixelShader(
		(PATH_SHADER + "Swirl.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psSwirlConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psScanningLine = LoadPixelShader(
		(PATH_SHADER + "ScanningLine.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psScanningLineConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psDistortion = LoadPixelShader(
		(PATH_SHADER + "Distortion.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psDistortionConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psDirBlur = LoadPixelShader(
		(PATH_SHADER + "DirBlur.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psDirBlurConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psBlur = LoadPixelShader(
		(PATH_SHADER + "Blur.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psBlurConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psFlash = LoadPixelShader(
		(PATH_SHADER + "Flash.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psFlashConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psNormalMap = LoadPixelShader(
		(PATH_SHADER + "NormalMap.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psNormalMapConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psStatusUp = LoadPixelShader(
		(PATH_SHADER + "StatusUp.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psStatusUpConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psStatusDown = LoadPixelShader(
		(PATH_SHADER + "StatusDown.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psStatusDownConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psPoison = LoadPixelShader(
		(PATH_SHADER + "Poison.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psPoisonConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//�s�N�Z���V�F�[�_�[�̃��[�h
	psParalysis = LoadPixelShader(
		(PATH_SHADER + "Paralysis.cso").c_str());
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psParalysisConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

}

void Release(void)
{

	// �s�N�Z���V�F�[�_�[�����
	DeleteShader(psSimpleColor);
	DeleteShader(psCustomColor);
	DeleteShader(psCircleColor);
	DeleteShader(psTexture);
	DeleteShader(psAlphaBlend);
	DeleteShader(psDithering);
	DeleteShader(psBayerDithe);
	DeleteShader(psMonotone);
	DeleteShader(psSimleSepia);
	DeleteShader(psNoise);
	DeleteShader(psMosaic);
	DeleteShader(psCrayon);
	DeleteShader(psScroll);
	DeleteShader(psRotate);
	DeleteShader(psSwirl);
	DeleteShader(psScanningLine);
	DeleteShader(psDistortion);
	DeleteShader(psDirBlur);
	DeleteShader(psBlur);
	DeleteShader(psFlash);
	DeleteShader(psNormalMap);
	DeleteShader(psStatusUp);
	DeleteShader(psStatusDown);
	DeleteShader(psPoison);
	DeleteShader(psParalysis);

	// �s�N�Z���V�F�[�_�[�p�萔�o�b�t�@�����
	DeleteShaderConstantBuffer(psCustomColorConstBuf);
	DeleteShaderConstantBuffer(psCircleColorConstBuf);
	DeleteShaderConstantBuffer(psTextureConstBuf);
	DeleteShaderConstantBuffer(psAlphaBlendConstBuf);
	DeleteShaderConstantBuffer(psDitheringConstBuf);
	DeleteShaderConstantBuffer(psBayerDitheConstBuf);
	DeleteShaderConstantBuffer(psMonotoneConstBuf);
	DeleteShaderConstantBuffer(psSimleSepiaConstBuf);
	DeleteShaderConstantBuffer(psNoiseConstBuf);
	DeleteShaderConstantBuffer(psMosaicConstBuf);
	DeleteShaderConstantBuffer(psCrayonConstBuf);
	DeleteShaderConstantBuffer(psScrollConstBuf);
	DeleteShaderConstantBuffer(psRotateConstBuf);
	DeleteShaderConstantBuffer(psSwirlConstBuf);
	DeleteShaderConstantBuffer(psScanningLineConstBuf);
	DeleteShaderConstantBuffer(psDistortionConstBuf);
	DeleteShaderConstantBuffer(psDirBlurConstBuf);
	DeleteShaderConstantBuffer(psBlurConstBuf);
	DeleteShaderConstantBuffer(psFlashConstBuf);
	DeleteShaderConstantBuffer(psStatusUpConstBuf);
	DeleteShaderConstantBuffer(psStatusDownConstBuf);
	DeleteShaderConstantBuffer(psPoisonConstBuf);
	DeleteShaderConstantBuffer(psParalysisConstBuf);


}

void Run(void)
{

	// ���C���X�N���[���쐬
	mainScreen = MakeScreen(SCREEN_X, SCREEN_Y, true);

	// �f���^�^�C��
	mPreTime = std::chrono::system_clock::now();
	mTotalTime = 0.0f;

	// ESC�L�[���������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// �f���^�^�C��
		auto nowTime = std::chrono::system_clock::now();
		mDeltaTime = static_cast<float>(
			std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - mPreTime).count() / 1000000000.0);
		mPreTime = nowTime;

		// �Q�[���N������
		mTotalTime += mDeltaTime;

		// ���C���֐ؑ�
		SetDrawScreen(mainScreen);

		// ��ʂ�������
		ClearDrawScreen();

		// �w�i�F�̕`��
		//DrawBox(0, 0, SCREEN_X, SCREEN_Y, 0x0, true);
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, 0x00aaaa, true);

		// ���W�̏�����
		mPosX = 10;
		mPosY = 80;
		
		// �ʏ�̕`��
		DrawTitle("DrawGraph");
		DrawGraph(mPosX, mPosY, texDragon, true);
		mPosX += PLUS_X;

		//�P�F
		DrawSimpleColor();
		mPosX += PLUS_X;

		//�w��F
		DrawCustomColor();
		mPosX += PLUS_X;

		//�~
		DrawCircleColor();
		mPosX += PLUS_X;

		//�e�N�X�`��
		DrawTexture();
		mPosX += PLUS_X;

		//������
		DrawAlphaBlend();
		mPosX += PLUS_X;

		//�f�B�U�����O
		DrawDithering();
		mPosX += PLUS_X;

		// ���W�̏�����
		mPosX = 10;
		mPosY += 180;

		//�׃C���[�f�B�U
		DrawBayerDithe();
		mPosX += PLUS_X;

		//�O���[�X�P�[��
		DrawMonotone();
		mPosX += PLUS_X;

		//�V���v���Z�s�A
		DrawSimleSepia();
		mPosX += PLUS_X;

		//�m�C�Y
		DrawNoise();
		mPosX += PLUS_X;

		//���U�C�N
		DrawMosaic();
		mPosX += PLUS_X;

		//�N������
		//DrawCrayon();
		//mPosX += PLUS_X;

		//�X�N���[��
		DrawScroll();
		mPosX += PLUS_X;

		//��]
		DrawRotate();
		mPosX += PLUS_X;

		// ���W�̏�����
		mPosX = 10;
		mPosY += 180;

		//�Q��
		DrawSwirl();
		mPosX += PLUS_X;

		//������
		DrawScanningLine();
		mPosX += PLUS_X;

		//�c��
		//DrawDistortion();
		//mPosX += PLUS_X;

		//�����u���[
		DrawDirBlur();
		mPosX += PLUS_X;

		//�u���[
		DrawBlur();
		mPosX += PLUS_X;

		//����
		DrawFlash();
		mPosX += PLUS_X;

		//�@���}�b�v
		DrawNormalMap();
		mPosX += PLUS_X;

		//�X�e�[�^�X�A�b�v
		DrawStatusUp();
		mPosX += PLUS_X;

		// ���W�̏�����
		mPosX = 10;
		mPosY += 180;

		//�X�e�[�^�X�_�E��
		DrawStatusDown();
		mPosX += PLUS_X;

		//��
		DrawPoison();
		mPosX += PLUS_X;

		//���
		DrawParalysis();
		mPosX += PLUS_X;


		// ����ʂɕ`��
		SetDrawScreen(DX_SCREEN_BACK);
		// ��ʂ�������
		ClearDrawScreen();
		// �`��
		DrawGraph(0, 0, mainScreen, true);

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

	}

	// ���C���X�N���[���폜
	DeleteGraph(mainScreen);

}

void MakeSquereVertex(void)
{
	//�O�p�`�̃|���S����2����āA�������Ă���

	// ���񒸓_�f�[�^���쐬����͖̂��ʂł����A
	// �V�F�[�_�[�ǉ����̍�Ƃ����炷���߁A���t���[���쐬

	int cnt = 0;
	float sX = static_cast<float>(mPosX);
	float sY = static_cast<float>(mPosY);
	float eX = static_cast<float>(mPosX + IMG_SIZE_X - 1);
	float eY = static_cast<float>(mPosY + IMG_SIZE_Y - 1);

	// �S���_�̏�����
	for (int i = 0; i < 4; i++)
	{
		mVertex[i].rhw = 1.0f;
		mVertex[i].dif = GetColorU8(255, 255, 255, 255);
		mVertex[i].spc = GetColorU8(255, 255, 255, 255);
		mVertex[i].su = 0.0f;
		mVertex[i].sv = 0.0f;
	}

	// ����
	mVertex[cnt].pos = VGet(sX, sY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// �E��
	mVertex[cnt].pos = VGet(eX, sY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// �E��
	mVertex[cnt].pos = VGet(eX, eY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 1.0f;
	cnt++;

	// ����
	mVertex[cnt].pos = VGet(sX, eY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 1.0f;

	/*
	�@�`�`�`�`�`�`
		0-----1
		|     |
		|     |
		3-----2
	�@�`�`�`�`�`�`
		0-----1
		|  �^
		|�^
		3
	�@�`�`�`�`�`�`
			  1
		   �^ |
		 �^   |
		3-----2
	�@�`�`�`�`�`�`
	*/


	// ���_�C���f�b�N�X
	cnt = 0;
	mIndex[cnt++] = 0;
	mIndex[cnt++] = 1;
	mIndex[cnt++] = 3;

	mIndex[cnt++] = 1;
	mIndex[cnt++] = 2;
	mIndex[cnt++] = 3;

}

/// <summary>
/// ���s
/// </summary>
/// <param name=""></param>
void NewLine(void)
{
	mPosX = 10;
	mPosY += 180;
}

void DrawTitle(std::string title)
{
	DrawString(mPosX, mPosY + TITLE_Y, title.c_str(), 0x000000);
}

void DrawFrame(void)
{
	DrawBox(mPosX - 1, mPosY - 1, mPosX + IMG_SIZE_X, mPosY + IMG_SIZE_Y, 0x000000, false);
}

void DrawSimpleColor(void)
{
	DrawTitle("�P�F");

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psSimpleColor);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

	//�t���[��
	DrawFrame();
}

void DrawCustomColor(void)
{
	DrawTitle("�w��F");

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psCustomColor);
	
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf = 
		(COLOR_F*)GetBufferShaderConstantBuffer(psCustomColorConstBuf);
	cbBuf->r = 0.0f;
	cbBuf->g = 0.5f;
	cbBuf->b = 0.0f;
	cbBuf->a = 1.0f;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(psCustomColorConstBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(psCustomColorConstBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

	//�t���[��
	DrawFrame();
}

void DrawCircleColor(void)
{
	DrawTitle("�~");

	auto& cBuf = psCircleColorConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psCircleColor);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 0.4f;
	cbBuf->g = 0.4f;
	cbBuf->b = 0.8f;
	cbBuf->a = 1.0f;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

	//�t���[��
	DrawFrame();
}

void DrawTexture(void)
{
	DrawTitle("�e�N�X�`��");

	auto& cBuf = psTextureConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psTexture);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawAlphaBlend(void)
{
	DrawTitle("�A���t�@�u�����h");

	auto& cBuf = psAlphaBlendConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psAlphaBlend);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	//cbBuf->a = 0.5f;
	cbBuf->a = 1.0f;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();
}

void DrawDithering(void)
{
	DrawTitle("�f�B�U�����O");

	auto& cBuf = psDitheringConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psDithering);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 128;		

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();
}

void DrawBayerDithe(void)
{
	DrawTitle("�x�C���[�f�B�U");

	auto& cBuf = psBayerDitheConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psBayerDithe);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 10;		//�x�C���[���x��
	cbBuf->g = 128;		//�摜�T�C�YX
	cbBuf->b = 128;		//�摜�T�C�YY

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawMonotone(void)
{
	DrawTitle("�O���[�X�P�[��");

	auto& cBuf = psMonotoneConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psMonotone);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawSimleSepia(void)
{
	DrawTitle("�V���v���Z�s�A");

	auto& cBuf = psSimleSepiaConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psSimleSepia);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();
}

void DrawNoise(void)
{
	DrawTitle("�m�C�Y");

	auto& cBuf = psNoiseConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psNoise);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->g = mDeltaTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawMosaic(void)
{
	DrawTitle("���U�C�N");

	auto& cBuf = psMosaicConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psMosaic);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 8.0f;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawCrayon(void)
{
	DrawTitle("�N������");

	auto& cBuf = psCrayonConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psCrayon);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();
}

void DrawScroll(void)
{
	DrawTitle("�X�N���[��");

	auto& cBuf = psScrollConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psScroll);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 0.3f;
	cbBuf->g = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�A�O���b�V�u���[�h��ݒ肷��
	//SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP);
	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawRotate(void)
{
	DrawTitle("��]");

	auto& cBuf = psRotateConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psRotate);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texCircle);
	SetUseTextureToShader(1, texCircleMask);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 1.0f;
	cbBuf->g = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawSwirl(void)
{
	DrawTitle("�Q��");

	auto& cBuf = psSwirlConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psSwirl);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 0.5f;
	cbBuf->g = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawScanningLine(void)
{
	DrawTitle("������");

	auto& cBuf = psScanningLineConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psScanningLine);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 0.3f;
	cbBuf->g = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();
}

void DrawDistortion(void)
{
	DrawTitle("�c��");

	auto& cBuf = psDistortionConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psDistortion);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);
	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(1, texNoize);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 4);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�A�O���b�V�u���[�h��ݒ肷��
	SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP);
	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�A�O���b�V�u���[�h�����Ƃɖ߂�
	SetTextureAddressModeUV(DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP);

	//�t���[��
	DrawFrame();
}

void DrawDirBlur(void)
{
	DrawTitle("�u���[");

	auto& cBuf = psDirBlurConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psDirBlur);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawBlur(void)
{
	DrawTitle("�u���[");

	auto& cBuf = psBlurConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psBlur);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 1.0f;
	cbBuf->r = 128.0f;
	cbBuf->r = 128.0f;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();
}

void DrawFlash(void)
{
	DrawTitle("����");

	auto& cBuf = psFlashConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psFlash);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 1.0f;
	cbBuf->r = 128.0f;
	cbBuf->r = 128.0f;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawNormalMap(void)
{
	DrawTitle("�@���}�b�v");

	auto& cBuf = psNormalMapConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psNormalMap);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);
	SetUseTextureToShader(1, texDragonNor);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 1.0f;
	cbBuf->r = 1.0f;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawStatusUp(void)
{
	DrawTitle("�X�e�[�^�X�A�b�v");

	auto& cBuf = psStatusUpConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psStatusUp);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawStatusDown(void)
{
	DrawTitle("�X�e�[�^�X�_�E��");

	auto& cBuf = psStatusDownConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psStatusDown);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}

void DrawPoison(void)
{
	DrawTitle("��");

	auto& cBuf = psPoisonConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psPoison);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();


}

void DrawParalysis(void)
{
	DrawTitle("���");

	auto& cBuf = psParalysisConstBuf;

	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psParalysis);

	////�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, texDragon);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = mTotalTime;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�l�p�|���S���i�O�p2�j�𐶐�
	MakeSquereVertex();

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���[��
	DrawFrame();

}
