#pragma once
#include <Model.h>
#include <Effects.h>
#include <map>
#include <d3d11.h>
#include <SimpleMath.h>
#include <memory>
#include <CommonStates.h>

class Camera;

//@ �L�����N�^�[�����̓����̃x�[�X�ɂȂ�Ƃ���ł�
class ObjectBase
{
public:
	//�G�t�F�N�g�t�@�N�g���[��setter
	static void SetEffectFactory(std::shared_ptr<DirectX::EffectFactory> pEffect) { s_pEffectFactory = pEffect; }
	//�`��X�e�[�g��setter
	static void SetStates(std::shared_ptr<DirectX::CommonStates> pStates) { s_pStates = pStates; }
	//�J������setter
	static void SetCamera(std::shared_ptr<Camera> pCamera) { s_pCamera = pCamera; }
private:
	//���ʂ̃G�t�F�N�g�t�@�N�g��
	static std::shared_ptr<DirectX::EffectFactory> s_pEffectFactory;
	//�ǂݍ��ݍς݃��f���R���e�i
	static std::map<std::wstring, std::shared_ptr<DirectX::Model>> s_modellarray;
	//�`��X�e�[�g�ւ̃|�C���^
	static std::shared_ptr<DirectX::CommonStates> ObjectBase::s_pStates;
	//���ʂ̃J����(�`�掞�Ɏg�p)
	static std::shared_ptr<Camera> s_pCamera;
public:
	//�R���e�L�X�g
	ObjectBase();
	//�f�X�g���N�^
	~ObjectBase();
	//�t�@�C�����烂�f����ǂݍ���
	void LoadModelFile(const wchar_t* filename = nullptr);
	//�s��̌v�Z
	void Calc(DirectX::SimpleMath::Matrix& matrix);
	//�`��
	void Draw(std::shared_ptr<Camera> camera, DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f), ID3D11PixelShader* pl = nullptr);
	//�I�u�W�F�N�g�̃��C�e�B���O�𖳌��ɂ���
	void DisableLighting();

	//�A�N�Z�b�T
	//���s�ړ���������
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { _Trans = trans; }
	//��]���s��
	void SetRot(const DirectX::SimpleMath::Vector3& rot) { _Rot = rot; }
	//�X�P�[���̕ύX
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { _Scale = scale; }
	//���[���h�s��̐ݒ�
	void SetLocalWorld(const DirectX::SimpleMath::Matrix& mat) { _LocalWorld = mat; }
	//�e�q�֌W����������
	void SetParentMatrix(const DirectX::SimpleMath::Matrix* pParent) { _pParentMatrix = pParent; }
	//�N�H�[�^�j�I���ł̉�]�s��
	void SetRotQ(const DirectX::SimpleMath::Quaternion& rotQ) { _RotQ = rotQ; }
	//�N�H�[�^�j�I�����g�p����
	void SetUseQuternion(bool flag) { _UseQuternion = flag; }
	
	//���݂̍��W���󂯗���
	DirectX::SimpleMath::Vector3& GetTrans() { return _Trans; }
	//���݂̉�]�p�x���󂯗���
	DirectX::SimpleMath::Vector3& GetRot() { return _Rot; }
	//���݂̊g��k�����󂯗���
	DirectX::SimpleMath::Vector3& GetScale() { return _Scale; }
	//���݂̃��[���h�s����󂯗���
	DirectX::SimpleMath::Matrix& GetLocalWorld() { return _LocalWorld; }

protected:
	//���f��
	std::shared_ptr<DirectX::Model> _model;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> _commonState;
	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> _factory;
	//���s�ړ�
	DirectX::SimpleMath::Vector3 _Trans;
	//��]
	DirectX::SimpleMath::Vector3 _Rot;
	//�X�P�[�����O
	DirectX::SimpleMath::Vector3 _Scale;
	//���[���h�s��
	DirectX::SimpleMath::Matrix _LocalWorld;
	//��]���N�H�[�^�j�I���ő҂��ǂ���
	bool _UseQuternion;
	//�N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion _RotQ;
	//�e�̃��[���h�s��ւ̃|�C���^
	const DirectX::SimpleMath::Matrix* _pParentMatrix;
	//���݂̃J�[�h���
	bool _States;
};

