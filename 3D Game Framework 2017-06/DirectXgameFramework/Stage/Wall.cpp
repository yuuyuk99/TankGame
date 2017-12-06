#include "Wall.h"
#include <SimpleMath.h>
#include "../Graphics.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

Wall::Wall()
{
	//�ǂ𐶐�����
	_wall = make_shared<ObjectBase>();
}

Wall::~Wall()
{

}

/*
 *@����������
 */
void Wall::Initialize()
{
	//�ǂ̃��f����ǂݍ���
	this->_wall->LoadModelFile(L"Resources/cModels/box.cmo");

	//�����蔻��̏�����
	_collisionNode.Initialize();
	//�����蔻��̃��[���h���W��ݒ�
	_collisionNode.SetParentMatrix(&this->_wall->GetLocalWorld());
	//�����蔻��̑傫����ݒ�
	_collisionNode.SetLocalradius(0.1f);
	//�����蔻�肪�e����ǂꂾ������Ă��邩
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
}

/*
 *@�X�V����
 */
void Wall::Update()
{
	//���[���h���W
	Matrix world = Matrix::Identity;
	//�s��X�V
	_wall->Calc(world);
	//�����蔻��̍X�V
	_collisionNode.Update();
}

/*
 *@�`�揈��
 */
void Wall::Draw(std::shared_ptr<Camera> camera)
{
	//�ǂ̕`����s��
	_wall->Draw(camera);
}

/*
 *@�I������
 */
void Wall::Finalize()
{

}
