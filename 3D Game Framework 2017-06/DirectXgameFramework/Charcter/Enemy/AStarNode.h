#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "Enemy.h"

class AStarNode
{
public:
	//���
	enum STATE
	{
		UNCHECKED,
		OPEN,
		CLOSED,
		CONFIRM,
	};
	//�R���X�g���N�^
	AStarNode();
	//�f�X�g���N�^
	~AStarNode();
	//����������
	void Initialize();
	//���݂̏�Ԃ�ݒ肷��
	void SetState(STATE state) { _State = state; }
	//���݂̏�Ԃ��󂯓n��
	STATE GetState() { return _State; }
	//���݂̃X�R�A��Ԃ�
	int GetScore();
	//�}�b�v�̃R�X�g��ݒ肷��
	void SetCost(int cost) { _Cost = cost; }
	//�}�b�v�̃R�X�g���󂯓n��
	int GetCost() { return _Cost; }
	//�I�_�ݒ�
	void SetGoal(DirectX::SimpleMath::Vector3 trans);
	//���g�̍��W�̐ݒ�
	void SetVec(DirectX::SimpleMath::Vector3 trans);
	//�I�[�v��
	void Open(Enemy::_Direction parent);
private:
	//���
	STATE _State;
	//�ړ��̃R�X�g
	int _Cost;
	//�q���[���X�e�B�b�N
	int _Heuristic;
	//���W
	DirectX::SimpleMath::Vector3 _Trans;
	//�I�_���W
	DirectX::SimpleMath::Vector3 _GoalTrans;
	//�����̂ڂ����
	int _parent;
};