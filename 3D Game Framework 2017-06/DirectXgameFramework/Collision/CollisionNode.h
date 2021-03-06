#pragma once
#include "../Base/ObjectBase.h"
#include "Collision.h"
class CollisionNode
{
protected:
	//デバッグ表示のON/OFFフラグ
	static bool s_DebugVisible;
public:
	//デバッグ表示のON/OFFを設定
	static void SetDebugVisible(bool flag) { s_DebugVisible = flag; }
	//デバッグ表示のON/OFFを取得
	static bool GetDebugVisible(void) { return s_DebugVisible; }
};

//当たり判定ノード
class SphereNode : public Sphere
{
public:
	//コンストラクタ
	SphereNode();
	//初期化
	void Initialize();
	//描画
	void Draw();
	//更新
	void Update();
	//親行列を設定
	void SetParentMatrix(DirectX::SimpleMath::Matrix* pParentMatrix);
	//ローカル半径を設定
	void SetLocalradius(float radius) { m_LocalRadius = radius; }
	//親行列からのオフセットを設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }
protected:
	//表示用オブジェクト
	ObjectBase m_Obj;
	//親行列の影響を受ける前のローカル半径
	float m_LocalRadius;
	//親行列からのオフセット座標
	DirectX::SimpleMath::Vector3 m_Trans;
	//行列
	DirectX::SimpleMath::Matrix _matrix;
};

//デバッグ表示付きカプセルノード
class CapsuleNode : public Capsule
{
public:
	//コンストラクタ
	CapsuleNode();
	//初期化
	void Initialize();
	//描画
	void Draw();
	//更新
	void Update();
	//親行列を設定
	void SetParentMatrix(DirectX::SimpleMath::Matrix* pParentMatrix);
	//親行列からの回転を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	//ローカル半径の設定
	void SetLocalRadius(float radius) { m_LocalRadius = radius; }
	//ローカル軸長さを設定
	void SetLength(float length) { m_LocalLength = length; }
	//親行列からのオフセットを設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_Trans = trans; }
protected:
	//表示用オブジェクト
	ObjectBase m_Obj;
	//親行列の影響を受ける前のローカル軸長さ
	float m_LocalLength;
	//親行列の影響を受ける前のローカル半径
	float m_LocalRadius;
	//親行列からのオフセット座標
	DirectX::SimpleMath::Vector3 m_Trans;
	//行列
	DirectX::SimpleMath::Matrix _matrix;
};
