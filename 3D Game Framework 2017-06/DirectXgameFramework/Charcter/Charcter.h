#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../Base/ObjectBase.h"
//#include "../Collision/CollisionNode.h"
//#include "../Map/Map.h"

enum TANK
{
	//�{��(���ꂪ���S�ƂȂ�)
	PARTS_TANK,
	//�C��
	PARTS_BATTERY,
	//���˂��鋅
	PARTS_BULLET,

	//�p�[�c�̌�
	TANK_NUM
};

//���삷��L�����N�^�[��G�̐e�N���X�ɂȂ�܂�
class Charcter
{
public:
	Charcter();
	~Charcter();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Calc() = 0;
	virtual void Draw() = 0;

	//���݂̏ꏊ���󂯎��
	const DirectX::SimpleMath::Vector3& GetTrans();
	//�ꏊ�̐ݒ�
	void SetTrans(DirectX::SimpleMath::Vector3& trans);
	//��]��ݒ�
	void SetRot(DirectX::SimpleMath::Vector3& rot);
	//��]�s����󂯎��
	const DirectX::SimpleMath::Vector3& GetRot();
	// ���[���h�s����擾
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
	//�v���C���[�{�̓����蔻��
	//const Sphere& GetCollisionBody() { return _CollisionNodeBody; }
	//���̂����蔻��
	//const Capsule& GetCollisionBullet() { return _CollisionNodeBullet; }
protected:
	//�L�����N�^�[
	ObjectBase m_Charcter[TANK_NUM];
	//����ł��Ă����Ԃ�
	bool _isShootState;
	//�����蔻��
	//SphereNode _CollisionNodeBody;
	//���̂����蔻��
	//CapsuleNode _CollisionNodeBullet;
	//�L�����N�^�[�����̗̑�
	float _health;
	//�_���[�W���󂯂Ă����Ԃ�
	bool _isDamegeState;
	//����ł��Ă��邩
	bool _isShoot;
	//�}�b�v�ւ̃|�C���^
	//Map* _Map;
	//�}�b�v��ł̍��W
	DirectX::SimpleMath::Vector3 _Pos;
};