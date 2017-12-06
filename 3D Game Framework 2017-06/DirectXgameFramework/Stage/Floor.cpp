#include "Floor.h"
#include "../Graphics.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

Floor::Floor()
{
	_floor = make_shared<ObjectBase>();
}

Floor::~Floor()
{

}

/*
 *@������
 */
void Floor::Initialize()
{
	//�n�ʂ̃��f����ǂݍ���
	this->_floor->LoadModelFile(L"Resources/cModels/floor.cmo");

	this->_floor->SetScale(Vector3(2.5f, 1.0f, 6.0f));
	this->_floor->SetTrans(Vector3(6.0f, 0.0f, 10.0f));

	//�����蔻��̏�����
	_collisionNode.Initialize();
	//�����蔻��̃��[���h���W��ݒ�
	_collisionNode.SetParentMatrix(&this->_floor->GetLocalWorld());
	//�����蔻��̑傫����ݒ�
	_collisionNode.SetLocalradius(1.0f);
	//�����蔻�肪�e����ǂꂾ������Ă��邩
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
}

/*
 *@�X�V����
 */
void Floor::Update() 
{
	//���[���h�s��
	Matrix world = Matrix::Identity;
	//�s��X�V
	_floor->Calc(world);
	//�����蔻��̍X�V
	_collisionNode.Update();
}

/*
 *@�`�揈��
 */
void Floor::Draw(std::shared_ptr<Camera> camera)
{
	//Floor�̕`����s��
	_floor->Draw(camera);
}

void Floor::Finalize()
{

}
