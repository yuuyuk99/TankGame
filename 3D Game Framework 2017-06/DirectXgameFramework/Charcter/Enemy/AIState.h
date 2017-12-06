#pragma once
#include "Enemy.h"
#include <memory>
#include <SpriteBatch.h>

class Enemy;

/*
 *@Stateインターフェイスを宣言する
 */
class AIState
{
public:
	//純粋仮想関数を宣言する
	virtual void Execute(Enemy* enemy) {}
private:
};

