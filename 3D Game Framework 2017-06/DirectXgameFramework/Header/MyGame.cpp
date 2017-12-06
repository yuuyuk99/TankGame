#include "MyGame.h"

using namespace Microsoft;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;
using namespace DX;

// コンストラクタ Constructor
MyGame::MyGame(int width, int height) : Game(width, height) {
	this->scale = 1.0f;
}

// MyGameオブジェクトを初期する Initialize MyGame object
void MyGame::Initialize(int width, int height) {
	// 基本クラスのInitializeを呼び出す 
	Game::Initialize(width, height);

	//シーンを呼び出す
	sceneManager = make_shared<SceneManager>(SCENE_TITLE);

	//現在のシーンを入れる
	sceneManager->SetManager(sceneManager);
	//シーンの実行
	sceneManager->Reset();

	// Graphicsクラスのインスタンスを取得する
	auto& graphics = Graphics::Get();
	//シーンの初期化
	sceneManager->Initiaize();
}

// ゲームを更新する Update game
void MyGame::Update(const DX::StepTimer& timer) {
	float elapsedTime = float(timer.GetElapsedSeconds());

	//シーンの更新
	sceneManager->Update();
}

// シーンを描画する Draws the scene
void MyGame::Render(const DX::StepTimer& timer) {
	// 最初の更新の前は何も描画しないようにする Don't try to render anything before the first Update.
	if (timer.GetFrameCount() == 0) {
		return;
	}

	Clear();
	
	// TODO: レンダリングコードを追加する Add your rendering code here
	// Graphicsクラスのインスタンスを取得する
	auto& graphics = Graphics::Get();

	this->spriteBatch->Begin(SpriteSortMode_Deferred, commonStates->NonPremultiplied());

	//シーンの描画
	sceneManager->Draw();
	
	// FPSを描画する
	//DrawFPS();
	// ワールド行列を初期化する
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	// スケールを変更する Change scale 
	world = SimpleMath::Matrix::CreateScale(scale);

	this->spriteBatch->End();
	
	Present();
}

// 終了処理をおこなう Finalize Game
void MyGame::Finalize() {

	//シーンの後処理
	sceneManager->Finalize();

	// 基本クラスのFinalizeを呼び出す
	Game::Finalize();
}
