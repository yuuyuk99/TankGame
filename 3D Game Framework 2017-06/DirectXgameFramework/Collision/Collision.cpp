#include "Collision.h"

using namespace DirectX::SimpleMath;

// �ŏ��l�ƍő�l�̊ԂɃN�����v����
inline float Clamp(float _x, float _min, float _max)
{
	return min(max(_x, _min), _max);
}

//bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
//{
//	//��A��B�̒��S���W�̍����v�Z����
//	//Vector3 sub = sphereA.center - sphereB.center;
//	//�O�����̒藝�ŁA�x�N�g���̒������v�Z����
//	//�����x�N�g���̒����́A2�_�Ԃ̋���
//	//float distance = sqrtf(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
//	float distance = Distance3D(sphereA.center, sphereB.center);
//	//���������a�̗ւ��傫����Γ������Ă��Ȃ�
//	if (distance > sphereA.radius + sphereB.radius)
//	{
//		return false;
//	}
//	return true;
//}
//
//float VectorLength(const Vector3& v)
//{
//	float distance = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
//	return distance;
//}
//
//float Distance3D(const Vector3& p1, const Vector3& p2)
//{
//	float sub = VectorLength(p1 - p2);
//	return sub;
//}

bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//��A��B�̒��S���W�̍����v�Z����
	Vector3 sub = sphereA.center - sphereB.center;
	//�O�����̒藝�ŁA�x�N�g���̒������v�Z����
	//�����x�N�g���̒����́A2�_�Ԃ̋���
	float distanceSQ = DistanceSQ3D(sphereA.center, sphereB.center);

	//���a�̍�
	float radius_sum = sphereA.radius + sphereB.radius;
	float radius_sumSQ = radius_sum * radius_sum;
	//���������a�̗ւ��傫����Γ������Ă��Ȃ�
	if (distanceSQ > sphereA.radius + sphereB.radius)
	{
		return false;
	}
	return true;
}

float VectorLengthSQ(const Vector3& v)
{
	float distance = v.x * v.x + v.y * v.y + v.z * v.z;
	return distance;
}

float DistanceSQ3D(const Vector3& p1, const Vector3& p2)
{
	float sub = VectorLengthSQ(p1 - p2);
	return sub;
}

//�J�v�Z���ƃJ�v�Z���̓����蔻��
bool CheckCapsule2Capsule(const Capsule& capsule0, const Capsule& capsule1)
{
	//���̒��S�ƃJ�v�Z���̐����̋���(��2��)���v�Z
	float distanceSQ = GetSqDistanceSegment2Segment(capsule0.segment, capsule1.segment);

	//���a�̘a(��2��)���v�Z
	float radiusSum = capsule0.radius + capsule1.radius;
	float radiusSumSQ = radiusSum * radiusSum;

	//����(��2��)�����a�̗�(��2��)���傫����Γ������Ă��Ȃ�
	if (distanceSQ > radiusSumSQ) return false;

	return true;
}


//--------------------------------------------------------------------------------------------
// �� �� : �_�Ɛ����̋����̓����擾
// �� �� : _point�_
//			_segment	����
// �߂�l : �_�Ɛ����̋����̓��
// �� �� : ���������Z�o���Ȃ���
//	�����̒[�_��A,B	�_��C�Ƃ��āA
//	�@AB�x�N�g����AC�x�N�g���̓��ς����̎��A�_A���_C�̍ŋߖT�ł���
//	�ABA�x�N�g����BC�x�N�g���̓��ς����̎��A�_B���_C�̍ŋߖT�ł���
//	�B�@�@�A�A�ɊY�����Ȃ��ꍇ�A�_C�̎ˉe��AC�̓����ɑ��݂��邽�߁A���̓_���ŋߖT�ł���
//--------------------------------------------------------------------------------------------
float GetSqDistancePoint2Segment(const Vector3& _point, const Segment& _segment)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vector3 SegmentSub;
	Vector3 SegmentPoint;
	Vector3 CP;

	// �����̎n�_����I�_�ւ̃x�N�g��
	SegmentSub = _segment.end - _segment.start;

	// �����̎n�_����_�ւ̃x�N�g��
	SegmentPoint = _point - _segment.start;
	if (SegmentSub.Dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̎n�_���ŋߖT
		return SegmentPoint.Dot(SegmentPoint);
	}

	// �_��������̏I�_�ւ̃x�N�g��
	SegmentPoint = _segment.end - _point;
	if (SegmentSub.Dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̏I�_���ŋߖT
		return SegmentPoint.Dot(SegmentPoint);
	}

	// ��L�̂ǂ���ɂ��Y�����Ȃ��ꍇ�A������ɗ��Ƃ����ˉe���ŋߖT
	// (�{���Ȃ�T�C���ŋ��߂邪�A�O�ς̑傫��/�����̃x�N�g���̑傫���ŋ��܂�)
	CP = SegmentSub.Cross(SegmentPoint);

	return CP.Dot(CP) / SegmentSub.Dot(SegmentSub);
}

//���ƃJ�v�Z���̓����蔻��
bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule)
{
	float distance2 = GetSqDistancePoint2Segment(sphere.center, capsule.segment);

	//����(��2��)�����a�̘a(��2��)��菬������Γ������Ă���
	float radius = sphere.radius + capsule.radius;

	if (distance2 > radius * radius) return false;

	return true;
}


//--------------------------------------------------------------------------------------------
// ���@�� : �����Ɛ����̋����̓����擾
// ���@�� : _segment0	����0
//			_segment1	����1
// �߂�l : �����Ɛ����̋����̓��
// ���@�� : ���������Z�o���Ȃ���
//	�@������̍Őڋߓ_�������̐����̓����ɑ��݂��鎞
//	�A������̍Őڋߓ_������݂̂̐����̓����ɑ��݂��鎞
//	�B������̍Őڋߓ_�������̐����̊O���ɑ��݂��鎞
//	���ꂼ��̃P�[�X�œ�̐�����̍Őڋߓ_�����߁A���̋������Z�o����
//--------------------------------------------------------------------------------------------
float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vector3 d0, d1, r;
	Vector3 c0, c1;	// ��̐�����̍Őڋߓ_
	Vector3 v;		// c1��c0�x�N�g��
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end - _segment0.start;	// ����0�̕����x�N�g��
	d1 = _segment1.end - _segment1.start; // ����1�̕����x�N�g��
	r = _segment0.start - _segment1.start; // ����1�̎n�_�������0�̎n�_�ւ̃x�N�g��
	a = d0.Dot(d0);		// ����0�̋����̓��
	e = d1.Dot(d1);		// ����1�̋����̓��
						//	b = d0.Dot(d1);		// �œK���̈׌���Ɉړ�����
						//	c = d0.Dot(r);		// �œK���̈׌���Ɉړ�����
						//	f = d1.Dot(r);		// �œK���̈׌���Ɉړ�����

						// ���Âꂩ�̐����̒�����0���ǂ����`�F�b�N
	if (a <= epsilon && e <= epsilon)
	{// ��������0
		v = _segment0.start - _segment1.start;

		return v.Dot(v);
	}

	if (a <= epsilon)
	{// ����0������0
		return GetSqDistancePoint2Segment(_segment0.start, _segment1);
	}

	if (e <= epsilon)
	{// ����1������0
		return GetSqDistancePoint2Segment(_segment1.start, _segment0);
	}

	b = d0.Dot(d1);
	f = d1.Dot(r);
	c = d0.Dot(r);

	denom = a * e - b * b;	// ��ɔ�
							// ���������s�łȂ��ꍇ�A����0��̒���1�ɑ΂���ŋߐړ_���v�Z�A������
							// ����0��ɃN�����v�B�����łȂ��ꍇ�͔C�ӂ�s��I��
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// ����1��̍Őڋߓ_���v�Z
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	c0 = s * d0 + _segment0.start;
	c1 = t * d1 + _segment1.start;
	v = c0 - c1;

	return v.Dot(v);
}


//���Ƌ��̓����蔻��
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, Vector3* inter)
{
	//��A��B�̒��S���W�̍����v�Z����
	Vector3 sub = sphereA.center - sphereB.center;
	//�O�����̒藝�ŁA�x�N�g���̒������v�Z����
	//�����x�N�g���̒����́A2�_�Ԃ̋���
	float distanceSQ = DistanceSQ3D(sphereA.center, sphereB.center);

	//���a�̍�
	float radius_sum = sphereA.radius + sphereB.radius;
	float radius_sumSQ = radius_sum * radius_sum;
	//���������a�̗ւ��傫����Γ������Ă��Ȃ�
	if (distanceSQ > radius_sumSQ)
	{
		return false;
	}

	//�ϐ��A�h���X���w�肵�Ă����ꍇ�̂݋^����_���v�Z����
	if (inter)
	{
		Vector3 sub = sphereA.center - sphereB.center;
		//��A,B�̒��S���W�𔼌a�̔䗦�œ��������_���^����_�Ƃ���
		//B����^����_�ւ̃x�N�g��
		Vector3 BtoInter = sub * sphereB.radius / (sphereA.radius + sphereB.radius);
		*inter = sphereB.center + BtoInter;
	}
	return true;
}

//�J�v�Z���ƃJ�v�Z���̓����蔻��
bool CheckCapsule2Capsule(const Capsule& capsuleA, Capsule& capsuleB, Vector3* inter)
{
	float distanceSQ = GetSqDistanceSegment2Segment(capsuleA.segment, capsuleB.segment);

	//���a�̘a(��2��)���v�Z
	float radiusSum = capsuleA.radius + capsuleB.radius;
	float radiusSumSQ = radiusSum * radiusSum;

	//����(��2��)�����a�̗�(��2��)���傫����Γ������Ă��Ȃ�
	if (distanceSQ > radiusSumSQ) return false;
	if (inter)
	{
		Vector3 cpointA, cpointB;

		ClosestPtSegment2Segment(capsuleA.segment, capsuleB.segment, &cpointA, &cpointB);
		//BtoA�̍����x�N�g��
		Vector3 sub = cpointA - cpointB;
		//����A,B�̍ŋߋߐڐړ_���W���A���a�̔䗦�œ��������_���A�^����_�Ƃ���
		//B����^����_�ւ̃x�N�g��
		Vector3 BtoInter = sub * capsuleB.radius / (capsuleA.radius + capsuleB.radius);
		*inter = cpointB + BtoInter;
	}

	return true;
}

bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule, Vector3* inter)
{
	float distance2 = GetSqDistancePoint2Segment(sphere.center, capsule.segment);

	//����(��2��)�����a�̘a(��2��)��菬������Γ������Ă���
	float radius = sphere.radius + capsule.radius;

	if (distance2 > radius * radius) return false;

	//�ϐ��A�h���X���w�肵�Ă����ꍇ�̂݋^����_���v�Z����
	if (inter)
	{
		//�^����_���v�Z
		Vector3 cpoint;
		//�J�v�Z���̎�����ŁA���܂Ɉ�ԋ߂��_�����߂�
		ClosestPtPoint2Segment(sphere.center, capsule.segment, &cpoint);
		//B��A�̍����x�N�g��
		Vector3 sub = sphere.center - cpoint;
		//A,B�̍ŋߐړ_���W���A���a�̔䗦�œ��������_���A�^����_�Ƃ���
		//B����^����_�ւ̃x�N�g��
		Vector3 BtoInter = sub * capsule.radius / (sphere.radius + capsule.radius);
		*inter = cpoint + BtoInter;
	}
	return true;
}

//--------------------------------------------------------------------------------------------
// ���@�� : �_�Ɛ����̍ŋߐړ_���v�Z
// ���@�� : _point	�_
//			_segment	����
//			_closest	�ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Segment(const Vector3& _point, const Segment& _segment, Vector3* _closest)
{
	Vector3 segv;
	Vector3 s2p;
	float t;

	segv = _segment.end - _segment.start;
	s2p = _point - _segment.start;
	t = segv.Dot(s2p) / segv.Dot(segv);

	// �����̊O���ɂ���ꍇ�At���Őڋߓ_�܂ŃN�����v
	t = Clamp(t, 0, 1);

	// �N�����v����Ă���t����̎ˉe����Ă���ʒu���v�Z
	*_closest = t * segv + _segment.start;
}

//--------------------------------------------------------------------------------------------
// ���@�� : �����Ɛ����̍ŋߐړ_���v�Z
// ���@�� : _segment0	����0
//			_segment1	����1
//			_closest0	����0��̍ŋߐړ_(���ʏo�͗p�j
//			_closest1	����1��̍ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtSegment2Segment(const Segment& _segment0, const Segment& _segment1, Vector3* _closest0, Vector3* _closest1)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vector3 d0, d1, r;
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end - _segment0.start;		// ����0�̕����x�N�g��
	d1 = _segment1.end - _segment1.start;		// ����1�̕����x�N�g��
	r = _segment0.start - _segment1.start;	// ����1�̎n�_�������0�̎n�_�ւ̃x�N�g��
	a = d0.Dot(d0);	// ����0�̋����̓��
	e = d1.Dot(d1);	// ����1�̋����̓��
					//	b = d0.Dot(d1);	// �œK���̈׌���Ɉړ�����
					//	c = d0.Dot(r);	// �œK���̈׌���Ɉړ�����
					//	f = d1.Dot(r);	// �œK���̈׌���Ɉړ�����

					// ���Âꂩ�̐����̒�����0���ǂ����`�F�b�N
	if (a <= epsilon && e <= epsilon)
	{// ��������0
		*_closest0 = _segment0.start;
		*_closest1 = _segment1.start;
		return;
	}

	if (a <= epsilon)
	{// ����0������0
		*_closest0 = _segment0.start;
		ClosestPtPoint2Segment(_segment0.start, _segment1, _closest1);
	}

	if (e <= epsilon)
	{// ����1������0
		*_closest1 = _segment1.start;
		ClosestPtPoint2Segment(_segment1.start, _segment0, _closest0);
	}

	b = d0.Dot(d1);
	f = d1.Dot(r);
	c = d0.Dot(r);

	denom = a * e - b * b;	// ��ɔ�
							// ���������s�łȂ��ꍇ�A����0��̒���1�ɑ΂���ŋߐړ_���v�Z�A������
							// ����0��ɃN�����v�B�����łȂ��ꍇ�͔C�ӂ�s��I��
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// ����1��̍Őڋߓ_���v�Z
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	*_closest0 = s * d0 + _segment0.start;
	*_closest1 = t * d1 + _segment1.start;
}

//--------------------------------------------------------------------------------------------
// ���@�� : �R�_����O�p�`���v�Z�i�����v���Ɏw��j
// ���@�� : _p0	�_�O
//			_p1	�_�P
//			_p2 �_�Q
//			_triangle �O�p�`(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : �����v��菇�ɂR�_�w�肷��
//--------------------------------------------------------------------------------------------
void ComputeTriangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, Triangle* _triangle)
{
	//�O�p�`�̊e���_�̍��W���R�s�[
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;
	//���_0->1,���_0->2�̃x�N�g���̌v�Z
	Vector3 P0_P1 = _triangle->P1 - _triangle->P0;
	Vector3 P1_P2 = _triangle->P2 - _triangle->P1;
	//��ӂɐ����ȃx�N�g�����v�Z
	_triangle->Normal = P0_P1.Cross(P1_P2);
	
	_triangle->Normal.Normalize();
}

//--------------------------------------------------------------------------------------------
// ���@�� : �_�ƎO�p�`�̍ŋߐړ_���v�Z
// ���@�� : _point	�_
//			_segment	����
//			_closest	�ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Triangle(const Vector3& _point, const Triangle& _triangle, Vector3* _closest)
{
	// _point��P0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P0_P1 = _triangle.P1 - _triangle.P0;
	Vector3 P0_P2 = _triangle.P2 - _triangle.P0;
	Vector3 P0_PT = _point - _triangle.P0;

	float d1 = P0_P1.Dot(P0_PT);
	float d2 = P0_P2.Dot(P0_PT);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// P0���ŋߖT
		*_closest = _triangle.P0;
		return;
	}

	// _point��P1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P1_PT = _point - _triangle.P1;

	float d3 = P0_P1.Dot(P1_PT);
	float d4 = P0_P2.Dot(P1_PT);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// P1���ŋߖT
		*_closest = _triangle.P1;
		return;
	}

	// _point��P0_P1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P0_P1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*_closest = _triangle.P0 + v * P0_P1;
		return;
	}

	// _point��P2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 P2_PT = _point - _triangle.P2;

	float d5 = P0_P1.Dot(P2_PT);
	float d6 = P0_P2.Dot(P2_PT);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*_closest = _triangle.P2;
		return;
	}

	// _point��P0_P2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P0_P2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*_closest = _triangle.P0 + w * P0_P2;
		return;
	}

	// _point��P1_P2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����_point��P1_P2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*_closest = _triangle.P1 + w * (_triangle.P2 - _triangle.P1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*_closest = _triangle.P0 + P0_P1 * v + P0_P2 * w;
}

// �_�ƎO�p�`�̓����蔻��
bool CheckPoint2Triangle(const Vector3& _point, const Triangle& _triangle)
{
	//�_�ƎO�p�`�͓��ꕽ�ʏ�ɂ�����̂Ƃ��Ă��܂��B���ꕽ�ʏ�ɖ����ꍇ�͐��������ʂɂȂ�܂���
	//����͊O�Ƃ݂Ȃ��܂��B
	//ABC���O�p�`���ǂ����̃`�F�b�N�͏ȗ�...

	// �_0��1�A 1��2�A 2��0 �̃x�N�g�������ꂼ��v�Z
	Vector3 v01 = _triangle.P1 - _triangle.P0;
	Vector3 v12 = _triangle.P2 - _triangle.P1;
	Vector3 v20 = _triangle.P0 - _triangle.P2;
	// �O�p�`�̊e���_����_�ւ̃x�N�g�������ꂼ��v�Z
	Vector3 v0p = _point - _triangle.P0;
	Vector3 v1p = _point - _triangle.P1;
	Vector3 v2p = _point - _triangle.P2;
	// �e�Ӄx�N�g���ƁA�_�ւ̃x�N�g���̊O�ς��v�Z
	Vector3 c0 = v01.Cross(v0p);
	Vector3 c1 = v12.Cross(v1p);
	Vector3 c2 = v20.Cross(v2p);
	// ���ςœ����������ǂ������ׂ�
	float dot01 = c0.Dot(c1);
	float dot02 = c0.Dot(c2);
	// �O�σx�N�g�����S�ē��������Ȃ�A�O�p�`�̓����ɓ_������
	if (dot01 > 0 && dot02 > 0)
	{
		return true;
	}

	//�O�p�`�̊O���ɓ_������
	return false;

}

//--------------------------------------------------------------------------------------------
// ���@�� : ���Ɩ@���t���O�p�`�̓�����`�F�b�N
// ���@�� : _sphere		��
//			_tri		�@���t���O�p�`
//			_inter		��_�i�ȗ��j
// �߂�l : �������Ă��邩�ۂ�
// ���@�� : ���ʂ̓�����͂Ƃ�Ȃ�
//--------------------------------------------------------------------------------------------
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, Vector3 *_inter)
{
	Vector3 p;

	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	ClosestPtPoint2Triangle(_sphere.center, _triangle, &p);

	Vector3 v = p - _sphere.center;

	// ���ƎO�p�`����������̂́A���̒��S����_p�܂ł̋��������̔��a�����������ꍇ
	if (v.Dot(v) <= _sphere.radius * _sphere.radius)
	{
		if (_inter)
		{
			*_inter = p;
		}

		return true;
	}

	return false;

	// ���ƕ��ʁi�O�p�`������Ă��镽�ʁj�̓����蔻��
	// ���ƕ��ʂ̋������v�Z
	float ds = _sphere.center.Dot(_triangle.Normal);
	float dt = _triangle.P0.Dot(_triangle.Normal);
	float dist = ds - dt;
	// ���������a�ȏ�Ȃ�A������Ȃ�
	if (fabsf(dist) > _sphere.radius)	return false;
	// ���S�_�𕽖ʂɎˉe�����Ƃ��A�O�p�`�̓����ɂ���΁A�������Ă���
	// �ˉe�������W
	Vector3 center = -dist * _triangle.Normal + _sphere.center;

	// �O�p�`�̊O���ɂȂ���΁A�������Ă��Ȃ�
	if (!CheckPoint2Triangle(center, _triangle))	return false;

	if (_inter)
	{
		*_inter = center;	// ��_���R�s�[
	}

	return true;
}

// ���@�� : �����i�L���j�Ɩ@���t���O�p�`�̓�����`�F�b�N
// ���@�� : _segment		�����̐����istart��end���������j
//			_tri		�@���t���O�p�`
//			_inter		��_�i�ȗ��j
// �߂�l : �������Ă��邩�ۂ�
// ���@�� : ���ʂ̓�����͂Ƃ�Ȃ�
//--------------------------------------------------------------------------------------------
bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, Vector3 *_inter)
{
	const float epsilon = -1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vector3 LayV;		// �����̏I�_���n�_
	Vector3 tls;		// �O�p�`�̒��_0�������̎n�_
	Vector3 tle;		// �O�p�`�̒��_0�������̏I�_
	float 	distl0;
	float 	distl1;
	float 	dp;
	float 	denom;
	float 	t;
	Vector3	s;		// �����ƕ��ʂƂ̌�_
	Vector3 st0;		// ��_���O�p�`�̒��_0
	Vector3 st1;		// ��_���O�p�`�̒��_1
	Vector3 st2;		// ��_���O�p�`�̒��_2
	Vector3 t01;		// �O�p�`�̒��_0�����_1
	Vector3 t12;		// �O�p�`�̒��_1�����_2
	Vector3 t20;		// �O�p�`�̒��_2�����_0
	Vector3	m;

	// �����̎n�_���O�p�n�̗����ɂ���΁A������Ȃ�
	tls = _segment.start - _triangle.P0;
	distl0 = tls.Dot(_triangle.Normal);	// �����̎n�_�ƕ��ʂ̋���
	if (distl0 <= epsilon) return false;

	// �����̏I�_���O�p�n�̕\���ɂ���΁A������Ȃ�
	tle = _segment.end - _triangle.P0;
	distl1 = tle.Dot(_triangle.Normal);	// �����̏I�_�ƕ��ʂ̋���
	if (distl1 >= -epsilon) return false;

	// �����ƕ��ʂƂ̌�_s�����
	denom = distl0 - distl1;
	t = distl0 / denom;
	LayV = _segment.end - _segment.start;	// �����̕����x�N�g�����擾
	s = t * LayV + _segment.start;

	// ��_���O�p�`�̓����ɂ��邩�ǂ����𒲂ׂ�B
	// �O�p�`�̓����ɂ���ꍇ�A��_����e���_�ւ̃x�N�g���Ɗe�Ӄx�N�g���̊O�ρi�O�g�j���A
	// �S�Ė@���Ɠ�������������
	// ��ł���������v���Ȃ���΁A������Ȃ��B
	st0 = _triangle.P0 - s;
	t01 = _triangle.P1 - _triangle.P0;
	m = st0.Cross(t01);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	st1 = _triangle.P1 - s;
	t12 = _triangle.P2 - _triangle.P1;
	m = st1.Cross(t12);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	st2 = _triangle.P2 - s;
	t20 = _triangle.P0 - _triangle.P2;
	m = st2.Cross(t20);
	dp = m.Dot(_triangle.Normal);
	if (dp <= epsilon) return false;

	if (_inter)
	{
		*_inter = s;	// ��_���R�s�[
	}

	return true;
}