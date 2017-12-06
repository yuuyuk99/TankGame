#pragma once
#include <memory>
#include <CommonStates.h>
#include <Effects.h>
#include "../Base/ObjectBase.h"
#include "../Collision/CollisionNode.h"
#include "Wall.h"

//マップの横のサイズ
const int MAP_SIZE_X = 15;
//マップの縦のサイズ
const int MAP_SIZE_Y = 30;

//チップサイズ
const int CHIP_SIZE = 1;

//壁の数
const int WALL_NUM = MAP_SIZE_X * MAP_SIZE_Y;

class Camera;
class Floor;
class Wall;

class Stage
{
public:
	enum STAGE
	{
		GLASS,
		WALL,

		NUM_LAND
	};
	//コンストラクタ
	Stage();
	//デストラクタ
	~Stage();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw(std::shared_ptr<Camera> camera);
	//終了処理
	void Finalize();
	//XY座標を指定すると、その位置の情報を返す
	int GetMapData(int x, int y) { return _LandMap[y][x]; }
	//壁の当たり判定を受け渡す
	SphereNode& GetCollisionNodeWall(int i, int j);
private:
	//地面
	std::shared_ptr<Floor> _floor;
	//壁
	std::shared_ptr<Wall> _wall[MAP_SIZE_Y][MAP_SIZE_X];
	//ステージ
	int _LandMap[MAP_SIZE_Y][MAP_SIZE_X];
};
