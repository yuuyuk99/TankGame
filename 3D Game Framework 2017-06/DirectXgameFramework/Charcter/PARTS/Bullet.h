#pragma once
#include "../Tank.h"
#include "Turret.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../Collision/CollisionNode.h"

class Bullet : public Tank, public std::enable_shared_from_this<Bullet>
{
public:
	//コンストラクタ
	Bullet();
	//Bulletオブジェクトを初期化する
	void Initialize() override;
	//Bulletオブジェクトを更新する
	void Update(DirectX::SimpleMath::Matrix& matrix) override;
	//Bulletオブジェクトを描画する
	void Draw(std::shared_ptr<Camera> camera) override;
	//Bulletオブジェクトの後処理
	void Finalize() override;
	//球を発射する処理
	void ShootBullet(DirectX::SimpleMath::Matrix& matrix);
	//撃った球をもとに戻す
	void ResultBullet(DirectX::SimpleMath::Matrix& matrix);
	//当たり判定ノードを受け渡す
	//inline std::shared_ptr<SphereNode> GetCollisionNode() override { return _CollisionNode; }
	//親オブジェクトを設定する
	void Add(std::shared_ptr<Tank>&& pNode) override;
	//再帰的にオブジェクトを複製する
	std::shared_ptr<Tank> Clone() override;
	//球の状態を変更する
	void SetShootState(bool state) { _isStateShoot = state; }
	//現在の球の状態を受け渡す
	bool GetShootState() { return _isStateShoot; }
private:
	//球が撃たれているかどうか
	bool _isStateShoot;
	//球の現在値
	DirectX::SimpleMath::Vector3 _bulletPos;
	//撃たれる球の速度
	DirectX::SimpleMath::Vector3 _bulletVel;
	//撃った後のディレイ
	float _flagCount;
	//ポインタの格納
	std::vector<std::shared_ptr<Tank>> _child;
	//CommonStates
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//モデル
	std::unique_ptr<DirectX::Model> _model;
	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//スケール
	DirectX::SimpleMath::Vector3 _scale;
};
