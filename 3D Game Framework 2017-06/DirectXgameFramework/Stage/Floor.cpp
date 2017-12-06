#include "Floor.h"
#include "../Graphics.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

Floor::Floor()
{
	_floor = make_shared<ObjectBase>();
}

Floor::~Floor()
{

}

/*
 *@初期化
 */
void Floor::Initialize()
{
	//地面のモデルを読み込む
	this->_floor->LoadModelFile(L"Resources/cModels/floor.cmo");

	this->_floor->SetScale(Vector3(2.5f, 1.0f, 6.0f));
	this->_floor->SetTrans(Vector3(6.0f, 0.0f, 10.0f));

	//当たり判定の初期化
	_collisionNode.Initialize();
	//当たり判定のワールド座標を設定
	_collisionNode.SetParentMatrix(&this->_floor->GetLocalWorld());
	//当たり判定の大きさを設定
	_collisionNode.SetLocalradius(1.0f);
	//当たり判定が親からどれだけ離れているか
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
}

/*
 *@更新処理
 */
void Floor::Update() 
{
	//ワールド行列
	Matrix world = Matrix::Identity;
	//行列更新
	_floor->Calc(world);
	//当たり判定の更新
	_collisionNode.Update();
}

/*
 *@描画処理
 */
void Floor::Draw(std::shared_ptr<Camera> camera)
{
	//Floorの描画を行う
	_floor->Draw(camera);
}

void Floor::Finalize()
{

}
