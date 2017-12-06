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
	//�R���X�g���N�^
	Move();
	//Move�N���X�̃C���X�^���X���擾����
	static std::shared_ptr<AIState> GetInstance();
	//���s����
	void Execute(Enemy* enemy)override;
	//Move�I�u�W�F�N�g��j������
	static void Finalize();
public:
	//�v���C���[�Ƃ̋���
	float DistancePlayer(Enemy* enemy);
	//�^���[�Ƃ̋���
	float DistanceTower(Enemy* enemy);
public:
	//AstarNode���Q�l�ɂ��A�o�H�T�����āA�ړ�������֐�
	void Pathfinding(std::shared_ptr<Enemy> enemy);
private:
	//AI�̏��
	static std::shared_ptr<AIState> _AIstate;
	//�}�b�v
	//AstarNode* _FindMap[][]
	//�ړ����x
	DirectX::SimpleMath::Vector3 _Velocity;
	//�C��̉�]���x
	float _RotationBattery;
	//�}�b�v��ł̍��W
	DirectX::SimpleMath::Vector3 _Pos;
	//���݂̏�Ԃ�int�^�Ŕ��f
	int _currentstateNum;
};
