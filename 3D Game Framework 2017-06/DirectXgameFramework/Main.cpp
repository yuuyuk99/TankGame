// DirectX Game Framework 0.92 
// 2017/05/05　Added Japanese comment
// 2017/05/08  Added Graphics singleton class
// 2017/05/13  Added Window class
// 2017/05/20  Functioning WinMain function
// 2017/05/25  Change global Game object to local Game object
// 2017/05/25  Create Window object inside Game object

#include "pch.h"
#include "Game.h"
#include "Window.h"

#include "Header/MyGame.h"

using namespace DirectX;
using namespace std;


// エントリポイント Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;
	// COMライブラリを初期化する
    if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
        return 1;

	// ウィンドウ幅
	int width = 800;
	// ウィンドウ高
	int height = 600;
	// MyGameオブジェクトを生成する
	MyGame myGame(width, height);
	// ゲームを実行する
	MSG msg = myGame.Run();

	// Comライブラリを終了処理する
    CoUninitialize();
    return (int) msg.wParam;
}
