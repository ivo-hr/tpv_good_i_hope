#include "Coin.h"
#include "../Game.h"

Coin::Coin(Game* game) : GoodObject(game)
{
	texture = nullptr;
	w = 20;
	h = 20;
}

Coin::~Coin() {}

void Coin::draw()
{
	drawTexture(game->getTexture(moneyTexture));
}

void Coin::update() {}

bool Coin::receiveCarCollision(Car* car)
{
	alive = false;
	car->AddCoins(1);
	return true;
}
