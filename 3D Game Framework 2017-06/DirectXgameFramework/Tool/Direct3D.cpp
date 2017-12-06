//--------------------------------------------------------------------------------------
// File: Direct3D.cpp
//
// Direct3D�Ɋւ���֐��Q
//
// ���l�F���̃v���O������Direct3D���g�p���邽�߂̏������֐��������T���v���ł�
//
// Date: 2015.6.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include <DirectXColors.h>
#include "Direct3D.h"

using namespace Microsoft::WRL;

//////////////////////////////////
// �����N���郉�C�u�����w��		//
//////////////////////////////////
#pragma comment(lib, "d3d11.lib")

//////////////////////
// �O���[�o���ϐ�	//
//////////////////////
BOOL								g_fullScreen = FALSE;					// �t���X�N���[���ŋN������ꍇ��TRUE���w�肷��
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;	// �h���C�o�[�^�C�v�i�n�[�h�E�F�A�Ȃǁj
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;// �@�\���x��
ComPtr<ID3D11Device>                g_pd3dDevice;							// DirectX11�̃f�o�C�X
ComPtr<ID3D11DeviceContext>         g_pImmediateContext;					// �R���e�L�X�g
ComPtr<IDXGISwapChain>              g_pSwapChain;							// �X���b�v�`�F�C��
ComPtr<ID3D11RenderTargetView>      g_pRenderTargetView;					// �����_�[�^�[�Q�b�g�r���[
ComPtr<ID3D11Texture2D>             g_pDepthStencil;						// �[�x�X�e���V��
ComPtr<ID3D11DepthStencilView>      g_pDepthStencilView;					// �[�x�X�e���V���r���[

//--------------------------------------------------------------------------------------
// DirectX�f�o�C�X�̏�����
//--------------------------------------------------------------------------------------
HRESULT Direct3D_InitDevice(HWND hWnd)
{
	HRESULT hr = S_OK;

	// �N���C�A���g�̈�̎擾
	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;	// �f�o�b�N���C���[���T�|�[�g����t���O
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;	// <--���t���b�V�����[�g��DXGI�̎����ݒ�ɔC����
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = !g_fullScreen;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // <--�t���X�N���[���ւ̐؂�ւ��̎��ɕ\�����[�h��ύX����

	//////////////////////////////////////
	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬	//
	//////////////////////////////////////
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(nullptr, g_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	//////////////////////////////////////////////////
	// Atl+Enter�ŉ�ʃ��[�h��ύX���Ȃ��悤�ɂ���	//
	//////////////////////////////////////////////////
	ComPtr<IDXGIDevice1> pDXGIDevice;
	ComPtr<IDXGIAdapter> pDXGIAdapter;
	ComPtr<IDXGIFactory> pDXGIFactory;

	// �C���^�[�t�F�C�X�擾
	hr = g_pd3dDevice.As(&pDXGIDevice);
	if (FAILED(hr)) {
		return hr;
	}

	// �A�_�v�^�[�擾
	hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
	if (FAILED(hr)) {
		return hr;
	}
	// �t�@�N�g���[�擾
	hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (LPVOID*)&pDXGIFactory);
	if (FAILED(hr)) {
		return hr;
	}
	// ��ʃ��[�h�̐؂�ւ��@�\�̐ݒ�
	hr = pDXGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_WINDOW_CHANGES);
	if (FAILED(hr)) {
		return hr;
	}

	//////////////////////////
	// �o�b�N�o�b�t�@�̍쐬	//
	//////////////////////////
	hr = Direct3D_InitBackBuffer();
	if (FAILED(hr))
		return hr;

	//////////////////////
	// �r���[�|�[�g�쐬	//
	//////////////////////
	CD3D11_VIEWPORT vp(0.0f, 0.0f, (FLOAT)width, (FLOAT)height);
	g_pImmediateContext->RSSetViewports(1, &vp);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// �o�b�N�o�b�t�@�Ɛ[�x�o�b�t�@�̐ݒ�
//--------------------------------------------------------------------------------------
HRESULT Direct3D_InitBackBuffer()
{
	HRESULT hr = S_OK;

	//////////////////////////
	// �o�b�N�o�b�t�@�̍쐬	//
	//////////////////////////

	// �X���b�v�`�F�[������o�b�N�o�b�t�@���擾
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	// �o�b�N�o�b�t�@�Ɏw�肳��Ă���e�N�X�`�������擾
	D3D11_TEXTURE2D_DESC descBackBuffer;
	pBackBuffer->GetDesc(&descBackBuffer);

	// �����_�[�^�[�Q�b�g�r���[���쐬
	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, g_pRenderTargetView.GetAddressOf());
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	//////////////////////////
	// �[�x�o�b�t�@�̍쐬	//
	//////////////////////////

	// �[�x�X�e���V���e�N�X�`���̍쐬
	CD3D11_TEXTURE2D_DESC descDepth(descBackBuffer);	// <--�o�b�N�o�b�t�@�Ɏw�肳��Ă���e�N�X�`���������ɐݒ肷��
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = g_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);
	if (FAILED(hr))
		return hr;

	// �[�x�X�e���V���r���[�̍쐬
	CD3D11_DEPTH_STENCIL_VIEW_DESC descDSV(D3D11_DSV_DIMENSION_TEXTURE2D, descDepth.Format);
	hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil.Get(), &descDSV, &g_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	//////////////////////////////
	// �����_�[�^�[�Q�b�g�ݒ�	//
	//////////////////////////////
	g_pImmediateContext->OMSetRenderTargets(1, g_pRenderTargetView.GetAddressOf(), g_pDepthStencilView.Get());

	return S_OK;
}

//--------------------------------------------------------------------------------------
// DirectX�f�o�C�X����̏I������
//--------------------------------------------------------------------------------------
void Direct3D_CleanupDevice()
{
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
}

