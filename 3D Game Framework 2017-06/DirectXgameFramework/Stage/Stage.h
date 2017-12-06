#pragma once
#include <memory>
#include <CommonStates.h>
#include <Effects.h>
#include "../Base/ObjectBase.h"
#include "../Collision/CollisionNode.h"
#include "Wall.h"

//�}�b�v�̉��̃T�C�Y
const int MAP_SIZE_X = 15;
//�}�b�v�̏c�̃T�C�Y
const int MAP_SIZE_Y = 30;

//�`�b�v�T�C�Y
const int CHIP_SIZE = 1;

//�ǂ̐�
const int WALL_NUM = MAP_SIZE_X * MAP_SIZE_Y;

class Camera;
class Floor;
class Wall;

class Stage
{
public:
	enum STAGE
	{
		GLASS,
		WALL,

		NUM_LAND
	};
	//�R���X�g���N�^
	Stage();
	//�f�X�g���N�^
	~Stage();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw(std::shared_ptr<Camera> camera);
	//�I������
	void Finalize();
	//XY���W���w�肷��ƁA���̈ʒu�̏���Ԃ�
	int GetMapData(int x, int y) { return _LandMap[y][x]; }
	//�ǂ̓����蔻����󂯓n��
	SphereNode& GetCollisionNodeWall(int i, int j);
private:
	//�n��
	std::shared_ptr<Floor> _floor;
	//��
	std::shared_ptr<Wall> _wall[MAP_SIZE_Y][MAP_SIZE_X];
	//�X�e�[�W
	int _LandMap[MAP_SIZE_Y][MAP_SIZE_X];
};
