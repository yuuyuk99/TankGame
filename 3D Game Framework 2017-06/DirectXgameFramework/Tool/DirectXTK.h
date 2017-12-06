//--------------------------------------------------------------------------------------
// File: DirectXTK.h
//
// DirectXTKに関する関数群
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
// 関数のプロトタイプ宣言	//
//////////////////////////////
void DirectXTK_Initialize();
void DirectXTK_UpdateInputState();
void DirectXTK_ResetScrollWheelValue();

//////////////////////////////
// グローバル変数			//
//////////////////////////////

// キーボード関係
//extern DirectX::Keyboard::State g_key;
//extern std::shared_ptr<DirectX::Keyboard::KeyboardStateTracker> s_keyTracker;

// マウス関係
extern DirectX::Mouse::State g_mouse;
extern std::shared_ptr<DirectX::Mouse::ButtonStateTracker> s_mouseTracker;

// コモンステート
extern std::shared_ptr<DirectX::CommonStates> s_state;

// スプライトバッチ
extern std::shared_ptr<DirectX::SpriteBatch> s_spriteBatch;

// スプライトフォント
extern std::shared_ptr<DirectX::SpriteFont> s_spriteFont;


