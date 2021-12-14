#include "PowerUp.h"
#include "../Game.h"

PowerUp::PowerUp(Game* game) : GoodObject(game)
{
	texture = nullptr;
	w = 40;
	h = 40;
}

PowerUp::~PowerUp() {}

void PowerUp::draw()
{
	drawTexture(game->getTexture(coinTexture));
}

void PowerUp::update() {}

bool PowerUp::receiveCarCollision(Car* car)
{
	alive = false;
	car->AddPower();
	return true;
}
