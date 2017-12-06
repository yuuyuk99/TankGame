#include "Wall.h"
#include <SimpleMath.h>
#include "../Graphics.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

Wall::Wall()
{
	//壁を生成する
	_wall = make_shared<ObjectBase>();
}

Wall::~Wall()
{

}

/*
 *@初期化処理
 */
void Wall::Initialize()
{
	//壁のモデルを読み込む
	this->_wall->LoadModelFile(L"Resources/cModels/box.cmo");

	//当たり判定の初期化
	_collisionNode.Initialize();
	//当たり判定のワールド座標を設定
	_collisionNode.SetParentMatrix(&this->_wall->GetLocalWorld());
	//当たり判定の大きさを設定
	_collisionNode.SetLocalradius(0.1f);
	//当たり判定が親からどれだけ離れているか
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
}

/*
 *@更新処理
 */
void Wall::Update()
{
	//ワールド座標
	Matrix world = Matrix::Identity;
	//行列更新
	_wall->Calc(world);
	//当たり判定の更新
	_collisionNode.Update();
}

/*
 *@描画処理
 */
void Wall::Draw(std::shared_ptr<Camera> camera)
{
	//壁の描画を行う
	_wall->Draw(camera);
}

/*
 *@終了処理
 */
void Wall::Finalize()
{

}
