#include "Stage.h"
#include "../Camera/Camera.h"
#include "../Graphics.h"
#include "Floor.h"
#include "Wall.h"

#include <SimpleMath.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Stage::Stage()
{
	//地面の生成
	_floor = make_shared<Floor>();
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for(int j = 0; j < MAP_SIZE_X; j++)
		{
			//壁の生成
			_wall[i][j] = make_shared<Wall>();
		}
	}
	
}

Stage::~Stage()
{

}

/*
 *@初期化処理
 */
void Stage::Initialize()
{
	
	//地面の初期化を行う
	_floor->Initialize();
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			_wall[i][j]->Initialize();
		}
	}
}

/*
 *@更新処理
 */
void Stage::Update()
{
	//行列更新
	_floor->Update();

	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			if (i < 1 || i > MAP_SIZE_Y - 2 || j < 1 || j >MAP_SIZE_X - 2)
			{
				_wall[i][j]->SetTrans(Vector3((float)j * CHIP_SIZE, 0.0f, (float)i * CHIP_SIZE));
				_wall[i][j]->Update();
			}
		}
	}
}

/*
 *@描画処理
 */
void Stage::Draw(shared_ptr<Camera> camera)
{
	Matrix world = Matrix::Identity;
	//床を描画をする
	_floor->Draw(camera);
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			_wall[i][j]->Draw(camera);
		}
	}
}

/*
 *@終了処理
 */
void Stage::Finalize()
{

}

/*
 *@壁の当たり判定を受け渡す
 */
SphereNode& Stage::GetCollisionNodeWall(int i, int j)
{
	return _wall[i][j]->GetCollisionNode();
}