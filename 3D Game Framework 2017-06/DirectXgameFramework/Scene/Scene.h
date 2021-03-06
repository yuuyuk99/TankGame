#pragma once
#include <memory>
#include <WICTextureLoader.h>

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	//シーンの描画
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
};