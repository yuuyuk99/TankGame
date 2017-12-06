//--------------------------------------------------------------------------------------
// File: Direct3D.h
//
// Direct3D�Ɋւ���֐��Q
//
// Date: 2015.6.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <memory>

//////////////////////////////
// �֐��̃v���g�^�C�v�錾	//
//////////////////////////////
HRESULT Direct3D_InitDevice(HWND hWnd);
HRESULT Direct3D_InitBackBuffer();
void Direct3D_CleanupDevice();

//////////////////////////////
// �O���[�o���ϐ�			//
//////////////////////////////
extern Microsoft::WRL::ComPtr<ID3D11Device>				g_pd3dDevice;			// DirectX11�̃f�o�C�X
extern Microsoft::WRL::ComPtr<ID3D11DeviceContext>		g_pImmediateContext;	// �R���e�L�X�g
extern Microsoft::WRL::ComPtr<IDXGISwapChain>			g_pSwapChain;			// �X���b�v�`�F�C��
extern Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	g_pRenderTargetView;	// �����_�[�^�[�Q�b�g�r���[
extern Microsoft::WRL::ComPtr<ID3D11Texture2D>			g_pDepthStencil;		// �[�x�X�e���V��
extern Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	g_pDepthStencilView;	// �[�x�X�e���V���r���[
