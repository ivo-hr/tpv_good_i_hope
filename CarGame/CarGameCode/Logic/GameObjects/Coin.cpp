#include "Coin.h"
#include "../Game.h"

Coin::Coin(Game* game) : GoodObject(game)
{
	texture = nullptr;
	w = 40;
	h = 40;
}

Coin::~Coin() {}

void Coin::draw()
{
	drawTexture(game->getTexture(coinTexture));
}

void Coin::update() {}

bool Coin::receiveCarCollision(Car* car)
{
	alive = false;
	car->AddPower();
	return true;
}
