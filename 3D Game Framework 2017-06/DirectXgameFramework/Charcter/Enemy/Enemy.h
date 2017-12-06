#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../Tank.h"
#include "../PARTS/TankFactory.h"

class Player;
class Tank;
class AIState;
class GameObject;
class Tower;

//敵に関するクラスです
class Enemy{
public:
	enum _Direction
	{
		NONE,
		UP,
		RIGHT,
		DOWN,
		LEFT,

		NUM_DIRECTION
	};
	//コンストラクタ
	Enemy();
	//初期化
	void Initialize();
	//更新
	void Update();
	//状態を変更する
	void ChangeState(std::shared_ptr<AIState> currentState);
	//描画
	void Draw(std::shared_ptr<Camera> camera);
	//終了処理(オブジェクトを破棄する処理)
	void Finalize();
public:
	//Enemyの座標を設定する
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _body->SetTrans(trans); }
	//Enemyの座標を受け渡す
	const DirectX::SimpleMath::Vector3& GetTrans() { return _body->GetTrans(); }
	//Enemyの回転座標を設定
	void SetRot(DirectX::SimpleMath::Vector3& rot) { _body->SetRot(rot); }
	//Enemyの回転座標を受け取る
	const DirectX::SimpleMath::Vector3& GetRot() { return _body->GetRot(); }
	//bodyの当たり判定を返す
	inline SphereNode& GetCollisionnodeBody() { return _body->GetCollisionNode(); }
	//bulletの当たり判定を
	inline SphereNode& GetCollisionNodeBullet() { return _bullet->GetCollisionNode(); }
	//球を撃つ
	void SetShootBullet(bool state) { _bullet->SetKeyDown(state); }
public: 
	//プレイヤーの情報を返す
	std::shared_ptr<Player> GetPlayer() { return _Player; }
	//プレイヤーの情報を受け取る
	void SetPlayer(std::shared_ptr<Player> player) { _Player = (player); }
	//プレイヤーとの距離を受け渡す
	double GetDistancePlayer() { return _distance; }
public:
	//タワーの情報を返す
	std::shared_ptr<Tower> GetTower() { return _tower; }
	//タワーの情報を受け取る
	void SetTower(std::shared_ptr<Tower> tower) { _tower = tower; }
	//タワーとの距離を受け渡す
	double GetDistanceTower() { return _distanceT; }
private:
	//AIのステートパターン
	std::shared_ptr<AIState> _currentState;
	//プレイヤー
	std::shared_ptr<Player> _Player;
	//プレイヤーとの距離
	double _distance;
private:
	//タワー
	std::shared_ptr<Tower> _tower;
	//タワーとの距離を求める
	double _distanceT;
private:
	//Tankパーツ
	std::shared_ptr<Tank> _tank;
	//bodyパーツ
	std::shared_ptr<Tank> _body;
	//Turretパーツ
	std::shared_ptr<Tank> _turret;
	//Bulletパーツ
	std::shared_ptr<Tank> _bullet;
};

