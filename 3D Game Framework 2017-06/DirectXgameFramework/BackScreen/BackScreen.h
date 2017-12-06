#pragma once

#include <memory>

#include "../Base/ObjectBase.h"

class Camera;

class BackScreen
{
public:
	//コンストラクタ
	BackScreen();
	//デストラクタ
	~BackScreen();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw(std::shared_ptr<Camera> camera);
	//終了処理
	void Finalize();
private:
	//背景
	std::shared_ptr<ObjectBase> _back;
	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> _commonState;
};
