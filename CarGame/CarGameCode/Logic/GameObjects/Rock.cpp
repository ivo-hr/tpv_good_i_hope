#include "Rock.h"
#include "Bullet.h"
#include "../Game.h"
Rock::Rock(Game* game) : BadObject(game)
{
	texture = nullptr;
	w = 50;
	h = 50;
}

Rock::~Rock() {}

void Rock::draw()
{
	drawTexture(game->getTexture(rockTexture));
}

void Rock::update() {}

bool Rock::receiveCarCollision(Car* car)
{
	alive = false;
	car->GetHit();
	return true;
}

bool Rock::receiveBulletCollision(Bullet* bullet)
{
	cout << "bala ha chocado" << endl;
	bullet->hasImpacted();
	alive = false;
	return true;
}
