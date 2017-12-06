#pragma once
#include <memory>
#include "MapData.h"
#include "../Base/ObjectBase.h"

class Wall : public MapData
{
public:
	Wall();
	~Wall();
	void Initialize() override;
	void Update() override;
	void Calc() override;
	void Draw() override;
	void Finalize() override;
private:
	std::shared_ptr<ObjectBase> _Wall;
};