#pragma once
#include "../Tank.h"
#include "../../Collision/CollisionNode.h"
#include <CommonStates.h>
#include <Effects.h>

class Body : public Tank, public std::enable_shared_from_this<Body>
{
public:
	//コンストラクタ
	Body();
	//Bodyオブジェクトを初期化する
	void Initialize() override;
	//Bodyオブジェクトを更新
	void Update(DirectX::SimpleMath::Matrix& matrix) override;
	//Bodyオブジェクトを描画
	void Draw(std::shared_ptr<Camera> camera) override;
	//Bodyオブジェクトの後処理を行う
	void Finalize() override;
	//子オブジェクトを追加する
	void Add(std::shared_ptr<Tank>&& pNode) override;
	//当たり判定
	//inline std::shared_ptr<SphereNode> GetCollisionNode() override { return _collisionNode; }
	//球に当たったを受け渡す
	bool GetHit() { return _hit; }
	//球に当たったか
	void SetHit(bool hit) { _hit = hit; }
	//球に当たった時の判定
	void HitEffect();
	//再帰的にオブジェクトを複製する
	std::shared_ptr<Tank> Clone() override;
	//現在地を設定する
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _body->SetTrans(trans); }
	//現在値を受け渡す
	DirectX::SimpleMath::Vector3& GetTrans() { return _body->GetTrans(); }
private:
	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//当たっているかどうか
	bool _hit;
	//スケール
	DirectX::SimpleMath::Vector3 _scale;
	//ワールド行列
	DirectX::SimpleMath::Matrix _localWorld;
	//回転でクォータニオンを使用するか
	bool _useQuternion;
	//クォータニオン行列
	DirectX::SimpleMath::Quaternion _quternion;
	//ポインタの格納をする
	std::vector<std::shared_ptr<Tank>> _child;
};