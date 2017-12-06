#include "Body.h"
#include <Windows.h>
#include "../../Graphics.h"
#include "../../Game.h"
#include "../../Camera/Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;
//using Microsoft::WRL::ComPtr;

/*
 *@�R���X�g���N�^
 */
Body::Body()
{
	//�I�u�W�F�N�g
	_body = make_shared<ObjectBase>();
	//�������Ă��Ȃ���Ԃ���J�n����
	_hit = false;
	//�傫����ύX����
	_scale = Vector3(1.0f, 1.0f, 1.0f);
	//�L�[�{�[�h���擾����
	_keyboard = make_shared<Keyboard::State>();
	//�p�x�̐ݒ�
	_angle = 0.0f;
	//�ړ����x
	_Velocity = Vector3(0.0f, 0.0f, 0.0f);
}

/*
 *@Body�I�u�W�F�N�g������������
 */
void Body::Initialize()
{
	//body�̃��f����ǂݍ���
	this->_body->LoadModelFile(L"Resources/cModels/Body.cmo");

	//�����蔻��̏�����
	_collisionNode.Initialize();
	//�����蔻��̃��[���h���W��
	_collisionNode.SetParentMatrix(&this->_body->GetLocalWorld());
	//�����蔻��̑傫����ݒ�
	_collisionNode.SetLocalradius(1.0f);
	//�����蔻�肪�e����ǂꂾ������Ă��邩
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));


}

/*
 *@Body�I�u�W�F�N�g���X�V����
 */
void Body::Update(Matrix& matrix)
{
	//�e�̍s����󂯎��
	_body->SetLocalWorld(matrix);
	//�s��X�V
	_body->Calc(matrix);
	//�q���̍X�V�������Ăяo��
	for (auto child : _child)
	{
		child->Update(_body->GetLocalWorld());
	}
	
	//�����蔻��̍X�V
	_collisionNode.Update();
}


/*
 *@Body�I�u�W�F�N�g�̕`����s��
 */
void Body::Draw(shared_ptr<Camera> camera)
{
	//body�̕`����s��
	this->_body->Draw(camera);
	//�q���̕`�揈�����Ăяo��
	for (auto child : _child)
	{
		child->Draw(camera);
	}
	//�����蔻��̕`��
	_collisionNode.Draw();
}

/*
 *@Body�I�u�W�F�N�g�̌㏈�����s��
 */
void Body::Finalize()
{
	
}

/*
 *@���ɏՓ˂������̏���
 */
void Body::HitEffect()
{
	static float time = 0.0f;
	//
	if (_hit)
	{
		//�����Ȃ��悤�ɂ���
		_body->SetTrans(_body->GetTrans());
		time++;
	}
	//��莞�Ԃ�������
	if (time > 60)
	{
		_hit = false;
		time = 0.0f;
	}
}

/*
 *@�q�I�u�W�F�N�g��ǉ�����
 */
void Body::Add(shared_ptr<Tank>&& pNode)
{
	//Node,Leaf�I�u�W�F�N�g�̃|�C���^��ǉ�����
	_child.emplace_back(pNode);
	//�e�m�[�h��ݒ肷��
	pNode->Parent(shared_from_this());
}

/*
 *@�ċN�I�ɃI�u�W�F�N�g�𕡐�����
 */
shared_ptr<Tank> Body::Clone()
{
	//�I�u�W�F�N�g�̕��������
	auto pClone = make_shared<Body>();
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
