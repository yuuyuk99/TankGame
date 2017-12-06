#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <memory>
#include "../Base/ObjectBase.h"
#include "../Collision/CollisionNode.h"

class Camera;

class Tower
{
public:
	//コンストラクタ
	Tower();
	//Towerオブジェクトの初期化処理
	void Initialize();
	//Towerオブジェクトの更新処理
	void Update();
	//Towerオブジェクトの描画処理
	void Draw(std::shared_ptr<Camera> camera);
	//Towerオブジェクトの後処理
	void Finalize();
	//Towerオブジェクトの当たり判定
	CapsuleNode& GetCollsionNode() { return _collisionNode; }
	//耐久度の設定
	void SetHealth(int health) { _health = health; }
	//現在の耐久度を受け渡す
	int GetHealth() { return _health; }
	//タワーの陣地を設定
	void SetCamp(int camp) { _camp = camp; }
	//タワーの陣地の情報を受け取る
	int GetCamp() { return _camp; }
	//現在地を設定する
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _Tower->SetTrans(trans); }
	//現在値を受け渡す
	DirectX::SimpleMath::Vector3& GetTrans() { return _Tower->GetTrans(); }
private:
	//タワー
	std::shared_ptr<ObjectBase> _Tower;
	//当たり判定ノード
	CapsuleNode _collisionNode;
	//エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//スケール
	DirectX::SimpleMath::Vector3 _scale;
	//ワールド行列
	DirectX::SimpleMath::Matrix _localWorld;
	//回転でクォータニオンを使用するか
	bool _useQuternion;
	//クォータニオン行列
	DirectX::SimpleMath::Quaternion _quternion;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//当たっているかどうか
	bool _hit;
	//耐久度
	int _health;
	//タワーの陣営
	int _camp;
};
