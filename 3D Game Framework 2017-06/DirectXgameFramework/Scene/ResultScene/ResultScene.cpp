#include "ResultScene.h"
#include "../SceneManager.h"
#include "../../Game.h"

using namespace std;

/*
 *@�R���X�g���N�^
 */
ResultScene::ResultScene(shared_ptr<SceneManager> scene) : SceneBase(scene)
{

}

/*
 *@�f�X�g���N�^
 */
ResultScene::~ResultScene()
{

}

/*
 *@����������
 */
void ResultScene::Initialize()
{

}

/*
 *@�X�V����
 */
void ResultScene::Update()
{
	if (Game::keyboard->GetState().IsKeyDown(DirectX::Keyboard::Keys::Space))
	{
		m_SceneChanger._Get()->ChangeScene(SCENE_TITLE);
	}
}

/*
 *@�`�揈��
 */
void ResultScene::Draw()
{

}

/*
 *@�I������
 */
void ResultScene::Finalize()
{

}
