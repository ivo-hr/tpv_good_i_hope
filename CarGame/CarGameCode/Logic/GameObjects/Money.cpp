#include "Money.h"
#include "../Game.h"

Money::Money(Game* game) : GoodObject(game)
{
	texture = nullptr;
	w = 20;
	h = 20;
}

Money::~Money() {}

void Money::draw()
{
	drawTexture(game->getTexture(moneyTexture));
}

void Money::update() {}

bool Money::receiveCarCollision(Car* car)
{
	alive = false;
	car->AddCoins(1);
	return true;
}
