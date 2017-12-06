#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <memory>
#include "../SceneBase.h"
#include "../../Collision/CollisionNode.h"

class Player;
class Enemy;
class Camera;
class Tower;
class Stage;
class BackScreen;

static const int TOWER_NUM = 2;

//@ゲームシーンのクラス
//主にゲームを遊ぶ処理を行います
class GameScene : public SceneBase {
public:
	//コンストラクタ
	GameScene(std::shared_ptr<SceneManager> scene);
	//デストラクタ
	~GameScene();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//終了処理
	void Finalize();
private:
	//プレイヤー
	std::shared_ptr<Player> _Player;
	//エネミー
	std::shared_ptr<Enemy> _Enemy;
	//カメラ
	std::shared_ptr<Camera> _Camera;
	//タワー
	std::shared_ptr<Tower> _Tower[TOWER_NUM];
	//ステージ
	std::shared_ptr<Stage> _stage;
	//背景
	std::shared_ptr<BackScreen> _backScreen;
	//球と球のあたり判定
	bool CollisionSphere2Sphere(const Sphere& obj1, const Sphere& obj2);
	//球とカプセルの当たり判定
	bool CollisionSphere2Capusle(const Sphere& obj1, const Capsule& obj2);
};



