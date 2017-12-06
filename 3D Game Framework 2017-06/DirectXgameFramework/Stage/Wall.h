#pragma once
#include <CommonStates.h>
#include <Effects.h>
#include <memory>
#include "../Camera/Camera.h"
#include "../Collision/CollisionNode.h"

class Wall
{
public:
	//コンストラクタ
	Wall();
	//デストラクタ
	~Wall();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw(std::shared_ptr<Camera> camera);
	//終了処理
	void Finalize();
	//当たり判定
	SphereNode& GetCollisionNode() { return _collisionNode; }
	//位置を指定する
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _wall->SetTrans(trans); }
	//現在位置を受け渡す
	DirectX::SimpleMath::Vector3& GetTrans() { return _wall->GetTrans(); }
private:
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//壁
	std::shared_ptr<ObjectBase> _wall;
	//球の当たり判定
	SphereNode _collisionNode;
};