#include "BackScreen.h"
#include "../Graphics.h"

#include <SimpleMath.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
 *@�R���X�g���N�^
 */
BackScreen::BackScreen()
{
	//�w�i�̐���
	_back = make_shared<ObjectBase>();
	//�傫���̐ݒ�
	_back->SetScale(Vector3(3.0f, 3.0f, 3.0f));
}

/*
 *@�f�X�g���N�^
 */
BackScreen::~BackScreen()
{

}

/*
 *@����������
 */
void BackScreen::Initialize()
{
	//Graphics�N���X�̃C���X�^���X���擾����
	auto& graphics = Graphics::Get();
	//CommonStates�𐶐�����
	this->_commonState = make_unique<CommonStates>(graphics.Device().Get());
	//�G�t�F�N�g�t�@�N�g���̍쐬
	_factory = make_unique<EffectFactory>(graphics.Device().Get());
	//�e�N�X�`���̓ǂݍ��݃p�X���w�� �e�N�X�`��������t�@�C�����w��
	_factory->SetDirectory(L"Resources/cModels");
	//�t�@�C���̓ǂݍ���
	this->_back->LoadModelFile(L"Resources/cModels/back.cmo");
	//�w�i�̍��W��ݒ�
	_back->SetTrans(Vector3(0.0f, 0.0f, 0.0f));

}

/*
 *@�X�V����
 */
void BackScreen::Update()
{
	Matrix world = Matrix::Identity;
	//�s��X�V
	_back->Calc(world);
}

/*
 *@�`�揈��
 */
void BackScreen::Draw(shared_ptr<Camera> camera)
{
	//�w�i�̕`��
	_back->Draw(camera);
}

/*
 *@�I������
 */
void BackScreen::Finalize()
{

}