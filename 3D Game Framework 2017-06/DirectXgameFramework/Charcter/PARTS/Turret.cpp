#include "Turret.h"
#include <Windows.h>
#include "../../Graphics.h"
#include "../../Camera/Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/*
*@�R���X�g���N�^
*/
Turret::Turret()
{
	//turret�I�u�W�F�N�g�𐶐�
	_turret = make_shared<ObjectBase>();
	//turret�̑傫���̐ݒ�
	_scale = Vector3(0.5f, 0.5f, 0.5f);
}

/*
*@Turret�I�u�W�F�N�g������������
*/
void Turret::Initialize()
{
	//turret�̃��f����ǂݍ���
	this->_turret->LoadModelFile(L"Resources/cModels/turret.cmo");
	//�傫����ݒ�
	_turret->SetScale(_scale);
}

/*
*@Turret�I�u�W�F�N�g���X�V����
*/
void Turret::Update(Matrix& matrix)
{
	//�e�̍s��𔽉f
	_turret->SetLocalWorld(matrix);

	//�e�I�u�W�F�N�g����turret�̈ړ�
	_turret->SetTrans(Vector3(0.0f, 0.5f, 0.0f));

	//turret�̍s��X�V
	_turret->Calc(matrix);

	//turret��child�̍X�V
	for (auto child : _child)
	{
		child->Update(_turret->GetLocalWorld());
	}
}


/*
*@Turret�I�u�W�F�N�g�̕`����s��
*/
void Turret::Draw(shared_ptr<Camera> camera)
{
	//turret�̕`��
	_turret->Draw(camera);

	//turret��child�̕`��
	for (auto child : _child)
	{
		child->Draw(camera);
	}
}

/*
*@Turret�I�u�W�F�N�g�̌㏈�����s��
*/
void Turret::Finalize()
{

}

/*
 *@�q�I�u�W�F�N�g��ǉ�����
 */
void Turret::Add(shared_ptr<Tank>&& pNode)
{
	_child.emplace_back(pNode);
	//�e�m�[�h��ݒ肷��
	pNode->Parent(shared_from_this());
}

/*
 * @�ċA�I�ɃI�u�W�F�N�g�𕡐�����
 */
shared_ptr<Tank> Turret::Clone()
{
	//�I�u�W�F�N�g�̕���������
	auto pClone = make_shared<Turret>();
	//���X�g���N���A����
	pClone->_child.clear();
	for (auto& child : _child)
	{
		//�������ꂽ�q�I�u�W�F�N�g�����X�g�ɒǉ�����
		pClone->Add(child->Clone());
	}
	return pClone;
}