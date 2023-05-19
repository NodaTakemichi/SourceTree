#pragma once
class Stage
{
public:
	// �R���X�g���N�^
	Stage(void);
	// �f�X�g���N�^
	~Stage(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	int GetModel(void) { return modelId_; }

private:
	// �R�c���f���̃n���h��ID
	int modelId_;

	int bgImg_;
};