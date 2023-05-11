#pragma once
#include<string>
#include<vector>
#include"../../../Common/Vector2.h"
#include "../../../Utility/AsoUtility.h"
#include "../Status/Buff.h"
#include"../UnitBase.h"

class UnitUI
{
public:
	const int  HP_GAUGE_X = 20;
	const int  HP_GAUGE_Y = 120;


	UnitUI(Vector2 pos, std::string& name,
		int& hp, int& maxHp, int& beforHp);
	virtual ~UnitUI();


	virtual void Init(void);
	virtual void Draw(void);
	void Release(void);


	//�s�����̃��j�b�g�̕\��
	virtual void DrawActUnit(void) = 0;
	//���b�N�I��
	virtual void DrawRockOn(void) = 0;
	//�o�t���Z�b�g����
	void SetBuff(std::vector<Buff*> buffs);


private:

protected:
	//���j�b�g���W
	Vector2 unitPos_;
	//���j�b�g�l�[��
	std::string& name_;
	//HP
	int& hp_;
	int& maxHp_;
	int& beforHp_;
	
	//�l�[���t���[���摜
	int nameFrameImg_;

	//HP�V�F�[�_�[
	//���_���
	VERTEX2DSHADER mVertex[4];
	WORD mIndex[6];

	//�V�F�[�_�[�n���h��
	int psHpColor_;
	int psHpColorConstBuf_;

	//���v����
	float totalTime_;
	//HP�ω���
	int nowHp_;

	//�`��p�̎l�p���_�̂̍쐬
	void MakeSquereVertex(Vector2 pos);

	//HP�̃V�F�[�_�[�`��
	void DrawHpShader(const float& ratio, const COLOR_F& color);

	//HP�̌�������
	void DecHpGauge(void);

	//HP�g�̕`��
	void DrawHpFrame(const Vector2& pos);

	//���O�̕`��
	void DrawName(const std::string& name,const Vector2& uPos);
	
	//�o�t�A�C�R���̕`��
	void DrawBuffIcon();
	

	//�摜�A�C�R���i�e�X�g�j
	int icon_[9];
	//���L�o�t�̎擾
	std::vector<Buff*> buffs_;


};

