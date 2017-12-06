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
	// �R���X�g���N�^ Constructor
	MyGame(int width, int height);
	// �Q�[���I�u�W�F�N�g���������� Initialize game object
	void Initialize(int width, int height) override;
	// �Q�[�����X�V���� Update game
	void Update(const DX::StepTimer& timer) override;
	//��ʂ��N���A����
	//void Clear() override;
	// �Q�[���V�[����`�悷�� Draws the scene
	void Render(const DX::StepTimer& timer) override;
	// �o�b�N�o�b�t�@���X�N���[���ɑ���
	//void Present() override;
	// �I�������������Ȃ� Finalize game
	void Finalize() override;
protected:
	//// �v���C�� Player
	//std::unique_ptr<Player> player;
	//// �G�l�~�[ Enemy
	//std::unique_ptr<Enemy> enemy;

	//��Ԃ̑�
	std::unique_ptr<Model> _body;
	//��Ԃ̖C��
	std::unique_ptr<Model> _turret;
	//��Ԃ̋�
	std::unique_ptr<Model> _bullet;
	//�J�b�v
	// ���f�� Model
	std::unique_ptr<Model> cup;
	// ���[���h world
	DirectX::SimpleMath::Matrix world;
	// �X�P�[�� scale
	float scale;
	//�V�[���Ǘ�
	std::shared_ptr<SceneManager> sceneManager;
	//�o�b�N�X�N���[��
	std::unique_ptr<Model> _backScreen;
};

#endif // MYGAME