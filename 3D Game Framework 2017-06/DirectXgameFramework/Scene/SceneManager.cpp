#include "SceneManager.h"
#include "SceneBase.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "ResultScene/ResultScene.h"

/*
 *@�R���X�g���N�^
 */
SceneManager::SceneManager(_SCENE scene) : _nextScene(scene)
{
	
}


SceneManager::~SceneManager()
{
	
}

/*
 *@����������
 */
void SceneManager::Initiaize()
{
	//�V�[���̏�����
	this->_scene->Initialize();
}

/*
 *@�X�V����
 */
void SceneManager::Update()
{
	//�V�[���̕ύX���s��
	Reset();
	//�V�[���̍X�V
	_scene->Update();
}

/*
 *@�`��
 */
void SceneManager::Draw()
{
	//�V�[���̕`����s��
	_scene->Draw();
}

/*
 *@�I������
 */
void SceneManager::Finalize()
{
	_scene->Finalize();
}

/*
 *@�V�[���ڍs���s��
 */
void SceneManager::ChangeScene(_SCENE NextScene)
{
	//�V�[���ֈڍs
	_nextScene = NextScene;
}

/*
 *@�V�[�������Z�b�g����
 */
void SceneManager::Reset()
{
	//�V�[�����I������Ă�����
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
			//�^�C�g���V�[���ֈڍs���܂�
			_scene = std::make_unique<TitleScene>(_sceneManager);
			break;
		case SCENE_PLAY:
			//�v���C�V�[���Ɉڍs���܂�
			_scene = std::make_unique<GameScene>(_sceneManager);
			break;
		case SCENE_RESULT:
			//���U���g�V�[���Ɉڍs���܂�
			_scene = std::make_unique<ResultScene>(_sceneManager);
			break;
		}
		//�V�[�����ڍs���Ȃ��悤�ɂ���
		_nextScene = SCENE_NONE;
		//�V�[���̏�����
		_scene->Initialize();
	}
}

/*
 *@���݂̃V�[�����󂯎��
 */
void SceneManager::SetManager(std::shared_ptr<SceneManager> scene)
{
	_sceneManager = scene;
}
