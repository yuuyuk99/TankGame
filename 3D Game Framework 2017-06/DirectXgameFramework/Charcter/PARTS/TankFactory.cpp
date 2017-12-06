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
		//HEADオブジェクトを生成する
		tank = make_shared<Turret>();
		break;
	case Tank::ID::PARTS_BODY:
		//Bodyオブジェクトを生成する
		tank = make_shared<Body>();
		break;
	case Tank::ID::PARTS_BULLET:
		//Bulletオブジェクトを生成する
		tank = make_shared<Bullet>();
		break;
	default:
		return nullptr;
	}
	//それぞれのパーツを初期化する
	tank->Initialize();
	return move(tank);
}