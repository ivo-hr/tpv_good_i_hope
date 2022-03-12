// This file is part of the course TPV2@UCM - Samir Genaim

#include "Gun.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

Gun::Gun() : fireRate(0.25f)
{
}

Gun::~Gun()
{
}

void Gun::initComponent()
{
	timeLastShot = sdlutils().currRealTime();
}

void Gun::update()
{
	if (timeLastShot + fireRate > sdlutils().currRealTime())
	{
		//Crea la bala
		timeLastShot = sdlutils().currRealTime();
	}
}
