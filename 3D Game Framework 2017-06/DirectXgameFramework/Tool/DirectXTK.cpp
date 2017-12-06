//--------------------------------------------------------------------------------------
// File: DirectXTK.cpp
//
// DirectXTK�Ɋւ���֐��Q
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "Direct3D.h"
#include "DirectXTK.h"

using namespace DirectX;

//////////////////////////////////
// �����N���郉�C�u�����w��		//
//////////////////////////////////
#pragma comment(lib, "DirectXTK.lib")

//////////////////////
// �ÓI�ϐ�			//
//////////////////////
//static std::unique_ptr<Keyboard> s_keyboard(new Keyboard);
static std::unique_ptr<Mouse> s_mouse(new Mouse);

//////////////////////
// �O���[�o���ϐ�	//
//////////////////////

// �L�[�{�[�h�֌W
Keyboard::State g_key;
//std::shared_ptr<Keyboard::KeyboardStateTracker> s_keyTracker(new Keyboard::KeyboardStateTracker);

// �}�E�X�֌W
Mouse::State g_mouse;
std::shared_ptr<Mouse::ButtonStateTracker> s_mouseTracker(new Mouse::ButtonStateTracker);

// �X�v���C�g�o�b�`
//std::shared_ptr<SpriteBatch> s_spriteBatch;

// �X�v���C�g�t�H���g
std::shared_ptr<SpriteFont> s_spriteFont;

// �R�����X�e�[�g
std::shared_ptr<DirectX::CommonStates> s_state;

//--------------------------------------------------------------------------------------
// ������
//--------------------------------------------------------------------------------------
void DirectXTK_Initialize()
{
	// �R�����X�e�[�g���쐬
	s_state.reset(new CommonStates(g_pd3dDevice.Get()));

	// �X�v���C�g�o�b�`
	//s_spriteBatch.reset(new SpriteBatch(g_pImmediateContext.Get()));

	// �X�v���C�g�t�H���g
	s_spriteFont.reset(new SpriteFont(g_pd3dDevice.Get(), L"myfile.spritefont"));
}

//--------------------------------------------------------------------------------------
// �L�[���͂�}�E�X���̍X�V
//--------------------------------------------------------------------------------------
void DirectXTK_UpdateInputState()
{
	// �L�[���͏����擾
	//g_key = s_keyboard->GetState();
	//s_keyTracker->Update(g_key);

	// �}�E�X�����擾
	g_mouse = s_mouse->GetState();
	s_mouseTracker->Update(g_mouse);
}

//--------------------------------------------------------------------------------------
// �}�E�X�̃X�N���[���t�H�C�[���l�̃��Z�b�g�֐�
//--------------------------------------------------------------------------------------
void DirectXTK_ResetScrollWheelValue()
{
	s_mouse->ResetScrollWheelValue();
}
