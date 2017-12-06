#include "Turret.h"
#include <Windows.h>
#include "../../Graphics.h"
#include "../../Camera/Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/*
*@コンストラクタ
*/
Turret::Turret()
{
	//turretオブジェクトを生成
	_turret = make_shared<ObjectBase>();
	//turretの大きさの設定
	_scale = Vector3(0.5f, 0.5f, 0.5f);
}

/*
*@Turretオブジェクトを初期化する
*/
void Turret::Initialize()
{
	//turretのモデルを読み込む
	this->_turret->LoadModelFile(L"Resources/cModels/turret.cmo");
	//大きさを設定
	_turret->SetScale(_scale);
}

/*
*@Turretオブジェクトを更新する
*/
void Turret::Update(Matrix& matrix)
{
	//親の行列を反映
	_turret->SetLocalWorld(matrix);

	//親オブジェクトからturretの移動
	_turret->SetTrans(Vector3(0.0f, 0.5f, 0.0f));

	//turretの行列更新
	_turret->Calc(matrix);

	//turretのchildの更新
	for (auto child : _child)
	{
		child->Update(_turret->GetLocalWorld());
	}
}


/*
*@Turretオブジェクトの描画を行う
*/
void Turret::Draw(shared_ptr<Camera> camera)
{
	//turretの描画
	_turret->Draw(camera);

	//turretのchildの描画
	for (auto child : _child)
	{
		child->Draw(camera);
	}
}

/*
*@Turretオブジェクトの後処理を行う
*/
void Turret::Finalize()
{

}

/*
 *@子オブジェクトを追加する
 */
void Turret::Add(shared_ptr<Tank>&& pNode)
{
	_child.emplace_back(pNode);
	//親ノードを設定する
	pNode->Parent(shared_from_this());
}

/*
 * @再帰的にオブジェクトを複製する
 */
shared_ptr<Tank> Turret::Clone()
{
	//オブジェクトの複製をつくる
	auto pClone = make_shared<Turret>();
	//リストをクリアする
	pClone->_child.clear();
	for (auto& child : _child)
	{
		//複製された子オブジェクトをリストに追加する
		pClone->Add(child->Clone());
	}
	return pClone;
}