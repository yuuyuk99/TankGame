#pragma once
#include "Scene.h"

class SceneManager;

//シーンの基底クラス
class SceneBase : public Scene
{
public:
	SceneBase(std::shared_ptr<SceneManager> changer);
	virtual ~SceneBase();
	virtual void Initialize() override {}
	virtual void Update() override {}
	virtual void Draw() override {}
	virtual void Finalize() override {}
protected:
	std::weak_ptr<SceneManager> m_SceneChanger;
};

