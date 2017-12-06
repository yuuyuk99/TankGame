#pragma once

#include <memory>
#include "MapData.h"
class MapFactory
{
public:
	std::shared_ptr<MapData> Create(MapData::Land land) noexcept;
};
