#include "ResultScene.h"
#include "../SceneManager.h"
#include "../../Game.h"

using namespace std;

/*
 *@コンストラクタ
 */
ResultScene::ResultScene(shared_ptr<SceneManager> scene) : SceneBase(scene)
{

}

/*
 *@デストラクタ
 */
ResultScene::~ResultScene()
{

}

/*
 *@初期化処理
 */
void ResultScene::Initialize()
{

}

/*
 *@更新処理
 */
void ResultScene::Update()
{
	if (Game::keyboard->GetState().IsKeyDown(DirectX::Keyboard::Keys::Space))
	{
		m_SceneChanger._Get()->ChangeScene(SCENE_TITLE);
	}
}

/*
 *@描画処理
 */
void ResultScene::Draw()
{

}

/*
 *@終了処理
 */
void ResultScene::Finalize()
{

}
