#pragma once
#include <memory>
#include "../Base/ObjectBase.h"
#include "MapData.h"

//マップの横のサイズ
const int MAP_SIZE_X = 20;
//マップの縦のサイズ
const int MAP_SIZE_Y = 15;

//チップサイズ
const int CIP_SIZE = 1;

//ゲーム画面の解像度
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
	//位置
	DirectX::SimpleMath::Vector3 _Pos;
	//速度
	DirectX::SimpleMath::Vector3 _Velocity;
	//回転
	DirectX::SimpleMath::Vector3 _Rot;
	//角度
	float angle;
	//子オブジェクトへのポインタ
	std::shared_ptr<Map> _Child;
	//Rootオブジェクトへのポインタ
	std::shared_ptr<Map> _Root;
};
