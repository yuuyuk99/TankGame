#include "Charcter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Charcter::Charcter() : _isShootState(false)
{

}

Charcter::~Charcter()
{

}
const Vector3& Charcter::GetTrans()
{
	//�^���N�p�[�c�̍��W��Ԃ�
	return m_Charcter[PARTS_TANK].GetTrans();
}

void Charcter::SetTrans(Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Charcter[PARTS_TANK].SetTrans(trans);
}

const Vector3& Charcter::GetRot()
{
	return m_Charcter[PARTS_TANK].GetRot();
}

void Charcter::SetRot(Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Charcter[PARTS_TANK].SetRot(rot);
}

const Matrix& Charcter::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return m_Charcter[PARTS_TANK].GetLocalWorld();
}
