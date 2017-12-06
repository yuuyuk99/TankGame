#include "Enemy.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "../PARTS/Body.h"
#include "../PARTS/Turret.h"
#include "../PARTS/Bullet.h"
#include "../../Game.h"
#include "Move.h"
#include "AIState.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
 *@コンストラクタ
 */
Enemy::Enemy()
{
	_currentState = make_shared<AIState>();
}

/*
 *@Enemyオブジェクトの初期化
 */
void Enemy::Initialize()
{
	//Bodyオブジェクトを生成する
	this->_body = make_shared<Body>();
	//Bodyオブジェクトを初期化する
	this->_body->Initialize();
	//Turretオブジェクトを生成する
	this->_turret = make_shared<Turret>();
	//Turretオブジェクトを初期化する
	this->_turret->Initialize();
	//BodyオブジェクトにTurretオブジェクトを追加する
	this->_body->Add(move(this->_turret));
	//bulletオブジェクトを追加する
	this->_bullet = make_shared<Bullet>();
	//bulletオブジェクトを初期化する
	this->_bullet->Initialize();
	//turretオブジェクトにbulletオブジェクトを追加する
	this->_turret->Add(move(this->_bullet));

	this->_body->SetTrans(Vector3(7.5f, 0.0f, 15.0f));

	ChangeState(Move::GetInstance());
	

}

/*
 *@Enemyオブジェクトの更新
 */
void Enemy::Update()
{
	//現在の状態を実行する
 	_currentState->Execute(this);

	//Tankオブジェクトを更新する
	this->_body->Update(this->_body->GetLocalWorld());
}

/*
 *@状態の変更
 */
void Enemy::ChangeState(shared_ptr<AIState> currentState)
{
	this->_currentState = currentState;
}

/*
 *@Enemyオブジェクトの描画
 */
void Enemy::Draw(shared_ptr<Camera> camera)
{
	//tankオブジェクトを描画する
	this->_body->Draw(camera);
}

/*
 *@Enemyオブジェクトの後処理
 */
void Enemy::Finalize()
{

}