#pragma once

#include "../Tank.h"
#include <CommonStates.h>

class Turret : public Tank, public std::enable_shared_from_this<Turret>
{
public:
	//�R���X�g���N�^
	Turret();
	//Body�I�u�W�F�N�g������������
	void Initialize() override;
	//Body�I�u�W�F�N�g���X�V
	void Update(DirectX::SimpleMath::Matrix& matrix) override;
	//Body�I�u�W�F�N�g��`��
	void Draw(std::shared_ptr<Camera> camera) override;
	//Body�I�u�W�F�N�g�̌㏈�����s��
	void Finalize() override;
	//�e�I�u�W�F�N�g��ݒ肷��
	void Add(std::shared_ptr<Tank>&& pNode) override;
	//�ċA�I�ɃI�u�W�F�N�g�𕡐�����
	std::shared_ptr<Tank> Clone() override;
protected:
	//�|�C���^�̊i�[
	std::vector<std::shared_ptr<Tank>> _child;
	//CommonState
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//���f��
	std::unique_ptr<DirectX::Model> _model;
	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//�X�P�[��
	DirectX::SimpleMath::Vector3 _scale;
};