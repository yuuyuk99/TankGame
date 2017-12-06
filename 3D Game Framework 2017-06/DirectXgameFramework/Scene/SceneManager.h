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
	//指定シーンに変更する
	virtual void ChangeScene(_SCENE NextScene);

	SceneManager(_SCENE scene);
	~SceneManager();
	//シーン遷移
	void Initiaize();
	//シーンの更新
	void Update();
	//シーンの描画
	void Draw();
	//シーンの終了処理
	void Finalize();
	//シーンを変更
	void Reset();
	//現在のシーンを受け取る
	void SetManager(std::shared_ptr<SceneManager> scene);
private:
	std::unique_ptr<Scene> _scene;
	_SCENE _nextScene;
	std::shared_ptr<SceneManager> _sceneManager;
};
