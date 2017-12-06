#include "Camera.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera() : m_FovY(XMConvertToRadians(60.0f)), m_Aspect(800.0f / 600.0f), m_NearClip(0.1f), m_FarClip(1000.0f)
{
	m_Viewmat = Matrix::Identity;
	m_Eyepos = Vector3(0.0f, 20.0f, 7.0f);
	//m_Eyepos = Vector3(0.0f, 200.0f, 50.0f);
	m_Refpos = Vector3(0.0f, 1.0f, 0.0f);
	m_Upvec = Vector3(0.0f, 1.0f, 0.0f);
	m_Projmat = Matrix::Identity;
}

Camera::~Camera()
{

}

void Camera::Update()
{
	//ビュー行列の計算
	m_Viewmat = Matrix::CreateLookAt(m_Eyepos, m_Refpos, m_Upvec);
	//プロジェクション行列を計算
	m_Projmat = Matrix::CreatePerspectiveFieldOfView(m_FovY, m_Aspect, m_NearClip, m_FarClip);
}