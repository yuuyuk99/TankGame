#include "MapFactory.h"
#include "Floor.h"
#include "Wall.h"

using namespace std;

shared_ptr<MapData> MapFactory::Create(MapData::Land land) noexcept
{
	shared_ptr<MapData> mapData;
	switch(land)
	{
	case MapData::Land::FLOOR:
		//Floorオブジェクトを生成する
		mapData = make_unique<Floor>();
		break;
	case MapData::Land::WALL:
		//Wallオブジェクトを生成する
		mapData = make_unique<Wall>();
		break;
	default:
		return nullptr;
	}
	//それぞれの地形を初期化する
	mapData->Initialize();
	return move(mapData);
}