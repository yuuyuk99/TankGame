#include "Tower.h"
#include "../Graphics.h"
#include <Effects.h>
#include <CommonStates.h>
#include "../Camera/Camera.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

/*
 *@コンストラクタ
 */
Tower::Tower()
{
	//タワーの生成
	this->_Tower = std::make_shared<ObjectBase>();

	this->_health = 10;
}

/*
 *@Towerオブジェクトの初期化処理
 */
void Tower::Initialize()
{
	//Graphicsクラスのインスタンスを取得する
	auto& graphics = Graphics::Get();
	//CommonStatesを生成する
	this->_commonState = make_unique<CommonStates>(graphics.Device().Get());
	//エフェクトファクトリの作成
	_factory = make_unique<EffectFactory>(graphics.Device().Get());
	//テクスチャの読み込みパスを指定 テクスチャがあるファイルを指定
	_factory->SetDirectory(L"Resources/cModels");
	//タワーのモデルを読み込む
	this->_Tower->LoadModelFile(L"Resources/cModels/cTower.cmo");

	//当たり判定の設定
	_collisionNode.Initialize();
	//当たり判定のワールド座標を設定
	_collisionNode.SetParentMatrix(&this->_Tower->GetLocalWorld());
	//当たり判定の大きさを設定
	_collisionNode.SetLocalRadius(1.0f);
	//当たり判定が親からどれだけ離れているか
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
}

/*
 *@Towerオブジェクトの更新処理
 */
void Tower::Update()
{
	//ワールド座標
	Matrix world = Matrix::Identity;
	//行列更新
	this->_Tower->Calc(world);
	//当たり判定の更新
	this->_collisionNode.Update();
}

/*
 *@Towerオブジェクトの描画処理
 */
void Tower::Draw(shared_ptr<Camera> camera)
{
	//タワーの描画
	this->_Tower->Draw(camera);
	//当たり判定の描画
	this->_collisionNode.Draw();
}

/*
 *@Towerオブジェクトの後処理
 */
void Tower::Finalize()
{

}

