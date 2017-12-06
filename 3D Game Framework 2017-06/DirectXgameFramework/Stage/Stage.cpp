#include "Stage.h"
#include "../Camera/Camera.h"
#include "../Graphics.h"
#include "Floor.h"
#include "Wall.h"

#include <SimpleMath.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Stage::Stage()
{
	//�n�ʂ̐���
	_floor = make_shared<Floor>();
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for(int j = 0; j < MAP_SIZE_X; j++)
		{
			//�ǂ̐���
			_wall[i][j] = make_shared<Wall>();
		}
	}
	
}

Stage::~Stage()
{

}

/*
 *@����������
 */
void Stage::Initialize()
{
	
	//�n�ʂ̏��������s��
	_floor->Initialize();
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			_wall[i][j]->Initialize();
		}
	}
}

/*
 *@�X�V����
 */
void Stage::Update()
{
	//�s��X�V
	_floor->Update();

	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			if (i < 1 || i > MAP_SIZE_Y - 2 || j < 1 || j >MAP_SIZE_X - 2)
			{
				_wall[i][j]->SetTrans(Vector3((float)j * CHIP_SIZE, 0.0f, (float)i * CHIP_SIZE));
				_wall[i][j]->Update();
			}
		}
	}
}

/*
 *@�`�揈��
 */
void Stage::Draw(shared_ptr<Camera> camera)
{
	Matrix world = Matrix::Identity;
	//����`�������
	_floor->Draw(camera);
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			_wall[i][j]->Draw(camera);
		}
	}
}

/*
 *@�I������
 */
void Stage::Finalize()
{

}

/*
 *@�ǂ̓����蔻����󂯓n��
 */
SphereNode& Stage::GetCollisionNodeWall(int i, int j)
{
	return _wall[i][j]->GetCollisionNode();
}