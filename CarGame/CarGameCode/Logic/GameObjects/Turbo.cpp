#include "Turbo.h"
#include "../Game.h"

Turbo::Turbo(Game* game) : GoodObject(game)
{
	texture = nullptr;
	w = 80;
	h = 40;
}

Turbo::~Turbo() {}

void Turbo::draw()
{
	drawTexture(game->getTexture(turboTexture));
}

void Turbo::update() {}

bool Turbo::receiveCarCollision(Car* car)
{
	car->ActivateTurbo();
	return true;
}
