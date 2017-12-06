#include "Player.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "../PARTS/Body.h"
#include "../PARTS/Turret.h"
#include "../PARTS/Bullet.h"
#include "../../Game.h"
#include "../../Camera/Camera.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
 *@�R���X�g���N�^
 */
Player::Player()
{
	
}

/*
 *@�f�X�g���N�^
 */
Player::~Player()
{

}

/*
 *@Player�̏���������
 */
void Player::Initialize()
{
	//Body�I�u�W�F�N�g�𐶐�����
	this->_body = make_shared<Body>();
	//Body�I�u�W�F�N�g�̏�����
	this->_body->Initialize();
	//Turret�I�u�W�F�N�g�𐶐�����
	this->_turret = make_shared<Turret>();
	//Turret�I�u�W�F�N�g�̏�����
	this->_turret->Initialize();
	//Body�I�u�W�F�N�g��Turret�I�u�W�F�N�g��ǉ�����
	this->_body->Add(move(this->_turret));
	//bullet�I�u�W�F�N�g�̐���
	this->_bullet = make_shared<Bullet>();
	//bullet�I�u�W�F�N�g�̏�����
	this->_bullet->Initialize();
	//turret�I�u�W�F�N�g��bullet�I�u�W�F�N�g��ǉ�����
	this->_turret->Add(move(this->_bullet));

	//���@�̏����ʒu��ύX
	this->_body->SetTrans(Vector3(7.5f, 0.0f, 10.0f));
}

/*
 *@Player�̍X�V����
 */
void Player::Update()
{
	//Body�I�u�W�F�N�g�̑��x������������
	this->_body->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));

	//�I�u�W�F�N�g���E�ɉ�]����
	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::A))
	{
		//��]����
		Vector3 rot = _body->GetRot();
		//��]�����l������
		rot += Vector3(0.0f, XMConvertToRadians(1.0f), 0.0f);
		//body�ɉ�]�������l������
		_body->SetRot(rot);
	}
	//�I�u�W�F�N�g�����ɉ�]����
	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::D))
	{
		//��]
		Vector3 rot = _body->GetRot();
		//��]
		rot += Vector3(0.0f, -XMConvertToRadians(1.0f), 0.0f);
		//body�ɉ�]�������l������
		_body->SetRot(rot);
	}
	//�O�i
	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::W))
	{

		//���݂̍��W��]�p���擾
		Vector3 trans = _body->GetTrans();
		float rot_y = _body->GetRot().y;
		//�ړ��x�N�g��
		Vector3 move(0.0f, 0.0f, 0.1f);
		Matrix rotm = Matrix::CreateRotationY(rot_y);
		//�ړ��x�N�g������]����
		move = Vector3::TransformNormal(move, rotm);
		//�ړ�����
		trans += move;
		//�ړ����s��
		_body->SetTrans(trans);
	}
	//��i
	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::S))
	{
		//���݂̍��W��]�p���擾
		Vector3 trans = _body->GetTrans();
		float rot_y = _body->GetRot().y;
		//�ړ��x�N�g��
		Vector3 move(0.0f, 0.0f, -0.1f);
		Matrix rotm = Matrix::CreateRotationY(rot_y);
		//�ړ��x�N�g������]����
		move = Vector3::TransformNormal(move, rotm);
		//�ړ�����
		trans += move;
		//�ړ����s��
		_body->SetTrans(trans);
	}

	if (Game::keyboard->GetState().IsKeyDown(Keyboard::Keys::R))
	{
		//�{�^����������Ă����Ԃɂ���
		this->_bullet->SetKeyDown(true);
		//���𔭎˂���
		this->_bullet->Update(this->_body->GetLocalWorld());
	}
	
	//�����{�^���������Ă��Ȃ���Ԃɂ���
	this->_bullet->SetKeyDown(false);

	//Tank�I�u�W�F�N�g���X�V����
	//�ċN�֐��Ȃ̂�body��child���Ă΂��
	this->_body->Update(this->_body->GetLocalWorld());

}

/*
 *@�v���C���[�̕`�揈��
 */
void Player::Draw(shared_ptr<Camera> camera)
{
	//Tank�I�u�W�F�N�g��`�悷��
	this->_body->Draw(camera);
}

/*
 *@�v���C���[�̌㏈��
 */
void Player::Finalize()
{
	//Tank�I�u�W�F�N�g�̏I���������s��
	this->_body->Finalize();
}

/*
*@�p�[�c���Ƃɓ����蔻����󂯓n��
*/
int Player::GetTank(int num)
{
	return num;
}