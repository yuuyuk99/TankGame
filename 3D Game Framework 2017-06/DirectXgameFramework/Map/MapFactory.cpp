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
		//Floor�I�u�W�F�N�g�𐶐�����
		mapData = make_unique<Floor>();
		break;
	case MapData::Land::WALL:
		//Wall�I�u�W�F�N�g�𐶐�����
		mapData = make_unique<Wall>();
		break;
	default:
		return nullptr;
	}
	//���ꂼ��̒n�`������������
	mapData->Initialize();
	return move(mapData);
}