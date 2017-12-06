#pragma once
#include <Memory>
#include "../Tank.h"
#include "../PARTS/TankFactory.h"
#include "../../Collision/CollisionNode.h"
#include <Keyboard.h>
#include "../../Game.h"
#include "../../Collision/CollisionNode.h"

class Body;
class Turret;
class Bullet;
class Camera;

class Player
{
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//�v���C���[������������
	void Initialize();
	//�v���C���[�̍X�V������
	void Update();
	//�v���C���[�̕`�������
	void Draw(std::shared_ptr<Camera> camera);
	//�v���C���[�̏I���������s��
	void Finalize();
public:
	//���W�̐ݒ�
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _body->SetTrans(trans); }
	//���W���󂯓n��
	DirectX::SimpleMath::Vector3& GetTrans() { return _body->GetTrans(); }
	//��]���W�̐ݒ�
	void SetRot(DirectX::SimpleMath::Vector3& rot) { _body->SetRot(rot); }
	//��]�s����󂯓n��
	DirectX::SimpleMath::Vector3& GetRot() { return _body->GetRot(); }
	//�����蔻����󂯓n��
	int GetTank(int num);
	//���݂̃��[���h�s����󂯗���
	//body�̓����蔻��
	inline SphereNode& GetCollisionNodeBody() { return _body->GetCollisionNode(); }
	//bullet�̓����蔻��
	inline SphereNode& GetCollisionNodeBullet() { return _bullet->GetCollisionNode(); }
	//���݂̑��x���󂯓n��
	DirectX::SimpleMath::Vector3& GetVelocity() { return _body->GetVelocity(); }

private:
	//�{�f�B
	std::shared_ptr<Tank> _body;
	//�C��
	std::shared_ptr<Tank> _turret;
	//��
	std::shared_ptr<Tank> _bullet;
	//�L�[�{�[�h
	std::shared_ptr<DirectX::Keyboard> _keyboard;

	
};