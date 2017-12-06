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
	//カメラの生成
	_camera = make_shared<Camera>();
}

TitleScene::~TitleScene()
{

}

/*
 *@初期化処理
 */
void TitleScene::Initialize()
{
	//グラフィックスのインスタンスを取得する
	auto& graphics = Graphics::Get();
	//commonStatesを生成する
	_commonStates = make_unique<CommonStates>(graphics.Device().Get());
	//エフェクトファクトリの作成
	this->_factory = make_unique<EffectFactory>(graphics.Device().Get());
	//テクスチャの読み込みパスを指定
	_factory->SetDirectory(L"Resources/cModels");
	//titleを読み込む
	this->_titleTexture->LoadModelFile(L"Resources/cModels/title.cmo");
	
	this->_titleTexture->SetScale(Vector3(0.2f, 0.2f, 0.2f));

	_camera->SetEyepos(Vector3(0.0f, 100.0f, 1.0f));
	//_camera->SetRefpos(Vector3(0.0f, 1.0f, 0.0f));
}

/*
 *@更新処理
 */
void TitleScene::Update()
{
	Matrix world = Matrix::Identity;
	//スペースキーが押されたら
	if (Game::keyboard->GetState().IsKeyDown(DirectX::Keyboard::Keys::Space))
	{
		if(!Game::keyboard->GetState().IsKeyUp(DirectX::Keyboard::Keys::Space))
		{
			//プレイシーンに移行する
			m_SceneChanger._Get()->ChangeScene(SCENE_PLAY);
		}
	}
	
	//ライティングの無効
	_titleTexture->DisableLighting();
	
	_titleTexture->Calc(world);

	_camera->Update();
}

/*
 *@描画処理
 */
void TitleScene::Draw()
{
	_titleTexture->Draw(_camera);
}

/*
 *@終了処理
 */
void TitleScene::Finalize()
{

}
