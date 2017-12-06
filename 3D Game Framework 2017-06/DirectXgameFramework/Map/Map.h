#pragma once
#include <memory>
#include "../Base/ObjectBase.h"
#include "MapData.h"

//�}�b�v�̉��̃T�C�Y
const int MAP_SIZE_X = 20;
//�}�b�v�̏c�̃T�C�Y
const int MAP_SIZE_Y = 15;

//�`�b�v�T�C�Y
const int CIP_SIZE = 1;

//�Q�[����ʂ̉𑜓x
const int WINDOW_X = 20;
const int WINDOW_Y = 15;

class Floor;
class Wall;
class MapData;

class Map
{
public:

	Map();
	~Map();
	void Initialize();
	void Update();
	void Calc();
	void Draw();
	void Finalize();

	int GetMapData(int x, int y) { return _LandMap[y][x]; }
private:
	std::shared_ptr<ObjectBase> _DrawMap;
	std::shared_ptr<MapData> _MapData;
	std::shared_ptr<Floor> _floor;
	std::shared_ptr<Wall> _wall;
	int _LandMap[MAP_SIZE_Y][MAP_SIZE_X];
	//�ʒu
	DirectX::SimpleMath::Vector3 _Pos;
	//���x
	DirectX::SimpleMath::Vector3 _Velocity;
	//��]
	DirectX::SimpleMath::Vector3 _Rot;
	//�p�x
	float angle;
	//�q�I�u�W�F�N�g�ւ̃|�C���^
	std::shared_ptr<Map> _Child;
	//Root�I�u�W�F�N�g�ւ̃|�C���^
	std::shared_ptr<Map> _Root;
};
