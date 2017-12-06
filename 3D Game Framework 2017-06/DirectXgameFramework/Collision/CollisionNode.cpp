#include "CollisionNode.h"
//����: �Փ˔���p�m�[�h

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�f�o�b�O������ON/OFF�t���O�̎���
bool CollisionNode::s_DebugVisible = false;

SphereNode::SphereNode()
{
	//�����l(���a1m)
	m_LocalRadius = 1.0f;

	_matrix = Matrix::Identity;
}

void SphereNode::Initialize()
{
	//�f�o�b�O�\���p���f���̓ǂݍ���
	//���f���͔��a1m�ō쐬���邱��
	//m_Obj.LoadModelFile(L"Resources/cModels/hitsphere.cmo");
}

void SphereNode::Update()
{
	//�I�u�W�F�N�g�̍s����X�V
	{
		//�e�ƂȂ�I�u�W�F�N�g����̈ʒu
		m_Obj.SetTrans(m_Trans);
		Vector3 local_scale;
		//���{�Ŕ��a1m�̋����f���Ȃ̂ŁA���a�����̂܂܃X�P�[�����O�ɂȂ�
		local_scale.x = m_LocalRadius;
		local_scale.y = m_LocalRadius;
		local_scale.z = m_LocalRadius;
		m_Obj.SetScale(local_scale);
		//�e�q�֌W���܂߂��s��֌W
		m_Obj.Calc(_matrix);
	}
	//���[���h���W�n�ł̓����蔼�a�����v�Z
	{
		//�v�Z�ς݃��[���h�s����擾
		Matrix worldm = m_Obj.GetLocalWorld();
		//���f�����W�n�ł̒��S
		Vector3 center(0.0f, 0.0f, 0.0f);
		//���f�����W�n�ł̉E�[
		Vector3 right(1.0f, 0.0f, 0.0f);

		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		//���[���h���W�ɕϊ�
		Sphere::center = center;
		//���[���h���W�n�ł̔��a���v�Z
		Sphere::radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Draw()
{
	//�f�o�b�O������ON�Ȃ�
	if (CollisionNode::GetDebugVisible())
	{
		//m_Obj.Draw();
	}
}

void SphereNode::SetParentMatrix(Matrix* pParentMatrix)
{
	m_Obj.SetParentMatrix(pParentMatrix);
}

//^---------------------------------------------------
CapsuleNode::CapsuleNode()
{
	//�����l(���a1m)
	m_LocalRadius = 1.0f;
	//�����l(������3m)
	m_LocalLength = 1.0f;

	_matrix = Matrix::Identity;
}

void CapsuleNode::Initialize()
{
	//�f�o�b�O�\�����f���̓ǂݍ���
	//���f���͔��a1m�A������1m�̉~���ō쐬���邱��
	//m_Obj.LoadModelFile(L"Resources/cModels/hitcapsule.cmo");
}

void CapsuleNode::Update()
{
	//�I�u�W�F�N�g�̍s����X�V
	{
		//�e�ƂȂ�I�u�W�F�N�g����̈ʒu
		m_Obj.SetTrans(m_Trans);
		Vector3 local_scale;
		//���{�Ŕ��a1m�̉~�����f���Ȃ̂ŁA���a�����̂܂܃X�P�[�����O�ɂȂ�
		local_scale.x = m_LocalRadius;
		local_scale.z = m_LocalRadius;
		//���{�Ŏ�������1m�̉~�����f���Ȃ̂ŁA���������̂܂܃X�P�[�����O�ɂȂ�
		local_scale.y = m_LocalLength;
		m_Obj.SetScale(local_scale);
		//�e�q�֌W���܂߂��s��v�Z
		m_Obj.Calc(_matrix);
	}
	//���[���h���W�n�ł̓����蔻��J�v�Z�����v�Z
	{
		//�v�Z�ς݃��[���h�s����擾
		Matrix worldm = m_Obj.GetLocalWorld();
		//���f�����W�n�ł̒��S
		Vector3 center(0.0f, 0.0f, 0.0f);
		//���f�����W�n�ł̏�[
		Vector3 up(0.0f, 1.0f, 0.0f);
		//���f�����W�n�ł̉E�[
		Vector3 right(1.0f, 0.0f, 0.0f);

		//���[���h���W�ɕϊ�
		center = Vector3::Transform(center, worldm);
		up = Vector3::Transform(up, worldm);
		right = Vector3::Transform(right, worldm);
		//���[���h���W�n�ł̎������W��ݒ�
		segment.start = center;
		segment.end = up;
		//���[���h���W�n�ł̔��a���v�Z
		Capsule::radius = Vector3::Distance(center, right);
	}
}

void CapsuleNode::Draw()
{
	if (CollisionNode::GetDebugVisible())
	{
		//m_Obj.Draw();
	}
}

void CapsuleNode::SetParentMatrix(Matrix* pParentMatrix)
{
	m_Obj.SetParentMatrix(pParentMatrix);
}

void CapsuleNode::SetRot(const Vector3& rot)
{
	m_Obj.SetRot(rot);
}