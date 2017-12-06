#pragma once
#ifndef GRAPHICS
#define GRAPHICS

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <SimpleMath.h>
#include <wrl.h>
#include "dx.h"

using namespace std;

// Uncopyable�N���X
class Uncopyable {
protected:
	Uncopyable() = default;
	~Uncopyable() = default;
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator =(const Uncopyable&) = delete;
};

// Graphics�N���X
class Graphics : private Uncopyable {
private:
	// �R���X�g���N�^ Constructor
	Graphics() {}

public:
	// Graphics�N���X�̃C���X�^���X���擾���� Get instance of Graphics class
	static Graphics& Get() {
		if (graphics.get() == nullptr) {
			graphics.reset(new Graphics());
		}
		return *graphics.get();
	}

	// Graphics�I�u�W�F�N�g��j������ Dispose Graphics object
	static void Dispose() {
		graphics.reset();
	}
	// �E�B���h�E�n���h�����擾���� Get hWnd
	HWND HWnd() {
		return hWnd;
	}
	// �E�B���h�E�n���h����ݒ肷�� Set hWnd
	void HWnd(HWND hWnd) {
		this->hWnd = hWnd;
	}
	// �E�B���h�E�����擾���� Get width
	int Width() {
		return width;
	}
	// �E�B���h�E����ݒ肷�� Set width
	void Width(int width) {
		this->width = width;
	}
	// �E�B���h�E�����擾���� Get height
	int Height() {
		return height;
	}
	// �E�B���h�E����ݒ肷�� Set height
	void Height(int height) {
		this->height = height;
	}
	// �f�o�C�X���擾���� Get device object
	Microsoft::WRL::ComPtr<ID3D11Device> Device() { 
		return this->device; 
	}
	// �f�o�C�X��ݒ肷�� Set device object
	void Device(Microsoft::WRL::ComPtr<ID3D11Device> device) {
		this->device = device;
	}
	// �f�o�C�X�R���e�L�X�g���擾���� Get device context object
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context() {
		return this->context;
	}
	// �f�o�C�X�R���e�L�X�g��ݒ肷�� Set device context object
	void Context(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context) {
		this->context = context;
	}

	// �X���b�v�`�F�C�����擾���� Get SwapChain
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain() {
		return swapChain;
	}
	// �X���b�v�`�F�C����ݒ肷�� Set SwapChain
	void SwapChain(Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain) {
		this->swapChain = swapChain;
	}
	// �����_�[�^�[�Q�b�g�r���[���擾����Get RenderTargetView
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView() {
		return renderTargetView;
	}
	// �����_�[�^�[�Q�b�g�r���[��ݒ肷�� Set RenderTargetView
	void RenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView) {
		this->renderTargetView = renderTargetView;
	}

	// �f�v�X�X�e���V���r���[���擾���� Get DepthStencilView
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView() {
		return depthStencilView;
	}
	// �f�v�X�X�e���V���r���[��ݒ肷�� Set DepthStencilView
	void DepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView) {
		this->depthStencilView = depthStencilView;
	}

	// �f�o�C�X�𐶐����� Create device
	void CreateDevice();

	// ���\�[�X�𐶐����� Create Resource
	void CreateResources();

	// �f�o�C�X���X�g�����������ꍇ OnDeviceLost
	void OnDeviceLost();
	
	//// Throw exception of error
	//void ThrowIfFailed(HRESULT hr) {
	//	if (FAILED(hr)) {
	//		// Set a breakpoint on this line to catch DirectX API errors
	//		throw std::exception();
	//	}
	//}

private:
	static std::unique_ptr<Graphics> graphics;

	HWND hWnd;
	int  width;
	int  height;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11Device1> device1;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>	context;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> context1;
	D3D_FEATURE_LEVEL  featureLevel;

	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
};

#endif	// GRAPHICS

