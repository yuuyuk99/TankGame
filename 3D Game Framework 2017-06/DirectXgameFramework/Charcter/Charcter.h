#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../Base/ObjectBase.h"
//#include "../Collision/CollisionNode.h"
//#include "../Map/Map.h"

enum TANK
{
	//本体(これが中心となる)
	PARTS_TANK,
	//砲台
	PARTS_BATTERY,
	//発射する球
	PARTS_BULLET,

	//パーツの個数
	TANK_NUM
};

//操作するキャラクターや敵の親クラスになります
class Charcter
{
public:
	Charcter();
	~Charcter();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Calc() = 0;
	virtual void Draw() = 0;

	//現在の場所を受け取る
	const DirectX::SimpleMath::Vector3& GetTrans();
	//場所の設定
	void SetTrans(DirectX::SimpleMath::Vector3& trans);
	//回転を設定
	void SetRot(DirectX::SimpleMath::Vector3& rot);
	//回転行列を受け取る
	const DirectX::SimpleMath::Vector3& GetRot();
	// ワールド行列を取得
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
	//プレイヤー本体当たり判定
	//const Sphere& GetCollisionBody() { return _CollisionNodeBody; }
	//球のあたり判定
	//const Capsule& GetCollisionBullet() { return _CollisionNodeBullet; }
protected:
	//キャラクター
	ObjectBase m_Charcter[TANK_NUM];
	//球を打っている状態か
	bool _isShootState;
	//当たり判定
	//SphereNode _CollisionNodeBody;
	//球のあたり判定
	//CapsuleNode _CollisionNodeBullet;
	//キャラクターたちの体力
	float _health;
	//ダメージを受けている状態か
	bool _isDamegeState;
	//球を打っているか
	bool _isShoot;
	//マップへのポインタ
	//Map* _Map;
	//マップ上での座標
	DirectX::SimpleMath::Vector3 _Pos;
};