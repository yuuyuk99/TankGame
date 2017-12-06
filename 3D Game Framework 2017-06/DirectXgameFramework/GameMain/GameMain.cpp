#include "GameMain.h"

using namespace Microsoft;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/*
 *@コンストラクタ
 */
GameMain::GameMain(int width, int height) : Game(width, height)
{

}

/*
 *@Gameオブジェクトを初期化する
 */
void GameMain::Initialize()
{
	//基本クラスのInitializeを呼び出す
	Game::Initialize();

	sceneManager = make_unique<SceneManager>(SCENE_PLAY);
}

/*
 *@ゲームを更新する
 */
void GameMain::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	sceneManager->Update();

}

void GameMain::Draw(DX::StepTimer const& timer)
{
	//最初の更新の前は何も描画しないようにする
	if (timer.GetFrameCount() == 0) return;

	//レンダリングコードを追加する

	//画面をクリアする
	Clear();
	//描画を始める
	spriteBatch->Begin();

	sceneManager->Draw();

	//描画を終える
	spriteBatch->End();
	//バックバッファをスクリーンに送る
	Present();
}

/*
 *@終了処理を行う
 */
void GameMain::Finalize()
{
	sceneManager->Finalize();

	//基本クラスのFinalizeを呼び出す
	Game::Finalize();

}
