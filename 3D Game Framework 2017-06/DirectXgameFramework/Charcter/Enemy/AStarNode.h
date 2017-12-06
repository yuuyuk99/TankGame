#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "Enemy.h"

class AStarNode
{
public:
	//状態
	enum STATE
	{
		UNCHECKED,
		OPEN,
		CLOSED,
		CONFIRM,
	};
	//コンストラクタ
	AStarNode();
	//デストラクタ
	~AStarNode();
	//初期化処理
	void Initialize();
	//現在の状態を設定する
	void SetState(STATE state) { _State = state; }
	//現在の状態を受け渡す
	STATE GetState() { return _State; }
	//現在のスコアを返す
	int GetScore();
	//マップのコストを設定する
	void SetCost(int cost) { _Cost = cost; }
	//マップのコストを受け渡す
	int GetCost() { return _Cost; }
	//終点設定
	void SetGoal(DirectX::SimpleMath::Vector3 trans);
	//自身の座標の設定
	void SetVec(DirectX::SimpleMath::Vector3 trans);
	//オープン
	void Open(Enemy::_Direction parent);
private:
	//状態
	STATE _State;
	//移動のコスト
	int _Cost;
	//ヒューリスティック
	int _Heuristic;
	//座標
	DirectX::SimpleMath::Vector3 _Trans;
	//終点座標
	DirectX::SimpleMath::Vector3 _GoalTrans;
	//さかのぼる方向
	int _parent;
};