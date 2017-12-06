#include "GameScene.h"
#include "../SceneManager.h"
#include "../../Charcter/Player/Player.h"
#include "../../Charcter/Enemy/Enemy.h"
#include <Effects.h>
#include "../../Camera/Camera.h"
#include "../../Collision/CollisionNode.h"
#include "../../Tower/Tower.h"
#include "../../Stage/Stage.h"
#include "../../BackScreen/BackScreen.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/*
 *@�R���X�g���N�^
 */
GameScene::GameScene(shared_ptr<SceneManager> scene) : SceneBase(scene)
{
	//�v���C���[�I�u�W�F�N�g�𐶐�����
	this->_Player = make_shared<Player>();
	//�G�I�u�W�F�N�g�𐶐�����
	this->_Enemy = make_shared<Enemy>();
	//�J����������
	this->_Camera = make_shared<Camera>();
	//�X�e�[�W
	this->_stage = make_shared<Stage>();
	//�w�i
	this->_backScreen = make_shared<BackScreen>();
}
	
/*
 *@�f�X�g���N�^
 */
GameScene::~GameScene()
{

}

/*
 *@GameScene�̏������������s��
 */
void GameScene::Initialize()
{
	//�v���C���[�̏�����
	this->_Player->Initialize();

	//�G�̏�����
	this->_Enemy->Initialize();
	//�G�Ƀv���C���[�̏�����������
	this->_Enemy->SetPlayer(this->_Player);
	//�^���[�̏����ݒ�
	//0 = PlayerTower, 1 = EnemyTower
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//�^���[�I�u�W�F�N�g�𐶐�����
		this->_Tower[i] = make_shared<Tower>();
		//�^���[�̏�����
		this->_Tower[i]->Initialize();
	}
	//�^���[�̏����ʒu�̐ݒ�
	_Tower[0]->SetTrans(Vector3(7.5f, 0.0f, 5.0f));
	_Tower[1]->SetTrans(Vector3(7.5f, 0.0f, 25.0f));
	//�v���C���[�̓��Ɍ����킹�邽�߂Ƀv���C���[���̃^���[�̏����󂯓n��
	this->_Enemy->SetTower(this->_Tower[0]);

	//�X�e�[�W�̏�����
	this->_stage->Initialize();
	//�V���̏�����
	this->_backScreen->Initialize();
}

/*
 *@GameScene�̍X�V�������s��
 */
void GameScene::Update()
{
	Vector3 old_trans = this->_Player->GetTrans();

	//�v���C���[�̍X�V
	this->_Player->Update();
	//�G�l�~�[�̍X�V
	this->_Enemy->Update();
	/*
	 *�J�����̐ݒ�
	 */
	{
		//�J��������
		const float CAMERA_DISTANCE = -5.0f;
		//���_�A�Q�Ɠ_
		Vector3 eyepos, refpos;
		//�^�[�Q�b�g�̍��W�͎��@�̍��W�ɒǏ]
		refpos = this->_Player->GetTrans() + Vector3(0.0f, 2.0f, 0.0f);
		//�^�[�Q�b�g�̍��W����J�������W�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
		//�J�����̎��������̋t������]
		Matrix rotmat = Matrix::CreateRotationY(_Player->GetRot().y);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		//�J�������W���v�Z
		eyepos = refpos + cameraV;
		//�J�����ɏ����Z�b�g
		_Camera->SetEyepos(eyepos);
		_Camera->SetRefpos(refpos);

	}

	//�J�����̍X�V
	this->_Camera->Update();

	//�^���[�̍X�V
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//�^���[�̍X�V
		this->_Tower[i]->Update();
	}

	//�X�e�[�W�̍X�V
	this->_stage->Update();

	//�����蔻��
	if (CollisionSphere2Sphere(this->_Player->GetCollisionNodeBody(), this->_Enemy->GetCollisionnodeBody()))
	{
		//�e�X�g�p
		int i = 0;
	}

	for (int i = 0; i < TOWER_NUM; i++)
	{
		//�f�o�b�O�p
		//�^���[�Ƃ̓����蔻��
		//if (CollisionSphere2Capusle(this->_Player->GetCollisionNodeBody(), this->_Tower[i]->GetCollsionNode()))
		//{
		//	//�^���[�̑ϋv�x�����炷
		//	_Tower[i]->SetHealth(_Tower[i]->GetHealth() - 1);
		//}

		//�^���[�Ƃ̓����蔻��
		if (CollisionSphere2Capusle(this->_Player->GetCollisionNodeBullet(), this->_Tower[i]->GetCollsionNode()))
		{
			//�^���[�̑ϋv�x�����炷
			this->_Tower[i]->SetHealth(_Tower[i]->GetHealth() - 1);
		}
	}

	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			//�v���C���[��Body�ƃX�e�[�W�̕ǂƂ̏Փ˔���
			if (CollisionSphere2Sphere(this->_Player->GetCollisionNodeBody(), this->_stage->GetCollisionNodeWall(i, j)))
			{
				//�v���C���[������ȏ�i�߂Ȃ��悤�ɂ���
				this->_Player->SetTrans(old_trans);
			}
		}
	}
	
	
	//�ǂ��炩�̃^���[�̑ϋv�x���Ȃ��Ȃ�����
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//�ǂ��炩�̃^���[�̑ϋv�x���O�ɂȂ����Ƃ�
		if (this->_Tower[i]->GetHealth() <= 0)
		{
			//���U���g�V�[���ֈڍs����
			m_SceneChanger._Get()->ChangeScene(SCENE_RESULT);
		}
	}

	//�w�i�̍X�V
	this->_backScreen->Update();
}

/*
 *@GameScene�̕`�揈�����s��
 */
void GameScene::Draw()
{
	//�X�e�[�W�̕`��
	this->_stage->Draw(_Camera);
	//�v���C���[�̕`����s��
	this->_Player->Draw(_Camera);
	//�G�l�~�[�̕`����s��
	this->_Enemy->Draw(_Camera);
	//�^���[�̕`��
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//�^���[�̕`����s��
		this->_Tower[i]->Draw(_Camera);
	}
	//�w�i�̕`��
	this->_backScreen->Draw(_Camera);
}

/*
 *@GameScene�̌㏈�����s��
 */
void GameScene::Finalize()
{
	//�v���C���[�̏I������
	this->_Player->Finalize();
	//�G�̏I������
	this->_Enemy->Finalize();
	//�^���[�̏I������
	for (int i = 0; i < TOWER_NUM; i++)
	{
		//�^���[�̏I������
		this->_Tower[i]->Finalize();
	}
	
}

/*
 *@���Ƌ��̓����蔻����s��
 *@�߂�l true�@�Փ˂��Ă���
 *             false   �Փ˂��Ă��Ȃ�
 */
bool GameScene::CollisionSphere2Sphere(const Sphere& obj1, const Sphere& obj2)
{
	//�Փ˓_�̍��W������ϐ�
	Vector3 inter;
	//���Ƌ��̏Փ˔���
	if (CheckSphere2Sphere(obj1, obj2, &inter))
	{
		return true;
	}
	return false;
}

/*
 *@�J�v�Z���Ƌ��̓����蔻����s��
 *@�߂�l true�@�Փ˂��Ă���
 *              false  �Փ˂��Ă��Ȃ�
 */
bool GameScene::CollisionSphere2Capusle(const Sphere& obj1, const Capsule& obj2)
{
	//�Փ˓_�̍��W������ϐ�
	Vector3 inter;
	//�J�v�Z���Ƌ��̏Փ˔���
	if (CheckSphere2Capsule(obj1, obj2, &inter))
	{
		return true;
	}
	return false;
}
