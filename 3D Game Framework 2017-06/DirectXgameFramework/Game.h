// Game.h

#pragma once
#ifndef GAME
#define GAME

#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Model.h>
#include <Keyboard.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <algorithm>

#include "StepTimer.h"
#include "dx.h"
#include "Window.h"
#include "Graphics.h"
#include "Grid.h"

#include "DebugCamera.h"
#include "Camera/Camera.h"

class Window;

// D3D11�f�o�C�X�𐶐����A�Q�[�����[�v��񋟂����{�Q�[������
// A basic game implementation that creates a D3D11 device and provides a game loop.
class Game
{
public:
	// ��{�Q�[�����[�v�����s���� Run basic game loop
	MSG Run();

	// �R���X�g���N�^ Constructor
    Game(int width, int height);
    // �������ƊǗ� Initialization and management
    virtual void Initialize(int width, int height);
    // ��{�Q�[�����[�v Basic game loop
	virtual void Update(const DX::StepTimer& timer);
	// ��ʂ��N���A���� Clear screen
	virtual void Clear();
	// �V�[����`�悷�� Render scene
	virtual void Render(const DX::StepTimer& timer);
	// �o�b�N�o�b�t�@���X�N���[���ɑ���
    virtual void Present();
	// �I������
	virtual void Finalize();

    // ���b�Z�[�W Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // �v���p�e�B Properties
    void GetDefaultSize(int& width, int& height) const;

	
	// FPS��`�悷�� Draw FPS
	//void DrawFPS();

	static std::unique_ptr<DirectX::Keyboard> keyboard;
private:
	HINSTANCE hInstance;
	int nCmdShow;
    // �f�o�C�X���\�[�X Device resources.
    HWND hWnd;
	// �o�͕� Output width
    int width;
	// �o�͍� Output height
    int height;

	// �E�B���h�E Window
	std::unique_ptr<Window> window;
	// �O���t�B�b�N�X Graphics
	std::unique_ptr<Graphics> graphics;
	// �@�\���x�� Feature level
    D3D_FEATURE_LEVEL featureLevel;

protected:
    // ���[�v�^�C�}�[��`�悷�� Rendering loop timer
    DX::StepTimer timer;

	// �L�[�{�[�h Keyboard
	// �X�v���C�g�o�b�` SpriteBatch
	std::unique_ptr<DirectX::SpriteBatch>	spriteBatch;
	// �f�o�b�O�J���� DebugCamera
	//std::unique_ptr<DebugCamera>	camera;
	std::unique_ptr<Camera> camera;
	// �O���b�h�t���A GridFloor
	std::unique_ptr<GridFloor> gridFloor;
	// �t�H���g Font
	std::unique_ptr<DirectX::SpriteFont> font;

	// �G�t�F�N�g�t�@�N�g���C���^�[�t�F�[�X IEffectFactory
	std::unique_ptr<DirectX::EffectFactory> fxFactory;
	// �R�����X�e�[�g CommonStates
	std::unique_ptr<DirectX::CommonStates> commonStates;

	//std::unique_ptr<EffectFactory> effect;

	//std::unique_ptr<GeometricPrimitive> box;

};

#endif	// GAME
