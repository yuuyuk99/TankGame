#pragma once
#include "Stage.h"

class Floor{
public:
	//�R���X�g���N�^
	Floor();
	//�f�X�g���N�^
	~Floor();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw(std::shared_ptr<Camera> camera);
	//�I������
	void Finalize();
private:
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//��
	std::shared_ptr<ObjectBase> _floor;
	//���̓����蔻��
	SphereNode _collisionNode;
};