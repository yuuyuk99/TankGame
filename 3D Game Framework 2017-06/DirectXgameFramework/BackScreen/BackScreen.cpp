#include "BackScreen.h"
#include "../Graphics.h"

#include <SimpleMath.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*
 *@コンストラクタ
 */
BackScreen::BackScreen()
{
	//背景の生成
	_back = make_shared<ObjectBase>();
	//大きさの設定
	_back->SetScale(Vector3(3.0f, 3.0f, 3.0f));
}

/*
 *@デストラクタ
 */
BackScreen::~BackScreen()
{

}

/*
 *@初期化処理
 */
void BackScreen::Initialize()
{
	//Graphicsクラスのインスタンスを取得する
	auto& graphics = Graphics::Get();
	//CommonStatesを生成する
	this->_commonState = make_unique<CommonStates>(graphics.Device().Get());
	//エフェクトファクトリの作成
	_factory = make_unique<EffectFactory>(graphics.Device().Get());
	//テクスチャの読み込みパスを指定 テクスチャがあるファイルを指定
	_factory->SetDirectory(L"Resources/cModels");
	//ファイルの読み込み
	this->_back->LoadModelFile(L"Resources/cModels/back.cmo");
	//背景の座標を設定
	_back->SetTrans(Vector3(0.0f, 0.0f, 0.0f));

}

/*
 *@更新処理
 */
void BackScreen::Update()
{
	Matrix world = Matrix::Identity;
	//行列更新
	_back->Calc(world);
}

/*
 *@描画処理
 */
void BackScreen::Draw(shared_ptr<Camera> camera)
{
	//背景の描画
	_back->Draw(camera);
}

/*
 *@終了処理
 */
void BackScreen::Finalize()
{

}