#include "TitleScene.h"
#include "../SceneManager.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../Game.h"
#include "../../Tool/DirectXTK.h"
#include "../../Graphics.h"

#include <WICTextureLoader.h>

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

TitleScene::TitleScene(std::shared_ptr<SceneManager> scene) : SceneBase(scene), _texture(nullptr)
{
	_titleTexture = make_shared<ObjectBase>();
	//�J�����̐���
	_camera = make_shared<Camera>();
}

TitleScene::~TitleScene()
{

}

/*
 *@����������
 */
void TitleScene::Initialize()
{
	//�O���t�B�b�N�X�̃C���X�^���X���擾����
	auto& graphics = Graphics::Get();
	//commonStates�𐶐�����
	_commonStates = make_unique<CommonStates>(graphics.Device().Get());
	//�G�t�F�N�g�t�@�N�g���̍쐬
	this->_factory = make_unique<EffectFactory>(graphics.Device().Get());
	//�e�N�X�`���̓ǂݍ��݃p�X���w��
	_factory->SetDirectory(L"Resources/cModels");
	//title��ǂݍ���
	this->_titleTexture->LoadModelFile(L"Resources/cModels/title.cmo");
	
	this->_titleTexture->SetScale(Vector3(0.2f, 0.2f, 0.2f));

	_camera->SetEyepos(Vector3(0.0f, 100.0f, 1.0f));
	//_camera->SetRefpos(Vector3(0.0f, 1.0f, 0.0f));
}

/*
 *@�X�V����
 */
void TitleScene::Update()
{
	Matrix world = Matrix::Identity;
	//�X�y�[�X�L�[�������ꂽ��
	if (Game::keyboard->GetState().IsKeyDown(DirectX::Keyboard::Keys::Space))
	{
		if(!Game::keyboard->GetState().IsKeyUp(DirectX::Keyboard::Keys::Space))
		{
			//�v���C�V�[���Ɉڍs����
			m_SceneChanger._Get()->ChangeScene(SCENE_PLAY);
		}
	}
	
	//���C�e�B���O�̖���
	_titleTexture->DisableLighting();
	
	_titleTexture->Calc(world);

	_camera->Update();
}

/*
 *@�`�揈��
 */
void TitleScene::Draw()
{
	_titleTexture->Draw(_camera);
}

/*
 *@�I������
 */
void TitleScene::Finalize()
{

}
