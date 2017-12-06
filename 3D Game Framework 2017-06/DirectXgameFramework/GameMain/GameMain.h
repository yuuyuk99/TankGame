#pragma once

#ifndef  GAMEMAIN
#define GAMEMAIN

#include "../Framework/Game.h"
#include "../Scene/SceneManager.h"

class GameMain : public Game {
public:
	//�R���X�g���N�^
	GameMain(int width, int height);
	//�Q�[���I�u�W�F�N�g������������
	void Initialize() override;
	//�Q�[�����X�V����
	void Update(DX::StepTimer const& timer) override;
	//�Q�[���V�[����`��
	void Draw(DX::StepTimer const& timer) override;
	//�I���������s��
	void Finalize() override;
protected:
	shared_ptr<SceneManager> sceneManager;
};

#endif // GAMEMAIN
