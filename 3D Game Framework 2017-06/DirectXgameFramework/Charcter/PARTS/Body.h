#pragma once
#include "../Tank.h"
#include "../../Collision/CollisionNode.h"
#include <CommonStates.h>
#include <Effects.h>

class Body : public Tank, public std::enable_shared_from_this<Body>
{
public:
	//�R���X�g���N�^
	Body();
	//Body�I�u�W�F�N�g������������
	void Initialize() override;
	//Body�I�u�W�F�N�g���X�V
	void Update(DirectX::SimpleMath::Matrix& matrix) override;
	//Body�I�u�W�F�N�g��`��
	void Draw(std::shared_ptr<Camera> camera) override;
	//Body�I�u�W�F�N�g�̌㏈�����s��
	void Finalize() override;
	//�q�I�u�W�F�N�g��ǉ�����
	void Add(std::shared_ptr<Tank>&& pNode) override;
	//�����蔻��
	//inline std::shared_ptr<SphereNode> GetCollisionNode() override { return _collisionNode; }
	//���ɓ����������󂯓n��
	bool GetHit() { return _hit; }
	//���ɓ���������
	void SetHit(bool hit) { _hit = hit; }
	//���ɓ����������̔���
	void HitEffect();
	//�ċA�I�ɃI�u�W�F�N�g�𕡐�����
	std::shared_ptr<Tank> Clone() override;
	//���ݒn��ݒ肷��
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _body->SetTrans(trans); }
	//���ݒl���󂯓n��
	DirectX::SimpleMath::Vector3& GetTrans() { return _body->GetTrans(); }
private:
	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//�������Ă��邩�ǂ���
	bool _hit;
	//�X�P�[��
	DirectX::SimpleMath::Vector3 _scale;
	//���[���h�s��
	DirectX::SimpleMath::Matrix _localWorld;
	//��]�ŃN�H�[�^�j�I�����g�p���邩
	bool _useQuternion;
	//�N�H�[�^�j�I���s��
	DirectX::SimpleMath::Quaternion _quternion;
	//�|�C���^�̊i�[������
	std::vector<std::shared_ptr<Tank>> _child;
};