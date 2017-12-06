#include "Tower.h"
#include "../Graphics.h"
#include <Effects.h>
#include <CommonStates.h>
#include "../Camera/Camera.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

/*
 *@�R���X�g���N�^
 */
Tower::Tower()
{
	//�^���[�̐���
	this->_Tower = std::make_shared<ObjectBase>();

	this->_health = 10;
}

/*
 *@Tower�I�u�W�F�N�g�̏���������
 */
void Tower::Initialize()
{
	//Graphics�N���X�̃C���X�^���X���擾����
	auto& graphics = Graphics::Get();
	//CommonStates�𐶐�����
	this->_commonState = make_unique<CommonStates>(graphics.Device().Get());
	//�G�t�F�N�g�t�@�N�g���̍쐬
	_factory = make_unique<EffectFactory>(graphics.Device().Get());
	//�e�N�X�`���̓ǂݍ��݃p�X���w�� �e�N�X�`��������t�@�C�����w��
	_factory->SetDirectory(L"Resources/cModels");
	//�^���[�̃��f����ǂݍ���
	this->_Tower->LoadModelFile(L"Resources/cModels/cTower.cmo");

	//�����蔻��̐ݒ�
	_collisionNode.Initialize();
	//�����蔻��̃��[���h���W��ݒ�
	_collisionNode.SetParentMatrix(&this->_Tower->GetLocalWorld());
	//�����蔻��̑傫����ݒ�
	_collisionNode.SetLocalRadius(1.0f);
	//�����蔻�肪�e����ǂꂾ������Ă��邩
	_collisionNode.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
}

/*
 *@Tower�I�u�W�F�N�g�̍X�V����
 */
void Tower::Update()
{
	//���[���h���W
	Matrix world = Matrix::Identity;
	//�s��X�V
	this->_Tower->Calc(world);
	//�����蔻��̍X�V
	this->_collisionNode.Update();
}

/*
 *@Tower�I�u�W�F�N�g�̕`�揈��
 */
void Tower::Draw(shared_ptr<Camera> camera)
{
	//�^���[�̕`��
	this->_Tower->Draw(camera);
	//�����蔻��̕`��
	this->_collisionNode.Draw();
}

/*
 *@Tower�I�u�W�F�N�g�̌㏈��
 */
void Tower::Finalize()
{

}

