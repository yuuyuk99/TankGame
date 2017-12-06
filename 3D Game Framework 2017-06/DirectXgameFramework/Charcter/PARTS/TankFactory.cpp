#include "TankFactory.h"
#include "Body.h"
#include "Turret.h"
#include "Bullet.h"

using namespace std;

shared_ptr<Tank> TankFactory::Create(Tank::ID id) noexcept
{
	shared_ptr<Tank> tank;
	switch(id)
	{
	case Tank::ID::PARS_TURRET:
		//HEAD�I�u�W�F�N�g�𐶐�����
		tank = make_shared<Turret>();
		break;
	case Tank::ID::PARTS_BODY:
		//Body�I�u�W�F�N�g�𐶐�����
		tank = make_shared<Body>();
		break;
	case Tank::ID::PARTS_BULLET:
		//Bullet�I�u�W�F�N�g�𐶐�����
		tank = make_shared<Bullet>();
		break;
	default:
		return nullptr;
	}
	//���ꂼ��̃p�[�c������������
	tank->Initialize();
	return move(tank);
}