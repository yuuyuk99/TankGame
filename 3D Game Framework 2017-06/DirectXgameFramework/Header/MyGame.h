#pragma once
#ifndef MYGAME
#define MYGAME

#include "../Game.h"
#include "../Scene/SceneManager.h"

class Body;
class Bullet;
class Turret;

class MyGame : public Game
{
public:
	// コンストラクタ Constructor
	MyGame(int width, int height);
	// ゲームオブジェクトを初期する Initialize game object
	void Initialize(int width, int height) override;
	// ゲームを更新する Update game
	void Update(const DX::StepTimer& timer) override;
	//画面をクリアする
	//void Clear() override;
	// ゲームシーンを描画する Draws the scene
	void Render(const DX::StepTimer& timer) override;
	// バックバッファをスクリーンに送る
	//void Present() override;
	// 終了処理をおこなう Finalize game
	void Finalize() override;
protected:
	//// プレイヤ Player
	//std::unique_ptr<Player> player;
	//// エネミー Enemy
	//std::unique_ptr<Enemy> enemy;

	//戦車の体
	std::unique_ptr<Model> _body;
	//戦車の砲台
	std::unique_ptr<Model> _turret;
	//戦車の球
	std::unique_ptr<Model> _bullet;
	//カップ
	// モデル Model
	std::unique_ptr<Model> cup;
	// ワールド world
	DirectX::SimpleMath::Matrix world;
	// スケール scale
	float scale;
	//シーン管理
	std::shared_ptr<SceneManager> sceneManager;
	//バックスクリーン
	std::unique_ptr<Model> _backScreen;
};

#endif // MYGAME