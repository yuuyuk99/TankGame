#pragma once
#include "SceneBase.h"
#include <memory>

class Scene;

enum _SCENE {
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RESULT,

	SCENE_NONE,
};

class SceneManager
{
public:
	//�w��V�[���ɕύX����
	virtual void ChangeScene(_SCENE NextScene);

	SceneManager(_SCENE scene);
	~SceneManager();
	//�V�[���J��
	void Initiaize();
	//�V�[���̍X�V
	void Update();
	//�V�[���̕`��
	void Draw();
	//�V�[���̏I������
	void Finalize();
	//�V�[����ύX
	void Reset();
	//���݂̃V�[�����󂯎��
	void SetManager(std::shared_ptr<SceneManager> scene);
private:
	std::unique_ptr<Scene> _scene;
	_SCENE _nextScene;
	std::shared_ptr<SceneManager> _sceneManager;
};
