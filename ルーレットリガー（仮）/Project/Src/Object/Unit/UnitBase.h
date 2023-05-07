#pragma once
#include <DxLib.h>
#include<string>
#include<vector>
#include"../../Common/Vector2.h"
#include "./Command.h"

class UnitUI;
class Par;

class UnitBase
{
public:

	//���j�b�g�̃^�C�v
	enum class UNIT_TYPE
	{
		PLAYER,
		ENEMY,
		END
	};

	//�o�t�̃^�C�v
	enum class CMD_TYPE
	{
		NONE = 0,
		PALALYSIS,
		POISON,
		CONFUSION,
		AVOIDANCE,

		P_UP,
		P_DOWN,
		S_UP,
		S_DOWN,
		D_UP,
		D_DOWN,

		CMD_DOWN,
		CMD_BAN,
		END
	};


	
	//�Q�[���V�[���ŕ`�悷�郆�j�b�g�̃T�C�Y
	static constexpr int DRAWING_SIZE = 180;
	//�Q�[���V�[���ŕ`�悷�郆�j�b�g�̃I�t�Z�b�g�l
	static constexpr int DRAWING_OFFSET_X = 50;


	UnitBase();
	virtual ~UnitBase();

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);
	

	//�X�s�[�h�̎擾�֐�
	const int& GetSpeed(void) { return speed_; }
	//�U���͂̎擾�֐�
	const int& GetAttack(void) { return attack_; }
	//�R�}���h�擾�֐�
	const std::vector<Command*> GetCommands(void) { return commands_; }
	//���j�b�g�̏��Ԏ擾�֐�
	const int& GetUnitNum(void) { return unitNum_; }
	//���j�b�g�̃^�C�v�擾�֐�
	const UNIT_TYPE& GetUnitType(void) { return type_; }

	const bool& IsActed(void) { return isActed_; }	//�s���ς݂��ǂ���
	const bool& IsAlive(void) { return isAlive_; }	//�����Ă��邩�ǂ���
	const bool& IsAct(void)   { return isAct_; }	//���݁A�s����Ԃ��ǂ���
	const bool& IsTargeted(void)   { return isTargeted_; }	//���݁A���b�N�I����Ԃ��ǂ���

	void SetActed(bool acted) { isActed_ = acted; }	//�s����Ԃ��Z�b�g����
	void SetAlive(bool alive) { isAlive_ = alive; }	//������Ԃ��Z�b�g����
	void SetAct(bool act)	  { isAct_ = act; }		//���݂̍s����Ԃ��Z�b�g����
	void SetTargeted(bool target) { isTargeted_ = target; }	//���݂̃��b�N�I����Ԃ��Z�b�g����

	void Damage(int dmg);		//�_���[�W�֐�
	void Heal(int heal);		//�񕜊֐�

	bool CheckDead(void);		//���S����

protected:
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

	//���j�b�g�̏���
	int unitNum_;
	//�\�����W
	Vector2 pos_;

	//���j�b�gUI
	UnitUI* unitUi_;

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

};



