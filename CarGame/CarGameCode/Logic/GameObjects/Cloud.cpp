#include "Cloud.h"
#include "../Game.h"

Cloud::Cloud(Game* game) : GoodObject(game)
{
	texture = nullptr;
	w = 40;
	h = 60;
}

Cloud::~Cloud() {}

void Cloud::draw()
{
	drawTexture(game->getTexture(cloudTexture));
}

void Cloud::update() {

	if (getY() < 50) {
		movement = + 5;
	}
	else if (getY() > game->getWindowHeight() - 50) {
		movement = -5;
	}

	pos = Point2D<double>(getX(), getY() + movement);
}

bool Cloud::receiveCarCollision(Car* car)
{
	car->AddCoins(1);
	return true;
}
