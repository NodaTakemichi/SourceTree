#pragma once
#include <DxLib.h>
#include<string>
#include<vector>
#include"../../Common/Vector2.h"
#include "./Status/Command.h"
#include "./Status/Buff.h"

class UnitUI;

class UnitBase
{
public:
	//�Q�[���V�[���ŕ`�悷�郆�j�b�g�̃T�C�Y
	static constexpr int DRAWING_SIZE = 180;
	//�Q�[���V�[���ŕ`�悷�郆�j�b�g�̃I�t�Z�b�g�l
	static constexpr int DRAWING_OFFSET_X = 50;

	//���j�b�g�̃^�C�v
	enum class UNIT_TYPE
	{
		PLAYER,
		ENEMY,
		END
	};



	UnitBase();
	virtual ~UnitBase();

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);
	
	//�s���I����̏���
	void TurnEndProcess(void);

	//�X�s�[�h�̎擾�֐�
	const int& GetSpeed(void);
	//�U���͂̎擾�֐�
	const int& GetAttack(void);

	//�o�t�ɂ��X�e�[�^�X�̌v�Z
	int CalcBuffStatus(const int& status,const Buff::BUFF_TYPE& up, const Buff::BUFF_TYPE& down);

	//���j�b�g�̏��Ԏ擾�֐�
	const int& GetUnitNum(void) { return unitNum_; }
	//���j�b�g�̃^�C�v�擾�֐�
	const UNIT_TYPE& GetUnitType(void) { return type_; }
	//�R�}���h�擾�֐�
	const std::vector<Command*> GetCommands(void) { return commands_; }
	//�o�t�擾�֐�
	const std::vector<Buff*> GetBuffs(void) { return buffs_; }


	const bool& IsActed(void) { return isActed_; }	//�s���ς݂��ǂ���
	const bool& IsAlive(void) { return isAlive_; }	//�����Ă��邩�ǂ���
	const bool& IsAct(void)   { return isAct_; }	//���݁A�s����Ԃ��ǂ���
	const bool& IsTargeted(void)   { return isTargeted_; }	//���݁A���b�N�I����Ԃ��ǂ���

	void SetActed(bool acted) { isActed_ = acted; }	//�s����Ԃ��Z�b�g����
	void SetAlive(bool alive) { isAlive_ = alive; }	//������Ԃ��Z�b�g����
	void SetAct(bool act)	  { isAct_ = act; }		//���݂̍s����Ԃ��Z�b�g����
	void SetTargeted(bool target) { isTargeted_ = target; }	//���݂̃��b�N�I����Ԃ��Z�b�g����

	void Damage(const int& dmg);				//�_���[�W�֐�
	void Heal(const int& heal);					//�񕜊֐�
	void GiveBuff(const Buff::BUFF_TYPE& type);	//�o�t�t�^�֐�

	bool CheckDead(void);		//���S����

protected:
	//���j�b�gUI
	UnitUI* unitUi_;

	//���j�b�g�̃^�C�v
	UNIT_TYPE type_;

	//���j�b�g�f�[�^������t�@�C���p�X
	std::string unitFile_;

	//���j�b�g�摜
	int unitImg_;
	//���j�b�g�̖��O
	std::string name_;

	//�q�b�g�|�C���g
	int hp_;
	int beforHp_;
	int maxHp_;
	//���j�b�g�F�U����
	int attack_;
	//�s�����x
	int speed_;


	//�R�}���h
	std::vector<Command*>commands_;
	//�o�t
	std::vector <Buff*> buffs_;

	//���j�b�g�̏���
	int unitNum_;
	//�\�����W
	Vector2 pos_;


	//�s���ς݂��ǂ����̔��f
	bool isActed_;
	//�����Ă��邩�ǂ����̔��f
	bool isAlive_;
	//�_���Ă��邩�ǂ���
	bool isTargeted_;

	//���݁A�s����Ԃ��ǂ����̔��f
	bool isAct_;

	//���_���
	VERTEX2DSHADER mVertex[4];
	WORD mIndex[6];
	
	//���݂̃V�F�[�_�[�n���h��
	int nowPs_;
	//�V�F�[�_�[�n���h��
	int psTex_;
	int psTexConstBuf_;

	int psMonotone_;
	int psMonotoneConstBuf_;

	//�`��p�̎l�p���_�̂̍쐬
	void MakeSquereVertex(Vector2 pos);

	//�\��������W�̃Z�b�g
	void SetDrawingPos(int posX);

	//���j�b�g�f�[�^�̎擾�ixml�f�[�^�̓ǂݍ��݁j
	std::string LoadData(std::string fileName);


	//�V�F�[�_�\�ɂ�郆�j�b�g�`��
	void DrawUnitShader(const int& shader ,const float& revers);


private:


	//�R�}���h�̐���
	void CreateCommand(Command::Par* par);

	//�o�t�̐���
	void CreateBuff(const Buff::BUFF_TYPE& type);

};



