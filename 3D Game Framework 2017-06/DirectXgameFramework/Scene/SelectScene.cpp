#include "SelectScene.h"
#include "SceneManager.h"


SelectScene::SelectScene(std::shared_ptr<SceneManager> scene) : SceneBase(scene)
{
}


SelectScene::~SelectScene()
{
}


void SelectScene::Initialize()
{

}

void SelectScene::Update()
{
	//if (s_keyTracker->pressed.Space)
	//{
	//	//ゲームプレイシーン
	//	m_SceneChanger->ChangeScene(SCENE_PLAY);
	//}
}

void SelectScene::Draw()
{

}

void SelectScene::Finalize()
{

}

