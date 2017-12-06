#include "AStarNode.h"

using namespace DirectX::SimpleMath;

AStarNode::AStarNode()
{

}

AStarNode::~AStarNode()
{

}

/*
 *@初期化処理
 */
void AStarNode::Initialize()
{
	//ノードの初期化
	_State = UNCHECKED;
	_Cost = 0;
	_Heuristic = 0;
	_parent = Enemy::NONE;
}

/*
 *@スコア取得
 */
int AStarNode::GetScore()
{
	return _Cost + _Heuristic;
}

/*
 *@終点設定
 */
void AStarNode::SetGoal(Vector3 trans)
{
	_GoalTrans = trans;
}

/*
 *@始点設定
 */
void AStarNode::SetVec(Vector3 trans)
{
	_Trans = trans;
}

void AStarNode::Open(Enemy::_Direction parent)
{
	//オープン状態にする
	_State = OPEN;

	//ペアレント登録
	_parent = parent;

	//ヒューリスティックコストの取得
	_Heuristic = (int)((_Trans.x - _GoalTrans.x) * (_Trans.x - _GoalTrans.x) + (_Trans.z - _GoalTrans.z) * (_Trans.z - _GoalTrans.z));
}