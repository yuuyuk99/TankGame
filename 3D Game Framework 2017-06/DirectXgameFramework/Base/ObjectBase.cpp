#include "ObjectBase.h"
#include "../Camera/Camera.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <CommonStates.h>
#include "../Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

//静的メンバ変数の実態
shared_ptr<EffectFactory> ObjectBase::s_pEffectFactory;
map<wstring, shared_ptr<Model>> ObjectBase::s_modellarray;
shared_ptr<Camera> ObjectBase::s_pCamera;

/*
 *@コンストラクタ
 */
ObjectBase::ObjectBase() : _pParentMatrix(nullptr), _model(nullptr)
{
	//スケールは1倍がデフォルト
	_Scale = Vector3(1.0f, 1.0f, 1.0f);
	//モデルを取得する
	this->_model = make_shared<Model>();

	_UseQuternion = false;
}

/*
 *@デストラクタ
 */
ObjectBase::~ObjectBase()
{

}

/*
 *@ファイルからモデルを読み込む
 */
void ObjectBase::LoadModelFile(const wchar_t* filename)
{
	//グラフィックスを受け取る
	auto& graphics = Graphics::Get();

	//コモンステートを取得
	this->_commonState = make_unique<CommonStates>(graphics.Device().Get());
	//エフェクトファクトリの取得
	this->_factory = make_unique<EffectFactory>(graphics.Device().Get());

	//同じ名前のモデルを読み込み済みでなければ
	if (s_modellarray.count(filename) == 0)
	{
		//モデルを読み込み,コンテナに登録(キーはファイル名)
		s_modellarray[filename] = Model::CreateFromCMO(graphics.Device().Get(), filename, *this->_factory);
	}

	_model = s_modellarray[filename];

}

/*
 *@オブジェクトのライティングを無効にする
 */
void ObjectBase::DisableLighting()
{
	if (!_model)
	{
		return;
	}

	//モデル内のメッシュ分回す
	ModelMesh::Collection::const_iterator it_mesh = _model->meshes.begin();
	for (; it_mesh != _model->meshes.end(); it_mesh++)
	{
		ModelMesh* modelmesh = it_mesh->get();
		assert(modelmesh);

		//メッシュ内の全パーツ分回す
		vector<unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
		for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
		{
			ModelMeshPart* meshpart = it_meshpart->get();
			assert(meshpart);

			//メッシュパーツにセットされたエフェクトをBasicEffectとして取得
			BasicEffect* eff = static_cast<BasicEffect*>(meshpart->effect.get());
			if (!eff)
			{
				return;
			}
			XMVECTOR emissive;
			emissive.m128_f32[0] = 1.0f;
			emissive.m128_f32[1] = 1.0f;
			emissive.m128_f32[2] = 1.0f;
			emissive.m128_f32[3] = 1.0f;
			eff->SetEmissiveColor(emissive);
			for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
			{
				//ライトを無効にする
				eff->SetLightEnabled(i, false);
			}
		}
	}
}

/*
 *@行列更新を行う
 */
void ObjectBase::Calc(Matrix& matrix)
{
	//スケール
	Matrix scalem;
	//回転
	Matrix rotm;
	//座標
	Matrix transm;

	//スケール
	scalem = Matrix::CreateScale(_Scale);

	if (_UseQuternion)
	{
		//クォータニオンから回転行列を計算
		rotm = Matrix::CreateFromQuaternion(_RotQ);
	}
	else
	{
		//オイラ一角から回転行列を計算
		rotm = Matrix::CreateFromYawPitchRoll(_Rot.y, _Rot.x, _Rot.z);
	}

	//座標
	transm = Matrix::CreateTranslation(_Trans);

	//ワールド行列をSRTに合成
	_LocalWorld = Matrix::Identity;
	_LocalWorld *= scalem;
	_LocalWorld *= matrix;
	_LocalWorld *= rotm;
	_LocalWorld *= transm;


	//親行列があれば
	if (_pParentMatrix)
	{
		//親行列を掛ける
		_LocalWorld = _LocalWorld * (*_pParentMatrix);
	}
}

/*
 *@描画処理を行う
 */
void ObjectBase::Draw(shared_ptr<Camera> camera, Vector3 scale, ID3D11PixelShader* ps)
{
	//グラフィックスのインスタンス
	auto& graphics = Graphics::Get();
	//カメラのビュー行列を受け取ってview行列に代入する
	Matrix view = camera->GetViewmat();
	//カメラのプロジェクション行列を受け取ってproj行列に代入
	Matrix proj = camera->GetProjmat();

	// モデルの描画
	_model->Draw(Graphics::Get().Context().Get(), *this->_commonState, _LocalWorld, view, proj);

}
