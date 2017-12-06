#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	//コンストラクタ
	Camera();
	//デストラクタ
	~Camera();
	//更新
	void Update();
	//アクセッサ
	void SetEyepos(const DirectX::SimpleMath::Vector3 pos) { m_Eyepos = pos; }
	void SetRefpos(const DirectX::SimpleMath::Vector3 pos) { m_Refpos = pos; }
	void SetUpvec(const DirectX::SimpleMath::Vector3 vec) { m_Upvec = vec; }
	const DirectX::SimpleMath::Vector3& GetEyepos() const { return m_Eyepos; }
	const DirectX::SimpleMath::Vector3& GetRefpos() const { return m_Refpos; }
	const DirectX::SimpleMath::Vector3& GetUpvec() const { return m_Upvec; }
	const DirectX::SimpleMath::Matrix& GetViewmat() const { return m_Viewmat; }
	const DirectX::SimpleMath::Matrix& GetProjmat() const { return m_Projmat; }
	void SetFovY(const float FovY) { m_FovY = FovY; }
	void SetAspect(const float Aspect) { m_Aspect = Aspect; }
	void SetNearClip(const float NearClip) { m_NearClip = NearClip; }
	void SetFarClip(const float FarClip) { m_FarClip = FarClip; }
private:
	//ビュー行列
	DirectX::SimpleMath::Matrix m_Viewmat;
	//カメラの座標
	DirectX::SimpleMath::Vector3 m_Eyepos;
	//ターゲット座標
	DirectX::SimpleMath::Vector3 m_Refpos;
	//上方向ベクトル
	DirectX::SimpleMath::Vector3 m_Upvec;
	//プロジェクション行列
	DirectX::SimpleMath::Matrix m_Projmat;
	//縦方向視野角
	float m_FovY;
	//アスペクト比
	float m_Aspect;
	//ニアクリップ
	float m_NearClip;
	//ファークリップ
	float m_FarClip;
};