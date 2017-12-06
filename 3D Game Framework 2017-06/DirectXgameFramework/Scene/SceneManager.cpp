#include "SceneManager.h"
#include "SceneBase.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "ResultScene/ResultScene.h"

/*
 *@コンストラクタ
 */
SceneManager::SceneManager(_SCENE scene) : _nextScene(scene)
{
	
}


SceneManager::~SceneManager()
{
	
}

/*
 *@初期化処理
 */
void SceneManager::Initiaize()
{
	//シーンの初期化
	this->_scene->Initialize();
}

/*
 *@更新処理
 */
void SceneManager::Update()
{
	//シーンの変更を行う
	Reset();
	//シーンの更新
	_scene->Update();
}

/*
 *@描画
 */
void SceneManager::Draw()
{
	//シーンの描画を行う
	_scene->Draw();
}

/*
 *@終了処理
 */
void SceneManager::Finalize()
{
	_scene->Finalize();
}

/*
 *@シーン移行を行う
 */
void SceneManager::ChangeScene(_SCENE NextScene)
{
	//シーンへ移行
	_nextScene = NextScene;
}

/*
 *@シーンをリセットする
 */
void SceneManager::Reset()
{
	//シーンが選択されていたら
	if (_nextScene != SCENE_NONE)
	{
		if (_scene)
		{
			_scene->Finalize();
			_scene.reset();
		}

		switch (_nextScene)
		{
		case SCENE_TITLE:
			//タイトルシーンへ移行します
			_scene = std::make_unique<TitleScene>(_sceneManager);
			break;
		case SCENE_PLAY:
			//プレイシーンに移行します
			_scene = std::make_unique<GameScene>(_sceneManager);
			break;
		case SCENE_RESULT:
			//リザルトシーンに移行します
			_scene = std::make_unique<ResultScene>(_sceneManager);
			break;
		}
		//シーンを移行しないようにする
		_nextScene = SCENE_NONE;
		//シーンの初期化
		_scene->Initialize();
	}
}

/*
 *@現在のシーンを受け取る
 */
void SceneManager::SetManager(std::shared_ptr<SceneManager> scene)
{
	_sceneManager = scene;
}
