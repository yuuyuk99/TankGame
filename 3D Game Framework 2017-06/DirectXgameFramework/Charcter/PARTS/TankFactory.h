#pragma once

#include <Windows.h>
#include "../Tank.h"
class TankFactory
{
public:
	std::shared_ptr<Tank> Create(Tank::ID id) noexcept;
};