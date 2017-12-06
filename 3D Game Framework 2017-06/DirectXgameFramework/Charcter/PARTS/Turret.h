#pragma once

#include "../Tank.h"
#include <CommonStates.h>

class Turret : public Tank, public std::enable_shared_from_this<Turret>
{
public:
	//コンストラクタ
	Turret();
	//Bodyオブジェクトを初期化する
	void Initialize() override;
	//Bodyオブジェクトを更新
	void Update(DirectX::SimpleMath::Matrix& matrix) override;
	//Bodyオブジェクトを描画
	void Draw(std::shared_ptr<Camera> camera) override;
	//Bodyオブジェクトの後処理を行う
	void Finalize() override;
	//親オブジェクトを設定する
	void Add(std::shared_ptr<Tank>&& pNode) override;
	//再帰的にオブジェクトを複製する
	std::shared_ptr<Tank> Clone() override;
protected:
	//ポインタの格納
	std::vector<std::shared_ptr<Tank>> _child;
	//CommonState
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//モデル
	std::unique_ptr<DirectX::Model> _model;
	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//スケール
	DirectX::SimpleMath::Vector3 _scale;
};