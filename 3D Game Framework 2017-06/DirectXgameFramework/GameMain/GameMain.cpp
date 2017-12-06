#include "GameMain.h"

using namespace Microsoft;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/*
 *@�R���X�g���N�^
 */
GameMain::GameMain(int width, int height) : Game(width, height)
{

}

/*
 *@Game�I�u�W�F�N�g������������
 */
void GameMain::Initialize()
{
	//��{�N���X��Initialize���Ăяo��
	Game::Initialize();

	sceneManager = make_unique<SceneManager>(SCENE_PLAY);
}

/*
 *@�Q�[�����X�V����
 */
void GameMain::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	sceneManager->Update();

}

void GameMain::Draw(DX::StepTimer const& timer)
{
	//�ŏ��̍X�V�̑O�͉����`�悵�Ȃ��悤�ɂ���
	if (timer.GetFrameCount() == 0) return;

	//�����_�����O�R�[�h��ǉ�����

	//��ʂ��N���A����
	Clear();
	//�`����n�߂�
	spriteBatch->Begin();

	sceneManager->Draw();

	//�`����I����
	spriteBatch->End();
	//�o�b�N�o�b�t�@���X�N���[���ɑ���
	Present();
}

/*
 *@�I���������s��
 */
void GameMain::Finalize()
{
	sceneManager->Finalize();

	//��{�N���X��Finalize���Ăяo��
	Game::Finalize();

}
