#pragma once
#include <Memory>
#include "../Tank.h"
#include "../PARTS/TankFactory.h"
#include "../../Collision/CollisionNode.h"
#include <Keyboard.h>
#include "../../Game.h"
#include "../../Collision/CollisionNode.h"

class Body;
class Turret;
class Bullet;
class Camera;

class Player
{
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//プレイヤーを初期化する
	void Initialize();
	//プレイヤーの更新をする
	void Update();
	//プレイヤーの描画をする
	void Draw(std::shared_ptr<Camera> camera);
	//プレイヤーの終了処理を行う
	void Finalize();
public:
	//座標の設定
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _body->SetTrans(trans); }
	//座標を受け渡す
	DirectX::SimpleMath::Vector3& GetTrans() { return _body->GetTrans(); }
	//回転座標の設定
	void SetRot(DirectX::SimpleMath::Vector3& rot) { _body->SetRot(rot); }
	//回転行列を受け渡す
	DirectX::SimpleMath::Vector3& GetRot() { return _body->GetRot(); }
	//当たり判定を受け渡す
	int GetTank(int num);
	//現在のワールド行列を受け流す
	//bodyの当たり判定
	inline SphereNode& GetCollisionNodeBody() { return _body->GetCollisionNode(); }
	//bulletの当たり判定
	inline SphereNode& GetCollisionNodeBullet() { return _bullet->GetCollisionNode(); }
	//現在の速度を受け渡す
	DirectX::SimpleMath::Vector3& GetVelocity() { return _body->GetVelocity(); }

private:
	//ボディ
	std::shared_ptr<Tank> _body;
	//砲塔
	std::shared_ptr<Tank> _turret;
	//球
	std::shared_ptr<Tank> _bullet;
	//キーボード
	std::shared_ptr<DirectX::Keyboard> _keyboard;

	
};