#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

//球
class Sphere
{
public:
	//中心座標
	DirectX::SimpleMath::Vector3 center;
	//半径
	float radius;
	Sphere()
	{
		radius = 1.0f;
	}
};



//線分
class Segment
{
public:
	//始点座標
	DirectX::SimpleMath::Vector3 start;
	//終点座標
	DirectX::SimpleMath::Vector3 end;
};

//カプセル
class Capsule
{
public:
	//芯線
	Segment segment;
	//半径
	float radius;
	//コンストラクタ
	Capsule()
	{
		segment.start = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		segment.end = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
		radius = 1.0f;
	}
};

// 法線付き三角形（反時計回りが表面）
class Triangle
{
public:
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	DirectX::SimpleMath::Vector3	Normal;	// 法線ベクトル
};

//bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);
//ベクトルの長さを計算
//float VectorLength(const DirectX::SimpleMath::Vector3& v);
//2点間の距離を計算
//float Distance3D(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2);
//ベクトルの長さの二乗を計算
//三平方の定理で、sqrtfをしないでreturnする
float VectorLengthSQ(const DirectX::SimpleMath::Vector3& v);
//2転換の距離を2乗で計算
float DistanceSQ3D(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2);
//球と球の当たり判定
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::SimpleMath::Vector3* inter = nullptr);
//球と球の当たり判定(高速版)
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);
//カプセルとカプセルの当たり判定
bool CheckCapsule2Capsule(const Capsule& capsule0, const Capsule& capsule1, DirectX::SimpleMath::Vector3* inter = nullptr);
//カプセルとカプセルの当たり判定
bool CheckCapsule2Capsule(const Capsule& capsule0, const Capsule& capsule1);
//点と線分の距離の2乗を取得
float GetSqDistancePoint2Segment(const DirectX::SimpleMath::Vector3& point, const Segment& segment);
//球とカプセルの当たり判定
bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule, DirectX::SimpleMath::Vector3* inter = nullptr);
//球とカプセルの当たり判定
bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule);
//線分と線分の距離の2乗を取得
float GetSqDistanceSegment2Segment(const Segment& segment0, const Segment& segment1);
//球と球の当たり判定
//bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::SimpleMath::Vector3* inter = nullptr);
void ClosestPtPoint2Segment(const DirectX::SimpleMath::Vector3& point, const Segment& segment, DirectX::SimpleMath::Vector3* closest);
void ClosestPtSegment2Segment(const Segment& segment0, const Segment& segment1, DirectX::SimpleMath::Vector3* closest0, DirectX::SimpleMath::Vector3* closest1);

//3点から三角形を計算(反時計回りに指定)
void ComputeTriangle(const DirectX::SimpleMath::Vector3& _p0, const DirectX::SimpleMath::Vector3& _p1, const DirectX::SimpleMath::Vector3& _p2, Triangle* _triangle);
//点と三角形の最近接点を計算
void ClosestPtPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle, DirectX::SimpleMath::Vector3* _closest);
//点と三角形の当たり判定
bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle);
//球と法線付き三角形の当たりチェック
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, DirectX::SimpleMath::Vector3* _inter);
//線分（有向）と法線付き三角形の当たりチェック
bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);

