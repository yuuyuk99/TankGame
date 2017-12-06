#pragma once
#include <Model.h>
#include <Effects.h>
#include <map>
#include <d3d11.h>
#include <SimpleMath.h>
#include <memory>
#include <CommonStates.h>

class Camera;

//@ キャラクターたちの動きのベースになるところです
class ObjectBase
{
public:
	//エフェクトファクトリーのsetter
	static void SetEffectFactory(std::shared_ptr<DirectX::EffectFactory> pEffect) { s_pEffectFactory = pEffect; }
	//描画ステートのsetter
	static void SetStates(std::shared_ptr<DirectX::CommonStates> pStates) { s_pStates = pStates; }
	//カメラのsetter
	static void SetCamera(std::shared_ptr<Camera> pCamera) { s_pCamera = pCamera; }
private:
	//共通のエフェクトファクトリ
	static std::shared_ptr<DirectX::EffectFactory> s_pEffectFactory;
	//読み込み済みモデルコンテナ
	static std::map<std::wstring, std::shared_ptr<DirectX::Model>> s_modellarray;
	//描画ステートへのポインタ
	static std::shared_ptr<DirectX::CommonStates> ObjectBase::s_pStates;
	//共通のカメラ(描画時に使用)
	static std::shared_ptr<Camera> s_pCamera;
public:
	//コンテキスト
	ObjectBase();
	//デストラクタ
	~ObjectBase();
	//ファイルからモデルを読み込む
	void LoadModelFile(const wchar_t* filename = nullptr);
	//行列の計算
	void Calc(DirectX::SimpleMath::Matrix& matrix);
	//描画
	void Draw(std::shared_ptr<Camera> camera, DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f), ID3D11PixelShader* pl = nullptr);
	//オブジェクトのライティングを無効にする
	void DisableLighting();

	//アクセッサ
	//平行移動をさせる
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { _Trans = trans; }
	//回転を行う
	void SetRot(const DirectX::SimpleMath::Vector3& rot) { _Rot = rot; }
	//スケールの変更
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { _Scale = scale; }
	//ワールド行列の設定
	void SetLocalWorld(const DirectX::SimpleMath::Matrix& mat) { _LocalWorld = mat; }
	//親子関係を持たせる
	void SetParentMatrix(const DirectX::SimpleMath::Matrix* pParent) { _pParentMatrix = pParent; }
	//クォータニオンでの回転行列
	void SetRotQ(const DirectX::SimpleMath::Quaternion& rotQ) { _RotQ = rotQ; }
	//クォータニオンを使用する
	void SetUseQuternion(bool flag) { _UseQuternion = flag; }
	
	//現在の座標を受け流す
	DirectX::SimpleMath::Vector3& GetTrans() { return _Trans; }
	//現在の回転角度を受け流す
	DirectX::SimpleMath::Vector3& GetRot() { return _Rot; }
	//現在の拡大縮小を受け流す
	DirectX::SimpleMath::Vector3& GetScale() { return _Scale; }
	//現在のワールド行列を受け流す
	DirectX::SimpleMath::Matrix& GetLocalWorld() { return _LocalWorld; }

protected:
	//モデル
	std::shared_ptr<DirectX::Model> _model;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//平行移動
	DirectX::SimpleMath::Vector3 _Trans;
	//回転
	DirectX::SimpleMath::Vector3 _Rot;
	//スケーリング
	DirectX::SimpleMath::Vector3 _Scale;
	//ワールド行列
	DirectX::SimpleMath::Matrix _LocalWorld;
	//回転をクォータニオンで待つかどうか
	bool _UseQuternion;
	//クォータニオン
	DirectX::SimpleMath::Quaternion _RotQ;
	//親のワールド行列へのポインタ
	const DirectX::SimpleMath::Matrix* _pParentMatrix;
	//現在のカード情報
	bool _States;
};

