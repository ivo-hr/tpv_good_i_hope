#include "SuperRock.h"
#include "Bullet.h"
#include "../Game.h"

SuperRock::SuperRock(Game* game) : BadObject(game)
{
	texture = nullptr;
	w = 160;
	h = 80;
}

SuperRock::~SuperRock() {}

void SuperRock::draw()
{
	drawTexture(game->getTexture(rockTexture));
}

bool SuperRock::receiveCarCollision(Car* car)
{
	alive = false;
	car->GetHit(2);
	car->StopTurbo();
	return true;
}

bool SuperRock::receiveBulletCollision(Bullet* bullet)
{
	bullet->hasImpacted();
	return true;
}
