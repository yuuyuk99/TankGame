#include "Body.h"
#include <Windows.h>
#include "../../Graphics.h"
#include "../../Game.h"
#include "../../Camera/Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;
//using Microsoft::WRL::ComPtr;

/*
 *@コンストラクタ
 */
Body::Body()
{
	//オブジェクト
	_body = make_shared<ObjectBase>();
	//当たっていない状態から開始する
	_hit = false;
	//大きさを変更する
	_scale = Vector3(1.0f, 1.0f, 1.0f);
	//キーボードを取得する
	_keyboard = make_shared<Keyboard::State>();
	//角度の設定
	_angle = 0.0f;
	//移動速度
	_Velocity = Vector3(0.0f, 0.0f, 0.0f);
}

/*
 *@Bodyオブジェクトを初期化する
 */
void Body::Initialize()
{
	//bodyのモデルを読み込む
	this->_body->LoadModelFile(L"Resources/cModels/Body.cmo");

	//当たり判定の初期化
	_collisionNode.Initialize();
	//当たり判定のワールド座標を
	_collisionNode.SetParentMatrix(&this->_body->GetLocalWorld());
	//当たり判定の大きさを設定
	_collisionNode.SetLocalradius(1.0f);
	//当たり判定が親からどれだけ離れているか
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));


}

/*
 *@Bodyオブジェクトを更新する
 */
void Body::Update(Matrix& matrix)
{
	//親の行列を受け取る
	_body->SetLocalWorld(matrix);
	//行列更新
	_body->Calc(matrix);
	//子供の更新処理を呼び出す
	for (auto child : _child)
	{
		child->Update(_body->GetLocalWorld());
	}
	
	//当たり判定の更新
	_collisionNode.Update();
}


/*
 *@Bodyオブジェクトの描画を行う
 */
void Body::Draw(shared_ptr<Camera> camera)
{
	//bodyの描画を行う
	this->_body->Draw(camera);
	//子供の描画処理を呼び出す
	for (auto child : _child)
	{
		child->Draw(camera);
	}
	//当たり判定の描画
	_collisionNode.Draw();
}

/*
 *@Bodyオブジェクトの後処理を行う
 */
void Body::Finalize()
{
	
}

/*
 *@球に衝突した時の処理
 */
void Body::HitEffect()
{
	static float time = 0.0f;
	//
	if (_hit)
	{
		//動けないようにする
		_body->SetTrans(_body->GetTrans());
		time++;
	}
	//一定時間たったら
	if (time > 60)
	{
		_hit = false;
		time = 0.0f;
	}
}

/*
 *@子オブジェクトを追加する
 */
void Body::Add(shared_ptr<Tank>&& pNode)
{
	//Node,Leafオブジェクトのポインタを追加する
	_child.emplace_back(pNode);
	//親ノードを設定する
	pNode->Parent(shared_from_this());
}

/*
 *@再起的にオブジェクトを複製する
 */
shared_ptr<Tank> Body::Clone()
{
	//オブジェクトの複製を作る
	auto pClone = make_shared<Body>();
	//リストをクリアする
	pClone->_child.clear();
	//すべてのリストの要素を参照する
	for (auto& child : _child)
	{
		//複製された子オブジェクトをリストに追加する
		pClone->Add(child->Clone());
	}
	return pClone;
}
