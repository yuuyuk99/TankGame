
#ifndef GRID
#define GRID

#include <Windows.h>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <wrl.h>
#include <CommonStates.h>
#include <algorithm>
#include <DirectXColors.h>

using namespace Microsoft;
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace std;

class Grid
{
	// [ADD]
	ComPtr<ID3D11Device> m_d3dDevice;
	// [ADD]
	ComPtr<ID3D11DeviceContext>	m_d3dContext;
	// [ADD]
	unique_ptr<CommonStates> m_commonStates;

	// �G�t�F�N�g
	unique_ptr<BasicEffect>	m_basicEffect;

	// �v���~�e�B�u�o�b�`
	unique_ptr<PrimitiveBatch<VertexPositionColor>> m_primitiveBatch;

	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_pInputLayout;

	// �O���b�h�`��G���A�̕�,����,�i�q�̃T�C�Y
	int m_width, m_height, m_size;

	// �I�t�Z�b�g
	int m_offsetX, m_offsetY;

public:
	// �R���X�g���N�^
	Grid(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, int width, int height, int size);

	// �f�X�g���N�^
	~Grid();

	// �`��
	void Render();

	// �O���b�h�̃T�C�Y��ݒ肷��
	void SetGripInfo(int width, int height, int size) {
		this->m_width = width;
		this->m_height = height;
		this->m_size = size;
	}

	// �I�t�Z�b�g��ݒ肷��
	void SetOffset(int offsetX, int offsetY) {
		this->m_offsetX = offsetX;
		this->m_offsetY = offsetY;
	}
};


//�@�O���b�h��̏��`��N���X
class GridFloor
{
private:
	// [ADD]
	Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	// [ADD]
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	// [ADD]
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_pInputLayout;

	// ���̈�ӂ̃T�C�Y
	float m_size;

	// ������
	int m_divides;

public:
	// �R���X�g���N�^�i���̈�ӂ̃T�C�Y�A��ӂ̕������j
	GridFloor(ComPtr<ID3D11Device> d3dDevice, ComPtr<ID3D11DeviceContext> d3dContext, float size, int divides);

	// �f�X�g���N�^
	~GridFloor();

	// �`��i�r���[�s��A�ˉe�s��j
	void Render(SimpleMath::Matrix view, SimpleMath::Matrix proj, DirectX::GXMVECTOR color = DirectX::Colors::Gray);
};

#endif	// GRID
