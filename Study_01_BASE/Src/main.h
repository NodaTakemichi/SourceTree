#pragma once

// �X�N���[���T�C�Y
const int SCREEN_X = 1080;
const int SCREEN_Y = 800;
// �C���[�W�T�C�Y
const int IMG_SIZE_X = 128;
const int IMG_SIZE_Y = 128;
const int IMG_SIZE_HX = IMG_SIZE_X / 2;
const int IMG_SIZE_HY = IMG_SIZE_Y / 2;
// �ʒu����
const int PLUS_X = 150;
const int TITLE_Y = -20;
// �V�F�[�_�[�p�X
const std::string PATH_SHADER = "x64/Debug/";
// �f���^�^�C��
std::chrono::system_clock::time_point mPreTime;
float mDeltaTime;
float mTotalTime;
// �`��ʒu
int mPosX;
int mPosY;
// ���_���
VERTEX2DSHADER mVertex[4];
WORD mIndex[6];
// �X�N���[���n���h��
int mainScreen;
// �摜�n���h��
int texDragon;
int texDragonNor;
int texFire;
int texNoize;
int texWhite;

int texCircle;		//���[�h�T�[�N��
int texCircleMask;	//���[�h�T�[�N���V�F�[�_�\

// �V�F�[�_�[�n���h��
int psSimpleColor;

int psCustomColor;
int psCustomColorConstBuf;

int psCircleColor;
int psCircleColorConstBuf;

int psTexture;
int psTextureConstBuf;

int psAlphaBlend;
int psAlphaBlendConstBuf;

int psDithering;
int psDitheringConstBuf;

int psBayerDithe;
int psBayerDitheConstBuf;

int psMonotone;
int psMonotoneConstBuf;

int psSimleSepia;
int psSimleSepiaConstBuf;

int psNoise;
int psNoiseConstBuf;

int psMosaic;
int psMosaicConstBuf;

int psCrayon;
int psCrayonConstBuf;

int psScroll;
int psScrollConstBuf;

int psRotate;
int psRotateConstBuf;

int psSwirl;
int psSwirlConstBuf;

int psScanningLine;
int psScanningLineConstBuf;

int psDistortion;
int psDistortionConstBuf;

int psDirBlur;
int psDirBlurConstBuf;

int psBlur;
int psBlurConstBuf;

int psFlash;
int psFlashConstBuf;

int psNormalMap;
int psNormalMapConstBuf;

int psStatusUp;
int psStatusUpConstBuf;

int psStatusDown;
int psStatusDownConstBuf;

int psPoison;
int psPoisonConstBuf;

void Init(void);
void Release(void);
void Run(void);
// �`��p�̎l�p���_���쐬
void MakeSquereVertex(void);
// ���s
void NewLine(void);
// �^�C�g���`��
void DrawTitle(std::string title);
// �g�`��
void DrawFrame(void);

// �V�F�[�_�[�`��֐�
void DrawSimpleColor(void);
void DrawCustomColor(void);
void DrawCircleColor(void);
void DrawTexture(void);
void DrawAlphaBlend(void);
void DrawDithering(void);
void DrawBayerDithe(void);
void DrawMonotone(void);
void DrawSimleSepia(void);
void DrawNoise(void);
void DrawMosaic(void);
void DrawCrayon(void);
void DrawScroll(void);
void DrawRotate(void);
void DrawSwirl(void);
void DrawScanningLine(void);
void DrawDistortion(void);
void DrawDirBlur(void);
void DrawBlur(void);
void DrawFlash(void);
void DrawNormalMap(void);
void DrawStatusUp(void);
void DrawStatusDown(void);
void DrawPoison(void);

