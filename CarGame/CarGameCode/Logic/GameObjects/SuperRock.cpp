#include "SuperRock.h"
#include "Bullet.h"
#include "../Game.h"

SuperRock::SuperRock(Game* game) : BadObject(game)
{
	texture = nullptr;
	w = 70;
	h = 70;
}

SuperRock::~SuperRock() {}

void SuperRock::draw()
{
	drawTexture(game->getTexture(rockTexture));
}

bool SuperRock::receiveCarCollision(Car* car)
{
	car->Stop();
	return true;
}

bool SuperRock::receiveBulletCollision(Bullet* bullet)
{
	bullet->hasImpacted();
	return true;
}
