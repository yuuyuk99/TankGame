//--------------------------------------------------------------------------------------
// File: DirectXTK.h
//
// DirectXTK�Ɋւ���֐��Q
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <SpriteFont.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <CommonStates.h>

//////////////////////////////
// �֐��̃v���g�^�C�v�錾	//
//////////////////////////////
void DirectXTK_Initialize();
void DirectXTK_UpdateInputState();
void DirectXTK_ResetScrollWheelValue();

//////////////////////////////
// �O���[�o���ϐ�			//
//////////////////////////////

// �L�[�{�[�h�֌W
//extern DirectX::Keyboard::State g_key;
//extern std::shared_ptr<DirectX::Keyboard::KeyboardStateTracker> s_keyTracker;

// �}�E�X�֌W
extern DirectX::Mouse::State g_mouse;
extern std::shared_ptr<DirectX::Mouse::ButtonStateTracker> s_mouseTracker;

// �R�����X�e�[�g
extern std::shared_ptr<DirectX::CommonStates> s_state;

// �X�v���C�g�o�b�`
extern std::shared_ptr<DirectX::SpriteBatch> s_spriteBatch;

// �X�v���C�g�t�H���g
extern std::shared_ptr<DirectX::SpriteFont> s_spriteFont;


