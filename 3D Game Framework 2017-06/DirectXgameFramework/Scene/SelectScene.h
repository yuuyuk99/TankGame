#pragma once
#include "SceneBase.h"

class SelectScene : public SceneBase
{
public:
	SelectScene(std::shared_ptr<SceneManager> scene);
	~SelectScene();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};

