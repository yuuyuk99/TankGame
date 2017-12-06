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

//�G�Ɋւ���N���X�ł�
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
	//�R���X�g���N�^
	Enemy();
	//������
	void Initialize();
	//�X�V
	void Update();
	//��Ԃ�ύX����
	void ChangeState(std::shared_ptr<AIState> currentState);
	//�`��
	void Draw(std::shared_ptr<Camera> camera);
	//�I������(�I�u�W�F�N�g��j�����鏈��)
	void Finalize();
public:
	//Enemy�̍��W��ݒ肷��
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _body->SetTrans(trans); }
	//Enemy�̍��W���󂯓n��
	const DirectX::SimpleMath::Vector3& GetTrans() { return _body->GetTrans(); }
	//Enemy�̉�]���W��ݒ�
	void SetRot(DirectX::SimpleMath::Vector3& rot) { _body->SetRot(rot); }
	//Enemy�̉�]���W���󂯎��
	const DirectX::SimpleMath::Vector3& GetRot() { return _body->GetRot(); }
	//body�̓����蔻���Ԃ�
	inline SphereNode& GetCollisionnodeBody() { return _body->GetCollisionNode(); }
	//bullet�̓����蔻���
	inline SphereNode& GetCollisionNodeBullet() { return _bullet->GetCollisionNode(); }
	//��������
	void SetShootBullet(bool state) { _bullet->SetKeyDown(state); }
public: 
	//�v���C���[�̏���Ԃ�
	std::shared_ptr<Player> GetPlayer() { return _Player; }
	//�v���C���[�̏����󂯎��
	void SetPlayer(std::shared_ptr<Player> player) { _Player = (player); }
	//�v���C���[�Ƃ̋������󂯓n��
	double GetDistancePlayer() { return _distance; }
public:
	//�^���[�̏���Ԃ�
	std::shared_ptr<Tower> GetTower() { return _tower; }
	//�^���[�̏����󂯎��
	void SetTower(std::shared_ptr<Tower> tower) { _tower = tower; }
	//�^���[�Ƃ̋������󂯓n��
	double GetDistanceTower() { return _distanceT; }
private:
	//AI�̃X�e�[�g�p�^�[��
	std::shared_ptr<AIState> _currentState;
	//�v���C���[
	std::shared_ptr<Player> _Player;
	//�v���C���[�Ƃ̋���
	double _distance;
private:
	//�^���[
	std::shared_ptr<Tower> _tower;
	//�^���[�Ƃ̋��������߂�
	double _distanceT;
private:
	//Tank�p�[�c
	std::shared_ptr<Tank> _tank;
	//body�p�[�c
	std::shared_ptr<Tank> _body;
	//Turret�p�[�c
	std::shared_ptr<Tank> _turret;
	//Bullet�p�[�c
	std::shared_ptr<Tank> _bullet;
};

