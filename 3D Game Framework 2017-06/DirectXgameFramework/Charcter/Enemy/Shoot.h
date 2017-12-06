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
 *@��������������EnemyClass�ɂ̂ݓK�������
 *@�ŏ��̐݌v��AI�������Ƃ������ӎ������̂Ńv���C���[�ɗ��p�ł��Ȃ�
 */
class Shoot : public AIState
{
public:
	//�R���X�g���N�^
	Shoot();
	//Shoot�N���X�̃C���X�^���X���擾����
	static std::shared_ptr<AIState> GetInstance();
	//���s����
	void Execute(Enemy* enemy) override;
	//Shoot�̃I�u�W�F�A�r��j������
	static void Finalize();
private:
	//AI�̏��
	static std::shared_ptr<AIState> _AIstate;
	//���̑��x
	DirectX::SimpleMath::Vector3 _Velocity;
	//�A���őłĂȂ��悤�ɂ��邽��
	float _delay;
	//��
};