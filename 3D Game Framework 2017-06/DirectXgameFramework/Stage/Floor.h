#pragma once
#include "Stage.h"

class Floor{
public:
	//コンストラクタ
	Floor();
	//デストラクタ
	~Floor();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw(std::shared_ptr<Camera> camera);
	//終了処理
	void Finalize();
private:
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//床
	std::shared_ptr<ObjectBase> _floor;
	//球の当たり判定
	SphereNode _collisionNode;
};