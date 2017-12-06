#include "Bullet.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../Graphics.h"
#include "../../Camera/Camera.h"
#include "../../Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/*
 *@�R���X�g���N�^
 */
Bullet::Bullet()
{
	//bullet�I�u�W�F�N�g�𐶐�
	_bullet = make_shared<ObjectBase>();
	//���������Ă��Ȃ������ɂ���
	_isStateShoot = false;
	//�����Ă����Ԃ̎���
	_flagCount = 60.0f;
}

/*
 *@Bullet�I�u�W�F�N�g�̏���������
 */
void Bullet::Initialize()
{
	//���̃��f����ǂݍ���
	this->_bullet->LoadModelFile(L"Resources/cModels/bullet.cmo");

	//�����蔻��m�[�h�̐ݒ�
	//������
	_collisionNode.Initialize();
	//�e�s��̐ݒ�
	_collisionNode.SetParentMatrix(&this->_bullet->GetLocalWorld());
	//�����蔻��
	_collisionNode.SetLocalradius(1.0f);
	//�e����̋���
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	//���̑傫����ݒ�
	this->_bullet->SetScale(Vector3(0.3f, 0.3f, 0.3f));
}

/*
 *@Bullet�I�u�W�F�N�g�̍X�V����
 *@���� matrix �e�̍s��
 */
void Bullet::Update(Matrix& matrix)
{
	//�e�s��̔��f
	_bullet->SetLocalWorld(matrix);

	//�����Ă����Ԃɂ���
	if (_isKeyDown)
	{
		ShootBullet(matrix);
	}

	//�����Ă����Ԃ�������
	if (_isStateShoot)
	{
		if (--_flagCount < 0.0f)
		{
			//����������x�Z�b�g����
			ResultBullet(matrix);
			//�����Ă��Ȃ���Ԃɖ߂�
			_isStateShoot = false;
		}
	}

	//���̈ړ����s��
	_Pos += _bulletVel;
	this->_bullet->SetTrans(_Pos);

	//�s��X�V
	_bullet->Calc(matrix);

	//�����蔻��̍X�V
	_collisionNode.Update();
}

/*
 *@Bullet�I�u�W�F�N�g�̕`�揈��
 */
void Bullet::Draw(shared_ptr<Camera> camera)
{
	//���̕`��
	this->_bullet->Draw(camera);

	//�����蔻��m�[�h�@
    _collisionNode.Draw();
}

/*
 *@Bullet�I�u�W�F�N�g�̌㏈��
 */
void Bullet::Finalize()
{

}

/*
 *@Bullet�I�u�W�F�N�g�𔭎˂���
 */
void Bullet::ShootBullet(Matrix& matrix)
{
	if (_isStateShoot) return;

	//���˂���e�ۂ̑��x�x�N�g��
	_bulletVel = Vector3(0.0f, 0.0f, 0.3f);
	//�x�N�g�����N�H�[�^�j�I���ŉ�]
	_bulletVel = Vector3::TransformNormal(_bulletVel, matrix);
	
	//�������˂���Ă��鎞��
	_flagCount = 60;

	//�����������ɂ���
	_isStateShoot = true;
}

/*
 *@�������������Ƃɖ߂�
 */
void Bullet::ResultBullet(Matrix& matrix)
{
	//���˒��łȂ�
	if (!_isStateShoot) return;

	//�ʒu�����Ƃɖ߂�
	_bullet->SetLocalWorld(matrix);
	//�N�H�[�^�j�I�����g�p���Ă��Ȃ���Ԃɖ߂�
	_bullet->SetUseQuternion(false);
	//���̑��x���O�ɂ���
	_bulletVel = Vector3(0.0f, 0.0f, 0.0f);
	//�ۑ�����Ă����ʒu������������
	_Pos = Vector3(0.0f, 0.0f, 0.0f);
	//���̈ʒu��������
	_bullet->SetTrans(Vector3(0.0f, 0.0f, 0.0f));

	//�����Ă��Ȃ���Ԃɂ���
	_isStateShoot = false;
}

/*
 *@�q�I�u�W�F�N�g��ǉ�����
 */
void Bullet::Add(shared_ptr<Tank> && pNode)
{
	_child.emplace_back(pNode);
	//�e�m�[�h��ݒ肷��
	pNode->Parent(shared_from_this());
}

/*
 * @�ċA�I�ɃI�u�W�F�N�g�𕡐�����
 */
shared_ptr<Tank> Bullet::Clone()
{
	//�I�u�W�F�N�g�̕��������
	auto pClone = make_shared<Bullet>();
	//���X�g���N���A����
	pClone->_child.clear();
	//���ׂẴ��X�g�̗v�f���Q�Ƃ���
	for (auto& child : _child)
	{
		//�������ꂽ�q�I�u�W�F�N�g�����X�g�ɒǉ�����
		pClone->Add(child->Clone());
	}
	return pClone;
}

