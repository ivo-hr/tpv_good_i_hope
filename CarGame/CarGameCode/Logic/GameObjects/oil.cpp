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

void Oil::update() {
	if (!colliding && slowed) {
		recoverSpeed(kar);
		slowed = false;
	}


	colliding = false;

}

bool Oil::receiveCarCollision(Car* car)
{
	kar = car;

	colliding = true;
	
	if (!slowed) {
		car->SlowDown(car->getSpeed() * 0.7);
		slowed = true;
	}
	
	
	return true;
}

void Oil::recoverSpeed(Car* car)
{
	car->SlowDown(car->getSpeed() * 10 / 7);
}
