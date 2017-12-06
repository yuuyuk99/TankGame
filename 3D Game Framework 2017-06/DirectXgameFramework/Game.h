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

// D3D11デバイスを生成し、ゲームループを提供する基本ゲーム実装
// A basic game implementation that creates a D3D11 device and provides a game loop.
class Game
{
public:
	// 基本ゲームループを実行する Run basic game loop
	MSG Run();

	// コンストラクタ Constructor
    Game(int width, int height);
    // 初期化と管理 Initialization and management
    virtual void Initialize(int width, int height);
    // 基本ゲームループ Basic game loop
	virtual void Update(const DX::StepTimer& timer);
	// 画面をクリアする Clear screen
	virtual void Clear();
	// シーンを描画する Render scene
	virtual void Render(const DX::StepTimer& timer);
	// バックバッファをスクリーンに送る
    virtual void Present();
	// 終了処理
	virtual void Finalize();

    // メッセージ Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // プロパティ Properties
    void GetDefaultSize(int& width, int& height) const;

	
	// FPSを描画する Draw FPS
	//void DrawFPS();

	static std::unique_ptr<DirectX::Keyboard> keyboard;
private:
	HINSTANCE hInstance;
	int nCmdShow;
    // デバイスリソース Device resources.
    HWND hWnd;
	// 出力幅 Output width
    int width;
	// 出力高 Output height
    int height;

	// ウィンドウ Window
	std::unique_ptr<Window> window;
	// グラフィックス Graphics
	std::unique_ptr<Graphics> graphics;
	// 機能レベル Feature level
    D3D_FEATURE_LEVEL featureLevel;

protected:
    // ループタイマーを描画する Rendering loop timer
    DX::StepTimer timer;

	// キーボード Keyboard
	// スプライトバッチ SpriteBatch
	std::unique_ptr<DirectX::SpriteBatch>	spriteBatch;
	// デバッグカメラ DebugCamera
	//std::unique_ptr<DebugCamera>	camera;
	std::unique_ptr<Camera> camera;
	// グリッドフロア GridFloor
	std::unique_ptr<GridFloor> gridFloor;
	// フォント Font
	std::unique_ptr<DirectX::SpriteFont> font;

	// エフェクトファクトリインターフェース IEffectFactory
	std::unique_ptr<DirectX::EffectFactory> fxFactory;
	// コモンステート CommonStates
	std::unique_ptr<DirectX::CommonStates> commonStates;

	//std::unique_ptr<EffectFactory> effect;

	//std::unique_ptr<GeometricPrimitive> box;

};

#endif	// GAME
