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
	//タンクパーツの座標を返す
	return m_Charcter[PARTS_TANK].GetTrans();
}

void Charcter::SetTrans(Vector3& trans)
{
	// タンクパーツの座標を設定
	m_Charcter[PARTS_TANK].SetTrans(trans);
}

const Vector3& Charcter::GetRot()
{
	return m_Charcter[PARTS_TANK].GetRot();
}

void Charcter::SetRot(Vector3& rot)
{
	// タンクパーツの座標を設定
	m_Charcter[PARTS_TANK].SetRot(rot);
}

const Matrix& Charcter::GetLocalWorld()
{
	// タンクパーツのワールド行列を返す
	return m_Charcter[PARTS_TANK].GetLocalWorld();
}
