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


	UnitUI(Vector2 pos, std::string& name,int& hp,int& nowHp, int& maxHp);
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


	//�_���[�W�\�L
	void SetDmg(const bool& drawing, const int& dmg);

private:

protected:
	//���j�b�g���W
	Vector2 unitPos_;
	//���j�b�g�l�[��
	std::string& name_;
	//�ő�HP,������HP
	int& hp_;
	int& maxHp_;
	int& nowHp_;

	//�l�[���t���[���摜
	int nameFrameImg_;
	//�^�[�Q�b�g�摜
	int targetImg_;



	//�_���[�W�t���[���摜
	int dmgFrameImg_;
	//�_���[�W�`��
	bool dmgNumDrawing_;	//�_���[�W�� true:�\�� , false:��\��
	//�_���[�W�l
	int dmg_;

	//�_���[�W�t�H���g
	int dmgFontHandle_;
	//�񕜃t�H���g
	int healFontHandle_;
	//���j�b�g�t�H���g
	int unitFontHandle_;


	//HP�V�F�[�_�[
	//�V�F�[�_�[�n���h��
	int psHpColor_;
	int psHpColorConstBuf_;
	//�ʏ�V�F�[�_�[
	int psTextrue_;

	//HP�̃V�F�[�_�[�`��
	void DrawHpShader(const Vector2& pos ,const COLOR_F& color);

	//HP�g�̕`��
	void DrawHpFrame(const Vector2& pos);

	//���O�̕`��
	void DrawName(const std::string& name,const Vector2& uPos);
	
	//�o�t�A�C�R���̕`��
	void DrawBuffIcon();
	

	//�摜�A�C�R���i�e�X�g�j
	int icon_[10];
	//���L�o�t�̎擾
	std::vector<Buff*> buffs_;


};
