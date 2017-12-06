#include "MyGame.h"

using namespace Microsoft;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;
using namespace DX;

// �R���X�g���N�^ Constructor
MyGame::MyGame(int width, int height) : Game(width, height) {
	this->scale = 1.0f;
}

// MyGame�I�u�W�F�N�g���������� Initialize MyGame object
void MyGame::Initialize(int width, int height) {
	// ��{�N���X��Initialize���Ăяo�� 
	Game::Initialize(width, height);

	//�V�[�����Ăяo��
	sceneManager = make_shared<SceneManager>(SCENE_TITLE);

	//���݂̃V�[��������
	sceneManager->SetManager(sceneManager);
	//�V�[���̎��s
	sceneManager->Reset();

	// Graphics�N���X�̃C���X�^���X���擾����
	auto& graphics = Graphics::Get();
	//�V�[���̏�����
	sceneManager->Initiaize();
}

// �Q�[�����X�V���� Update game
void MyGame::Update(const DX::StepTimer& timer) {
	float elapsedTime = float(timer.GetElapsedSeconds());

	//�V�[���̍X�V
	sceneManager->Update();
}

// �V�[����`�悷�� Draws the scene
void MyGame::Render(const DX::StepTimer& timer) {
	// �ŏ��̍X�V�̑O�͉����`�悵�Ȃ��悤�ɂ��� Don't try to render anything before the first Update.
	if (timer.GetFrameCount() == 0) {
		return;
	}

	Clear();
	
	// TODO: �����_�����O�R�[�h��ǉ����� Add your rendering code here
	// Graphics�N���X�̃C���X�^���X���擾����
	auto& graphics = Graphics::Get();

	this->spriteBatch->Begin(SpriteSortMode_Deferred, commonStates->NonPremultiplied());

	//�V�[���̕`��
	sceneManager->Draw();
	
	// FPS��`�悷��
	//DrawFPS();
	// ���[���h�s�������������
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	// �X�P�[����ύX���� Change scale 
	world = SimpleMath::Matrix::CreateScale(scale);

	this->spriteBatch->End();
	
	Present();
}

// �I�������������Ȃ� Finalize Game
void MyGame::Finalize() {

	//�V�[���̌㏈��
	sceneManager->Finalize();

	// ��{�N���X��Finalize���Ăяo��
	Game::Finalize();
}
