#pragma once
#include "Enemy.h"
#include <memory>
#include <SpriteBatch.h>

class Enemy;

/*
 *@State�C���^�[�t�F�C�X��錾����
 */
class AIState
{
public:
	//�������z�֐���錾����
	virtual void Execute(Enemy* enemy) {}
private:
};

