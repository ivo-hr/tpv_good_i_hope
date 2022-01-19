#include "Wormhole.h"
#include "../Game.h"

Wormhole::Wormhole(Game* game) : GoodObject(game)
{
	texture = nullptr;
	w = 60;
	h = 60;
}

Wormhole::~Wormhole() {}

void Wormhole::draw()
{
	drawTexture(game->getTexture(wormholeTexture));
}

void Wormhole::update() {}

bool Wormhole::receiveCarCollision(Car* car)
{
	alive = false;
	if (!car->teleporting) {
		car->telePort(500);
	}

	else car->teleporting = false;
	
	return true;
}
