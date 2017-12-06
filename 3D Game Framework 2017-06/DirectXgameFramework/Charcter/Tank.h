#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <memory>
#include <Model.h>
#include <Keyboard.h>

#include "../Base/ObjectBase.h"
#include "../Collision/CollisionNode.h"

class Camera;

class Tank
{
public:
	enum ID {
		PARTS_BODY,
		PARS_TURRET,
		PARTS_BULLET,

		PARTS_NUM
	};
	//位置
	DirectX::SimpleMath::Vector3 Position() { return _Pos; }
	void Position(DirectX::SimpleMath::Vector3 position) { this->_Pos = position; }

	//コンストラクタ
	Tank();
	Tank(DirectX::SimpleMath::Vector3& position);

	//Tankオブジェクトを初期化する
	virtual void Initialize() {}
	//Tankオブジェクトを更新する
	virtual void Update(DirectX::SimpleMath::Matrix& matrix) {}
	//Tankオブジェクトを描画する
	//void Draw();
	virtual void Draw(std::shared_ptr<Camera>) {}
	//後処理を行う
	virtual void Finalize() {}
	//親オブジェクトを設定する
	virtual void Add(std::shared_ptr<Tank>&& pNode) = 0;
	//親オブジェクトを取得する
	std::weak_ptr<Tank> Parent();
	//親オブジェクトを設定する
	void Parent(const std::shared_ptr<Tank>& parent);
	//再起的にオブジェクトを複製する
	virtual std::shared_ptr<Tank> Clone() = 0;
	//球を撃つ処理
	void SetKeyDown(bool state) { _isKeyDown = state; }
public:
	//ポジションを設定する
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { _body->SetTrans(trans); }
	//現在位置を受け渡す
	DirectX::SimpleMath::Vector3& GetTrans() { return _body->GetTrans(); }
	//速度を設定する
	void SetVelocity(DirectX::SimpleMath::Vector3& vel) { _Velocity = vel; }
	//速度を受け取る
	DirectX::SimpleMath::Vector3& GetVelocity() { return _Velocity; }
	//回転軸を設定する
	void SetRot(DirectX::SimpleMath::Vector3& rot) { _body->SetRot(rot); }
	//回転軸を受け渡す
	DirectX::SimpleMath::Vector3& GetRot() { return _body->GetRot(); }
	//角度を設定
	void SetAngle(float angle) { _angle = angle; }
	//角度を受け渡す
	float GetAngle() { return _angle; }
	//bodyの当たり判定を受け渡す
	SphereNode& GetCollisionNode() { return _collisionNode; }
	//ローカル行列を受け渡す
	DirectX::SimpleMath::Matrix& GetLocalWorld() { return _body->GetLocalWorld(); }
protected:
	//位置
	DirectX::SimpleMath::Vector3 _Pos;
	//速度
	DirectX::SimpleMath::Vector3 _Velocity;
	//回転
	DirectX::SimpleMath::Vector3 _Rot;
	//角度(float型)
	float _angle;
	//子オブジェクトへのポインタ
	std::shared_ptr<Tank> _Child;
	//Rootオブジェクトへのポインタ
	std::shared_ptr<Tank> _Root;
	//
	std::weak_ptr<Tank> _parent;
	//キーボード
	std::shared_ptr<DirectX::Keyboard::State> _keyboard;
	//Bodyオブジェクト
	std::shared_ptr<ObjectBase> _body;
	//turretオブジェクト
	std::shared_ptr<ObjectBase> _turret;
	//bulletオブジェクト
	std::shared_ptr<ObjectBase> _bullet;
	//当たり判定ノード
	SphereNode _collisionNode;
	//球を撃っているかどうかの処理
	bool _isKeyDown;
};
