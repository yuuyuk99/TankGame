#include "Enemy.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "../PARTS/Body.h"
#include "../PARTS/Turret.h"
#include "../PARTS/Bullet.h"
#include "../../Game.h"
#include "Move.h"
#include "AIState.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
 *@�R���X�g���N�^
 */
Enemy::Enemy()
{
	_currentState = make_shared<AIState>();
}

/*
 *@Enemy�I�u�W�F�N�g�̏�����
 */
void Enemy::Initialize()
{
	//Body�I�u�W�F�N�g�𐶐�����
	this->_body = make_shared<Body>();
	//Body�I�u�W�F�N�g������������
	this->_body->Initialize();
	//Turret�I�u�W�F�N�g�𐶐�����
	this->_turret = make_shared<Turret>();
	//Turret�I�u�W�F�N�g������������
	this->_turret->Initialize();
	//Body�I�u�W�F�N�g��Turret�I�u�W�F�N�g��ǉ�����
	this->_body->Add(move(this->_turret));
	//bullet�I�u�W�F�N�g��ǉ�����
	this->_bullet = make_shared<Bullet>();
	//bullet�I�u�W�F�N�g������������
	this->_bullet->Initialize();
	//turret�I�u�W�F�N�g��bullet�I�u�W�F�N�g��ǉ�����
	this->_turret->Add(move(this->_bullet));

	this->_body->SetTrans(Vector3(7.5f, 0.0f, 15.0f));

	ChangeState(Move::GetInstance());
	

}

/*
 *@Enemy�I�u�W�F�N�g�̍X�V
 */
void Enemy::Update()
{
	//���݂̏�Ԃ����s����
 	_currentState->Execute(this);

	//Tank�I�u�W�F�N�g���X�V����
	this->_body->Update(this->_body->GetLocalWorld());
}

/*
 *@��Ԃ̕ύX
 */
void Enemy::ChangeState(shared_ptr<AIState> currentState)
{
	this->_currentState = currentState;
}

/*
 *@Enemy�I�u�W�F�N�g�̕`��
 */
void Enemy::Draw(shared_ptr<Camera> camera)
{
	//tank�I�u�W�F�N�g��`�悷��
	this->_body->Draw(camera);
}

/*
 *@Enemy�I�u�W�F�N�g�̌㏈��
 */
void Enemy::Finalize()
{

}