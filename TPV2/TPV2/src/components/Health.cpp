// This file is part of the course TPV2@UCM - Samir Genaim

#include "Health.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

Health::Health() : hearts_(), lives(3)
{
}

Health::Health(Texture* heart) : hearts_(heart), lives(3)
{
}

Health::~Health() {
}

void Health::initComponent() {

}

void Health::update() {
}

void Health::render()
{
	for (int i = 0; i < lives; i++)
	{
		hearts_->render({ 10 + i * 50, 10, 50, 50});
	}
}

void Health::takeLive(int amount)
{
	lives -= amount;
	if (lives < 0)
	{
		resetLives();
	}
	sdlutils().soundEffects().at("explosion").play(0, 3);
}

void Health::resetLives()
{
	lives = 3;
}
