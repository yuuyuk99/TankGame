#pragma once

#include <memory>
#include <d3d11.h>
#include <SimpleMath.h>

class TowerData
{
public:
	enum Parts
	{
		CENTER,
		BALLET,
	};
	TowerData();
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void Finalize();
private:
};
