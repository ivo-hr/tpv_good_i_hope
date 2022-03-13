// This file is part of the course TPV2@UCM - Samir Genaim

#include "Hearts.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

Hearts::Hearts() : lives(3), hearts_()
{
}

Hearts::Hearts(Texture* heart) : lives(3), hearts_(heart)
{
}

Hearts::~Hearts() {
}

void Hearts::initComponent() {

}

void Hearts::update() {
}

void Hearts::render()
{
	for (int i = 0; i < lives; i++)
	{
		hearts_->render({ 10 + i * 50, 10, 50, 50});
	}
}

void Hearts::takeLive(int amount)
{
	lives -= amount;
	if (lives < 0)
	{
		resetLives();
	}
	sdlutils().soundEffects().at("explosion").play(0, 3);
}

void Hearts::resetLives()
{
	lives = 3;
}
