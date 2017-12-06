//--------------------------------------------------------------------------------------
// File: DirectXTK.cpp
//
// DirectXTKに関する関数群
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "Direct3D.h"
#include "DirectXTK.h"

using namespace DirectX;

//////////////////////////////////
// リンクするライブラリ指定		//
//////////////////////////////////
#pragma comment(lib, "DirectXTK.lib")

//////////////////////
// 静的変数			//
//////////////////////
//static std::unique_ptr<Keyboard> s_keyboard(new Keyboard);
static std::unique_ptr<Mouse> s_mouse(new Mouse);

//////////////////////
// グローバル変数	//
//////////////////////

// キーボード関係
Keyboard::State g_key;
//std::shared_ptr<Keyboard::KeyboardStateTracker> s_keyTracker(new Keyboard::KeyboardStateTracker);

// マウス関係
Mouse::State g_mouse;
std::shared_ptr<Mouse::ButtonStateTracker> s_mouseTracker(new Mouse::ButtonStateTracker);

// スプライトバッチ
//std::shared_ptr<SpriteBatch> s_spriteBatch;

// スプライトフォント
std::shared_ptr<SpriteFont> s_spriteFont;

// コモンステート
std::shared_ptr<DirectX::CommonStates> s_state;

//--------------------------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------------------------
void DirectXTK_Initialize()
{
	// コモンステートを作成
	s_state.reset(new CommonStates(g_pd3dDevice.Get()));

	// スプライトバッチ
	//s_spriteBatch.reset(new SpriteBatch(g_pImmediateContext.Get()));

	// スプライトフォント
	s_spriteFont.reset(new SpriteFont(g_pd3dDevice.Get(), L"myfile.spritefont"));
}

//--------------------------------------------------------------------------------------
// キー入力やマウス情報の更新
//--------------------------------------------------------------------------------------
void DirectXTK_UpdateInputState()
{
	// キー入力情報を取得
	//g_key = s_keyboard->GetState();
	//s_keyTracker->Update(g_key);

	// マウス情報を取得
	g_mouse = s_mouse->GetState();
	s_mouseTracker->Update(g_mouse);
}

//--------------------------------------------------------------------------------------
// マウスのスクロールフォイール値のリセット関数
//--------------------------------------------------------------------------------------
void DirectXTK_ResetScrollWheelValue()
{
	s_mouse->ResetScrollWheelValue();
}
