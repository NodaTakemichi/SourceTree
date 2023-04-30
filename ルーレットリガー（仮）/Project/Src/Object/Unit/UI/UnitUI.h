#pragma once
#include<string>
#include"../UnitBase.h"
#include"../../../Common/Vector2.h"

class UnitUI
{
public:
	const int  HP_GAUGE_X = 20;
	const int  HP_GAUGE_Y = 120;


	UnitUI();
	virtual ~UnitUI();


	virtual void Init(void);
	virtual void Draw(void) = 0;
	void Release(void);

	//�s�����̃��j�b�g�̕\��
	virtual void DrawActUnit(void) = 0;
	//���b�N�I��
	virtual void DrawRockOn(void) = 0;


private:

protected:
	////���j�b�g���W
	//Vector2 unitPos_;
	////���j�b�g�l�[��
	//std::string* name_;


	//�l�[���t���[���摜
	int nameFrameImg_;
	//HP�t���[���摜
	int hpFrameImg_;

	//HP�V�F�[�_�[
	//���_���
	VERTEX2DSHADER mVertex[4];
	WORD mIndex[6];

	//�V�F�[�_�[�n���h��
	int psHpColor_;
	int psHpColorConstBuf_;

	//�`��p�̎l�p���_�̂̍쐬
	void MakeSquereVertex(Vector2 pos);

};

