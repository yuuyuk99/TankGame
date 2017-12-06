#include "ObjectBase.h"
#include "../Camera/Camera.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <CommonStates.h>
#include "../Graphics.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

//�ÓI�����o�ϐ��̎���
shared_ptr<EffectFactory> ObjectBase::s_pEffectFactory;
map<wstring, shared_ptr<Model>> ObjectBase::s_modellarray;
shared_ptr<Camera> ObjectBase::s_pCamera;

/*
 *@�R���X�g���N�^
 */
ObjectBase::ObjectBase() : _pParentMatrix(nullptr), _model(nullptr)
{
	//�X�P�[����1�{���f�t�H���g
	_Scale = Vector3(1.0f, 1.0f, 1.0f);
	//���f�����擾����
	this->_model = make_shared<Model>();

	_UseQuternion = false;
}

/*
 *@�f�X�g���N�^
 */
ObjectBase::~ObjectBase()
{

}

/*
 *@�t�@�C�����烂�f����ǂݍ���
 */
void ObjectBase::LoadModelFile(const wchar_t* filename)
{
	//�O���t�B�b�N�X���󂯎��
	auto& graphics = Graphics::Get();

	//�R�����X�e�[�g���擾
	this->_commonState = make_unique<CommonStates>(graphics.Device().Get());
	//�G�t�F�N�g�t�@�N�g���̎擾
	this->_factory = make_unique<EffectFactory>(graphics.Device().Get());

	//�������O�̃��f����ǂݍ��ݍς݂łȂ����
	if (s_modellarray.count(filename) == 0)
	{
		//���f����ǂݍ���,�R���e�i�ɓo�^(�L�[�̓t�@�C����)
		s_modellarray[filename] = Model::CreateFromCMO(graphics.Device().Get(), filename, *this->_factory);
	}

	_model = s_modellarray[filename];

}

/*
 *@�I�u�W�F�N�g�̃��C�e�B���O�𖳌��ɂ���
 */
void ObjectBase::DisableLighting()
{
	if (!_model)
	{
		return;
	}

	//���f�����̃��b�V������
	ModelMesh::Collection::const_iterator it_mesh = _model->meshes.begin();
	for (; it_mesh != _model->meshes.end(); it_mesh++)
	{
		ModelMesh* modelmesh = it_mesh->get();
		assert(modelmesh);

		//���b�V�����̑S�p�[�c����
		vector<unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
		for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
		{
			ModelMeshPart* meshpart = it_meshpart->get();
			assert(meshpart);

			//���b�V���p�[�c�ɃZ�b�g���ꂽ�G�t�F�N�g��BasicEffect�Ƃ��Ď擾
			BasicEffect* eff = static_cast<BasicEffect*>(meshpart->effect.get());
			if (!eff)
			{
				return;
			}
			XMVECTOR emissive;
			emissive.m128_f32[0] = 1.0f;
			emissive.m128_f32[1] = 1.0f;
			emissive.m128_f32[2] = 1.0f;
			emissive.m128_f32[3] = 1.0f;
			eff->SetEmissiveColor(emissive);
			for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
			{
				//���C�g�𖳌��ɂ���
				eff->SetLightEnabled(i, false);
			}
		}
	}
}

/*
 *@�s��X�V���s��
 */
void ObjectBase::Calc(Matrix& matrix)
{
	//�X�P�[��
	Matrix scalem;
	//��]
	Matrix rotm;
	//���W
	Matrix transm;

	//�X�P�[��
	scalem = Matrix::CreateScale(_Scale);

	if (_UseQuternion)
	{
		//�N�H�[�^�j�I�������]�s����v�Z
		rotm = Matrix::CreateFromQuaternion(_RotQ);
	}
	else
	{
		//�I�C����p�����]�s����v�Z
		rotm = Matrix::CreateFromYawPitchRoll(_Rot.y, _Rot.x, _Rot.z);
	}

	//���W
	transm = Matrix::CreateTranslation(_Trans);

	//���[���h�s���SRT�ɍ���
	_LocalWorld = Matrix::Identity;
	_LocalWorld *= scalem;
	_LocalWorld *= matrix;
	_LocalWorld *= rotm;
	_LocalWorld *= transm;


	//�e�s�񂪂����
	if (_pParentMatrix)
	{
		//�e�s����|����
		_LocalWorld = _LocalWorld * (*_pParentMatrix);
	}
}

/*
 *@�`�揈�����s��
 */
void ObjectBase::Draw(shared_ptr<Camera> camera, Vector3 scale, ID3D11PixelShader* ps)
{
	//�O���t�B�b�N�X�̃C���X�^���X
	auto& graphics = Graphics::Get();
	//�J�����̃r���[�s����󂯎����view�s��ɑ������
	Matrix view = camera->GetViewmat();
	//�J�����̃v���W�F�N�V�����s����󂯎����proj�s��ɑ��
	Matrix proj = camera->GetProjmat();

	// ���f���̕`��
	_model->Draw(Graphics::Get().Context().Get(), *this->_commonState, _LocalWorld, view, proj);

}
