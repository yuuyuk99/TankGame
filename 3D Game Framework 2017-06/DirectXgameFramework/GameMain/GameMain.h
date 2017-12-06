#pragma once

#ifndef  GAMEMAIN
#define GAMEMAIN

#include "../Framework/Game.h"
#include "../Scene/SceneManager.h"

class GameMain : public Game {
public:
	//コンストラクタ
	GameMain(int width, int height);
	//ゲームオブジェクトを初期化する
	void Initialize() override;
	//ゲームを更新する
	void Update(DX::StepTimer const& timer) override;
	//ゲームシーンを描画
	void Draw(DX::StepTimer const& timer) override;
	//終了処理を行う
	void Finalize() override;
protected:
	shared_ptr<SceneManager> sceneManager;
};

#endif // GAMEMAIN
