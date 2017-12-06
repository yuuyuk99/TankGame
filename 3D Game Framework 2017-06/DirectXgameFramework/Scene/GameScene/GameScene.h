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

//@�Q�[���V�[���̃N���X
//��ɃQ�[����V�ԏ������s���܂�
class GameScene : public SceneBase {
public:
	//�R���X�g���N�^
	GameScene(std::shared_ptr<SceneManager> scene);
	//�f�X�g���N�^
	~GameScene();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�I������
	void Finalize();
private:
	//�v���C���[
	std::shared_ptr<Player> _Player;
	//�G�l�~�[
	std::shared_ptr<Enemy> _Enemy;
	//�J����
	std::shared_ptr<Camera> _Camera;
	//�^���[
	std::shared_ptr<Tower> _Tower[TOWER_NUM];
	//�X�e�[�W
	std::shared_ptr<Stage> _stage;
	//�w�i
	std::shared_ptr<BackScreen> _backScreen;
	//���Ƌ��̂����蔻��
	bool CollisionSphere2Sphere(const Sphere& obj1, const Sphere& obj2);
	//���ƃJ�v�Z���̓����蔻��
	bool CollisionSphere2Capusle(const Sphere& obj1, const Capsule& obj2);
};



