#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <memory>
#include "../Base/ObjectBase.h"
#include "../Collision/CollisionNode.h"

class Camera;

class Tower
{
public:
	//�R���X�g���N�^
	Tower();
	//Tower�I�u�W�F�N�g�̏���������
	void Initialize();
	//Tower�I�u�W�F�N�g�̍X�V����
	void Update();
	//Tower�I�u�W�F�N�g�̕`�揈��
	void Draw(std::shared_ptr<Camera> camera);
	//Tower�I�u�W�F�N�g�̌㏈��
	void Finalize();
	//Tower�I�u�W�F�N�g�̓����蔻��
	CapsuleNode& GetCollsionNode() { return _collisionNode; }
	//�ϋv�x�̐ݒ�
	void SetHealth(int health) { _health = health; }
	//���݂̑ϋv�x���󂯓n��
	int GetHealth() { return _health; }
	//�^���[�̐w�n��ݒ�
	void SetCamp(int camp) { _camp = camp; }
	//�^���[�̐w�n�̏����󂯎��
	int GetCamp() { return _camp; }
	//���ݒn��ݒ肷��
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _Tower->SetTrans(trans); }
	//���ݒl���󂯓n��
	DirectX::SimpleMath::Vector3& GetTrans() { return _Tower->GetTrans(); }
private:
	//�^���[
	std::shared_ptr<ObjectBase> _Tower;
	//�����蔻��m�[�h
	CapsuleNode _collisionNode;
	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//�X�P�[��
	DirectX::SimpleMath::Vector3 _scale;
	//���[���h�s��
	DirectX::SimpleMath::Matrix _localWorld;
	//��]�ŃN�H�[�^�j�I�����g�p���邩
	bool _useQuternion;
	//�N�H�[�^�j�I���s��
	DirectX::SimpleMath::Quaternion _quternion;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//�������Ă��邩�ǂ���
	bool _hit;
	//�ϋv�x
	int _health;
	//�^���[�̐w�c
	int _camp;
};
