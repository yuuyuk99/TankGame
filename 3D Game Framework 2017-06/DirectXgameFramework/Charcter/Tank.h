#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <memory>
#include <Model.h>
#include <Keyboard.h>

#include "../Base/ObjectBase.h"
#include "../Collision/CollisionNode.h"

class Camera;

class Tank
{
public:
	enum ID {
		PARTS_BODY,
		PARS_TURRET,
		PARTS_BULLET,

		PARTS_NUM
	};
	//�ʒu
	DirectX::SimpleMath::Vector3 Position() { return _Pos; }
	void Position(DirectX::SimpleMath::Vector3 position) { this->_Pos = position; }

	//�R���X�g���N�^
	Tank();
	Tank(DirectX::SimpleMath::Vector3& position);

	//Tank�I�u�W�F�N�g������������
	virtual void Initialize() {}
	//Tank�I�u�W�F�N�g���X�V����
	virtual void Update(DirectX::SimpleMath::Matrix& matrix) {}
	//Tank�I�u�W�F�N�g��`�悷��
	//void Draw();
	virtual void Draw(std::shared_ptr<Camera>) {}
	//�㏈�����s��
	virtual void Finalize() {}
	//�e�I�u�W�F�N�g��ݒ肷��
	virtual void Add(std::shared_ptr<Tank>&& pNode) = 0;
	//�e�I�u�W�F�N�g���擾����
	std::weak_ptr<Tank> Parent();
	//�e�I�u�W�F�N�g��ݒ肷��
	void Parent(const std::shared_ptr<Tank>& parent);
	//�ċN�I�ɃI�u�W�F�N�g�𕡐�����
	virtual std::shared_ptr<Tank> Clone() = 0;
	//����������
	void SetKeyDown(bool state) { _isKeyDown = state; }
public:
	//�|�W�V������ݒ肷��
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _body->SetTrans(trans); }
	//���݈ʒu���󂯓n��
	DirectX::SimpleMath::Vector3& GetTrans() { return _body->GetTrans(); }
	//���x��ݒ肷��
	void SetVelocity(DirectX::SimpleMath::Vector3& vel) { _Velocity = vel; }
	//���x���󂯎��
	DirectX::SimpleMath::Vector3& GetVelocity() { return _Velocity; }
	//��]����ݒ肷��
	void SetRot(DirectX::SimpleMath::Vector3& rot) { _body->SetRot(rot); }
	//��]�����󂯓n��
	DirectX::SimpleMath::Vector3& GetRot() { return _body->GetRot(); }
	//�p�x��ݒ�
	void SetAngle(float angle) { _angle = angle; }
	//�p�x���󂯓n��
	float GetAngle() { return _angle; }
	//body�̓����蔻����󂯓n��
	SphereNode& GetCollisionNode() { return _collisionNode; }
	//���[�J���s����󂯓n��
	DirectX::SimpleMath::Matrix& GetLocalWorld() { return _body->GetLocalWorld(); }
protected:
	//�ʒu
	DirectX::SimpleMath::Vector3 _Pos;
	//���x
	DirectX::SimpleMath::Vector3 _Velocity;
	//��]
	DirectX::SimpleMath::Vector3 _Rot;
	//�p�x(float�^)
	float _angle;
	//�q�I�u�W�F�N�g�ւ̃|�C���^
	std::shared_ptr<Tank> _Child;
	//Root�I�u�W�F�N�g�ւ̃|�C���^
	std::shared_ptr<Tank> _Root;
	//
	std::weak_ptr<Tank> _parent;
	//�L�[�{�[�h
	std::shared_ptr<DirectX::Keyboard::State> _keyboard;
	//Body�I�u�W�F�N�g
	std::shared_ptr<ObjectBase> _body;
	//turret�I�u�W�F�N�g
	std::shared_ptr<ObjectBase> _turret;
	//bullet�I�u�W�F�N�g
	std::shared_ptr<ObjectBase> _bullet;
	//�����蔻��m�[�h
	SphereNode _collisionNode;
	//���������Ă��邩�ǂ����̏���
	bool _isKeyDown;
};
