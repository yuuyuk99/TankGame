#include "Player.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "../PARTS/Body.h"
#include "../PARTS/Turret.h"
#include "../PARTS/Bullet.h"
#include "../../Game.h"
#include "../../Camera/Camera.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
 *@コンストラクタ
 */
Player::Player()
{
	
}

/*
 *@デストラクタ
 */
Player::~Player()
{

}

/*
 *@Playerの初期化処理
 */
void Player::Initialize()
{
	//Bodyオブジェクトを生成する
	this->_body = make_shared<Body>();
	//Bodyオブジェクトの初期化
	this->_body->Initialize();
	//Turretオブジェクトを生成する
	this->_turret = make_shared<Turret>();
	//Turretオブジェクトの初期化
	this->_turret->Initialize();
	//BodyオブジェクトにTurretオブジェクトを追加する
	this->_body->Add(move(this->_turret));
	//bulletオブジェクトの生成
	this->_bullet = make_shared<Bullet>();
	//bulletオブジェクトの初期化
	this->_bullet->Initialize();
	//turretオブジェクトにbulletオブジェクトを追加する
	this->_turret->Add(move(this->_bullet));

	//自機の初期位置を変更
	this->_body->SetTrans(Vector3(7.5f, 0.0f, 10.0f));
}

/*
 *@Playerの更新処理
 */
void Player::Update()
{
	//Bodyオブジェクトの速度を初期化する
	this->_body->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));

	//オブジェクトを右に回転する
	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::A))
	{
		//回転する
		Vector3 rot = _body->GetRot();
		//回転した値を入れる
		rot += Vector3(0.0f, XMConvertToRadians(1.0f), 0.0f);
		//bodyに回転させた値を入れる
		_body->SetRot(rot);
	}
	//オブジェクトを左に回転する
	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::D))
	{
		//回転
		Vector3 rot = _body->GetRot();
		//回転
		rot += Vector3(0.0f, -XMConvertToRadians(1.0f), 0.0f);
		//bodyに回転させた値を入れる
		_body->SetRot(rot);
	}
	//前進
	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::W))
	{

		//現在の座標回転角を取得
		Vector3 trans = _body->GetTrans();
		float rot_y = _body->GetRot().y;
		//移動ベクトル
		Vector3 move(0.0f, 0.0f, 0.1f);
		Matrix rotm = Matrix::CreateRotationY(rot_y);
		//移動ベクトルを回転する
		move = Vector3::TransformNormal(move, rotm);
		//移動する
		trans += move;
		//移動を行う
		_body->SetTrans(trans);
	}
	//後進
	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::S))
	{
		//現在の座標回転角を取得
		Vector3 trans = _body->GetTrans();
		float rot_y = _body->GetRot().y;
		//移動ベクトル
		Vector3 move(0.0f, 0.0f, -0.1f);
		Matrix rotm = Matrix::CreateRotationY(rot_y);
		//移動ベクトルを回転する
		move = Vector3::TransformNormal(move, rotm);
		//移動する
		trans += move;
		//移動を行う
		_body->SetTrans(trans);
	}

	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::R))
	{
		//ボタンが押されている状態にする
		this->_bullet->SetKeyDown(true);
		//球を発射する
		this->_bullet->Update(this->_body->GetLocalWorld());
	}
	
	//何もボタンを押していない状態にする
	this->_bullet->SetKeyDown(false);

	//Tankオブジェクトを更新する
	//再起関数なのでbodyのchildも呼ばれる
	this->_body->Update(this->_body->GetLocalWorld());

}

/*
 *@プレイヤーの描画処理
 */
void Player::Draw(shared_ptr<Camera> camera)
{
	//Tankオブジェクトを描画する
	this->_body->Draw(camera);
}

/*
 *@プレイヤーの後処理
 */
void Player::Finalize()
{
	//Tankオブジェクトの終了処理を行う
	this->_body->Finalize();
}

/*
*@パーツごとに当たり判定を受け渡す
*/
int Player::GetTank(int num)
{
	return num;
}