#pragma once
#include "SceneBase.h"
class SelectScene :
    public SceneBase
{
public:

	enum class select
	{
		NONE,
		GAME,
		DECK_EDIT,
		EXIT
	};

	// �R���X�g���N�^
	SelectScene(void);

	// �f�X�g���N�^
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:


	//�w�i�摜

	//���[���b�g�摜

	//���[���b�g�p�x
};

