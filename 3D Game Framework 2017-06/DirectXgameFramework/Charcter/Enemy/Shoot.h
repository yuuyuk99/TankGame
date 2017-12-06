#pragma once
#include "AIState.h"
#include "Shoot.h"
#include <d3d11.h>
#include <SimpleMath.h>

class Enemy;
class Player;
class Tower;

/*
 *@Shoot
 *@球を撃つ処理だがEnemyClassにのみ適応される
 *@最初の設計でAIが撃つことだけを意識したのでプレイヤーに流用できない
 */
class Shoot : public AIState
{
public:
	//コンストラクタ
	Shoot();
	//Shootクラスのインスタンスを取得する
	static std::shared_ptr<AIState> GetInstance();
	//実行処理
	void Execute(Enemy* enemy) override;
	//Shootのオブジェ帰途を破棄する
	static void Finalize();
private:
	//AIの状態
	static std::shared_ptr<AIState> _AIstate;
	//球の速度
	DirectX::SimpleMath::Vector3 _Velocity;
	//連続で打てないようにするため
	float _delay;
	//球
};