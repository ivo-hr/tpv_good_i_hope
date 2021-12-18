#include "oil.h"
#include "Bullet.h"
#include "../Game.h"

Oil::Oil(Game* game) : BadObject(game)
{
	texture = nullptr;
	w = 50;
	h = 50;
}

Oil::~Oil() {}

void Oil::draw()
{
	drawTexture(game->getTexture(oilTexture));
}

void Oil::update() {}

bool Oil::receiveCarCollision(Car* car)
{
	car->SlowDown(2);
	return true;
}

/*bool Oil::receiveBulletCollision(Bullet* bullet)
{
	bullet->hasImpacted();
	alive = false;
	return true;
}*/
