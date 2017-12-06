#include "AStarNode.h"

using namespace DirectX::SimpleMath;

AStarNode::AStarNode()
{

}

AStarNode::~AStarNode()
{

}

/*
 *@����������
 */
void AStarNode::Initialize()
{
	//�m�[�h�̏�����
	_State = UNCHECKED;
	_Cost = 0;
	_Heuristic = 0;
	_parent = Enemy::NONE;
}

/*
 *@�X�R�A�擾
 */
int AStarNode::GetScore()
{
	return _Cost + _Heuristic;
}

/*
 *@�I�_�ݒ�
 */
void AStarNode::SetGoal(Vector3 trans)
{
	_GoalTrans = trans;
}

/*
 *@�n�_�ݒ�
 */
void AStarNode::SetVec(Vector3 trans)
{
	_Trans = trans;
}

void AStarNode::Open(Enemy::_Direction parent)
{
	//�I�[�v����Ԃɂ���
	_State = OPEN;

	//�y�A�����g�o�^
	_parent = parent;

	//�q���[���X�e�B�b�N�R�X�g�̎擾
	_Heuristic = (int)((_Trans.x - _GoalTrans.x) * (_Trans.x - _GoalTrans.x) + (_Trans.z - _GoalTrans.z) * (_Trans.z - _GoalTrans.z));
}