#include "Bullet.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../Graphics.h"
#include "../../Camera/Camera.h"
#include "../../Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/*
 *@コンストラクタ
 */
Bullet::Bullet()
{
	//bulletオブジェクトを生成
	_bullet = make_shared<ObjectBase>();
	//球を撃っていない処理にする
	_isStateShoot = false;
	//撃っている状態の時間
	_flagCount = 60.0f;
}

/*
 *@Bulletオブジェクトの初期化処理
 */
void Bullet::Initialize()
{
	//球のモデルを読み込む
	this->_bullet->LoadModelFile(L"Resources/cModels/bullet.cmo");

	//当たり判定ノードの設定
	//初期化
	_collisionNode.Initialize();
	//親行列の設定
	_collisionNode.SetParentMatrix(&this->_bullet->GetLocalWorld());
	//当たり判定
	_collisionNode.SetLocalradius(1.0f);
	//親からの距離
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	//球の大きさを設定
	this->_bullet->SetScale(Vector3(0.3f, 0.3f, 0.3f));
}

/*
 *@Bulletオブジェクトの更新処理
 *@引数 matrix 親の行列
 */
void Bullet::Update(Matrix& matrix)
{
	//親行列の反映
	_bullet->SetLocalWorld(matrix);

	//撃っている状態にする
	if (_isKeyDown)
	{
		ShootBullet(matrix);
	}

	//撃っている状態だったら
	if (_isStateShoot)
	{
		if (--_flagCount < 0.0f)
		{
			//球をもう一度セットする
			ResultBullet(matrix);
			//撃っていない状態に戻す
			_isStateShoot = false;
		}
	}

	//球の移動を行う
	_Pos += _bulletVel;
	this->_bullet->SetTrans(_Pos);

	//行列更新
	_bullet->Calc(matrix);

	//当たり判定の更新
	_collisionNode.Update();
}

/*
 *@Bulletオブジェクトの描画処理
 */
void Bullet::Draw(shared_ptr<Camera> camera)
{
	//球の描画
	this->_bullet->Draw(camera);

	//当たり判定ノード　
    _collisionNode.Draw();
}

/*
 *@Bulletオブジェクトの後処理
 */
void Bullet::Finalize()
{

}

/*
 *@Bulletオブジェクトを発射する
 */
void Bullet::ShootBullet(Matrix& matrix)
{
	if (_isStateShoot) return;

	//発射する弾丸の速度ベクトル
	_bulletVel = Vector3(0.0f, 0.0f, 0.3f);
	//ベクトルをクォータニオンで回転
	_bulletVel = Vector3::TransformNormal(_bulletVel, matrix);
	
	//球が発射されている時間
	_flagCount = 60;

	//撃った処理にする
	_isStateShoot = true;
}

/*
 *@撃った球をもとに戻す
 */
void Bullet::ResultBullet(Matrix& matrix)
{
	//発射中でない
	if (!_isStateShoot) return;

	//位置をもとに戻す
	_bullet->SetLocalWorld(matrix);
	//クォータニオンを使用していない状態に戻す
	_bullet->SetUseQuternion(false);
	//球の速度を０にする
	_bulletVel = Vector3(0.0f, 0.0f, 0.0f);
	//保存されていた位置を初期化する
	_Pos = Vector3(0.0f, 0.0f, 0.0f);
	//球の位置も初期化
	_bullet->SetTrans(Vector3(0.0f, 0.0f, 0.0f));

	//撃っていない状態にする
	_isStateShoot = false;
}

/*
 *@子オブジェクトを追加する
 */
void Bullet::Add(shared_ptr<Tank> && pNode)
{
	_child.emplace_back(pNode);
	//親ノードを設定する
	pNode->Parent(shared_from_this());
}

/*
 * @再帰的にオブジェクトを複製する
 */
shared_ptr<Tank> Bullet::Clone()
{
	//オブジェクトの複製を作る
	auto pClone = make_shared<Bullet>();
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

