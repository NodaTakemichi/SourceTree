#pragma once
#include<vector>
#include<string>
class Command;

class Roulette
{
public:
	//��]���x
	const float ROT_SPEED_MAX = -16.0f;

	//���[���b�g��~�܂ł̑ҋ@����
	const float STOP_WAIT_TIME_ROU = 0.8f;

	Roulette();
	~Roulette();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//���[���b�g���~�߂�w���o���֐�
	void StopRoulette(const bool& autom);		//true�F�����Afalse�F�蓮

	//���[���b�g�ɃR�}���h�Z���Z�b�g����
	void SetCommand(std::vector<Command*> cmd);

	//���[���b�g�̉�]�󋵂����Z�b�g����
	void ResetRouSpin(void);

	//���[���b�g�̒�~��Ԃ̎擾�֐�
	bool GetRouStop(void) { return isStop_; }

	//���肵���R�}���h�̎擾
	Command* GetCmd(void);

private:

	//���[���b�g�摜
	int rouletteImg_;
	//���摜
	int arrowImg_;

	//��]�p�x
	double angle;
	//��]��
	double rotPower_;

	//���[���b�g�̉�]��
	bool isRouSpin_;
	//���[���b�g����~��Ԃ����f
	bool isStop_;

	//�t�H���g�n���h��
	int fontHandle_;

	//�R�}���h�Z
	std::vector<Command*>cmdNames_;

	//�ҋ@����
	float totalTime_;

	//���[���b�g�̉�]����
	void RotateProcess(void);


};

