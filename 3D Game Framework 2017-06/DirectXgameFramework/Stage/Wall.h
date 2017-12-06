#pragma once
#include <CommonStates.h>
#include <Effects.h>
#include <memory>
#include "../Camera/Camera.h"
#include "../Collision/CollisionNode.h"

class Wall
{
public:
	//�R���X�g���N�^
	Wall();
	//�f�X�g���N�^
	~Wall();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw(std::shared_ptr<Camera> camera);
	//�I������
	void Finalize();
	//�����蔻��
	SphereNode& GetCollisionNode() { return _collisionNode; }
	//�ʒu���w�肷��
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _wall->SetTrans(trans); }
	//���݈ʒu���󂯓n��
	DirectX::SimpleMath::Vector3& GetTrans() { return _wall->GetTrans(); }
private:
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//��
	std::shared_ptr<ObjectBase> _wall;
	//���̓����蔻��
	SphereNode _collisionNode;
};