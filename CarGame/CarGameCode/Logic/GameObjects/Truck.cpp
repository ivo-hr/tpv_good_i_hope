#include "Truck.h"
#include "Bullet.h"
#include "../Game.h"

Truck::Truck(Game* game) : BadObject(game)
{
	texture = nullptr;
	w = 120;
	h = 60;
}

Truck::~Truck() {}

void Truck::draw()
{
	drawTexture(game->getTexture(truckTexture));
}

void Truck::update() {
	pos = Point2D<double>(getX() - 5, getY());
}

bool Truck::receiveCarCollision(Car* car)
{
	alive = false;
	car->GetHit(1);
	car->SlowDown(0);
	return true;
}

bool Truck::receiveBulletCollision(Bullet* bullet)
{
	bullet->hasImpacted();
	alive = false;
	return true;
}

