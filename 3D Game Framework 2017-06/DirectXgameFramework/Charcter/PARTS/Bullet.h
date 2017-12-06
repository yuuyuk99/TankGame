#pragma once
#include "../Tank.h"
#include "Turret.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../Collision/CollisionNode.h"

class Bullet : public Tank, public std::enable_shared_from_this<Bullet>
{
public:
	//�R���X�g���N�^
	Bullet();
	//Bullet�I�u�W�F�N�g������������
	void Initialize() override;
	//Bullet�I�u�W�F�N�g���X�V����
	void Update(DirectX::SimpleMath::Matrix& matrix) override;
	//Bullet�I�u�W�F�N�g��`�悷��
	void Draw(std::shared_ptr<Camera> camera) override;
	//Bullet�I�u�W�F�N�g�̌㏈��
	void Finalize() override;
	//���𔭎˂��鏈��
	void ShootBullet(DirectX::SimpleMath::Matrix& matrix);
	//�������������Ƃɖ߂�
	void ResultBullet(DirectX::SimpleMath::Matrix& matrix);
	//�����蔻��m�[�h���󂯓n��
	//inline std::shared_ptr<SphereNode> GetCollisionNode() override { return _CollisionNode; }
	//�e�I�u�W�F�N�g��ݒ肷��
	void Add(std::shared_ptr<Tank>&& pNode) override;
	//�ċA�I�ɃI�u�W�F�N�g�𕡐�����
	std::shared_ptr<Tank> Clone() override;
	//���̏�Ԃ�ύX����
	void SetShootState(bool state) { _isStateShoot = state; }
	//���݂̋��̏�Ԃ��󂯓n��
	bool GetShootState() { return _isStateShoot; }
private:
	//����������Ă��邩�ǂ���
	bool _isStateShoot;
	//���̌��ݒl
	DirectX::SimpleMath::Vector3 _bulletPos;
	//������鋅�̑��x
	DirectX::SimpleMath::Vector3 _bulletVel;
	//��������̃f�B���C
	float _flagCount;
	//�|�C���^�̊i�[
	std::vector<std::shared_ptr<Tank>> _child;
	//CommonStates
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//���f��
	std::unique_ptr<DirectX::Model> _model;
	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//�X�P�[��
	DirectX::SimpleMath::Vector3 _scale;
};
