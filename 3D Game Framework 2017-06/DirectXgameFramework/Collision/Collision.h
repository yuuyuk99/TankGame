#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

//��
class Sphere
{
public:
	//���S���W
	DirectX::SimpleMath::Vector3 center;
	//���a
	float radius;
	Sphere()
	{
		radius = 1.0f;
	}
};



//����
class Segment
{
public:
	//�n�_���W
	DirectX::SimpleMath::Vector3 start;
	//�I�_���W
	DirectX::SimpleMath::Vector3 end;
};

//�J�v�Z��
class Capsule
{
public:
	//�c��
	Segment segment;
	//���a
	float radius;
	//�R���X�g���N�^
	Capsule()
	{
		segment.start = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		segment.end = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
		radius = 1.0f;
	}
};

// �@���t���O�p�`�i�����v��肪�\�ʁj
class Triangle
{
public:
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	DirectX::SimpleMath::Vector3	Normal;	// �@���x�N�g��
};

//bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);
//�x�N�g���̒������v�Z
//float VectorLength(const DirectX::SimpleMath::Vector3& v);
//2�_�Ԃ̋������v�Z
//float Distance3D(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2);
//�x�N�g���̒����̓����v�Z
//�O�����̒藝�ŁAsqrtf�����Ȃ���return����
float VectorLengthSQ(const DirectX::SimpleMath::Vector3& v);
//2�]���̋�����2��Ōv�Z
float DistanceSQ3D(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2);
//���Ƌ��̓����蔻��
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::SimpleMath::Vector3* inter = nullptr);
//���Ƌ��̓����蔻��(������)
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB);
//�J�v�Z���ƃJ�v�Z���̓����蔻��
bool CheckCapsule2Capsule(const Capsule& capsule0, const Capsule& capsule1, DirectX::SimpleMath::Vector3* inter = nullptr);
//�J�v�Z���ƃJ�v�Z���̓����蔻��
bool CheckCapsule2Capsule(const Capsule& capsule0, const Capsule& capsule1);
//�_�Ɛ����̋�����2����擾
float GetSqDistancePoint2Segment(const DirectX::SimpleMath::Vector3& point, const Segment& segment);
//���ƃJ�v�Z���̓����蔻��
bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule, DirectX::SimpleMath::Vector3* inter = nullptr);
//���ƃJ�v�Z���̓����蔻��
bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule);
//�����Ɛ����̋�����2����擾
float GetSqDistanceSegment2Segment(const Segment& segment0, const Segment& segment1);
//���Ƌ��̓����蔻��
//bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::SimpleMath::Vector3* inter = nullptr);
void ClosestPtPoint2Segment(const DirectX::SimpleMath::Vector3& point, const Segment& segment, DirectX::SimpleMath::Vector3* closest);
void ClosestPtSegment2Segment(const Segment& segment0, const Segment& segment1, DirectX::SimpleMath::Vector3* closest0, DirectX::SimpleMath::Vector3* closest1);

//3�_����O�p�`���v�Z(�����v���Ɏw��)
void ComputeTriangle(const DirectX::SimpleMath::Vector3& _p0, const DirectX::SimpleMath::Vector3& _p1, const DirectX::SimpleMath::Vector3& _p2, Triangle* _triangle);
//�_�ƎO�p�`�̍ŋߐړ_���v�Z
void ClosestPtPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle, DirectX::SimpleMath::Vector3* _closest);
//�_�ƎO�p�`�̓����蔻��
bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle);
//���Ɩ@���t���O�p�`�̓�����`�F�b�N
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, DirectX::SimpleMath::Vector3* _inter);
//�����i�L���j�Ɩ@���t���O�p�`�̓�����`�F�b�N
bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);

