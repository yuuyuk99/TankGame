#pragma once
#include "AIState.h"
#include "../Player/Player.h"
#include "AStarNode.h"
#include "Enemy.h"
#include "../../Tower/Tower.h"

class Enemy;
class Player;
class Toewr;

class Move : public AIState
{
public:
	//コンストラクタ
	Move();
	//Moveクラスのインスタンスを取得する
	static std::shared_ptr<AIState> GetInstance();
	//実行処理
	void Execute(Enemy* enemy)override;
	//Moveオブジェクトを破棄する
	static void Finalize();
public:
	//プレイヤーとの距離
	float DistancePlayer(Enemy* enemy);
	//タワーとの距離
	float DistanceTower(Enemy* enemy);
public:
	//AstarNodeを参考にし、経路探索して、移動をする関数
	void Pathfinding(std::shared_ptr<Enemy> enemy);
private:
	//AIの状態
	static std::shared_ptr<AIState> _AIstate;
	//マップ
	//AstarNode* _FindMap[][]
	//移動速度
	DirectX::SimpleMath::Vector3 _Velocity;
	//砲台の回転速度
	float _RotationBattery;
	//マップ上での座標
	DirectX::SimpleMath::Vector3 _Pos;
	//現在の状態をint型で判断
	int _currentstateNum;
};
