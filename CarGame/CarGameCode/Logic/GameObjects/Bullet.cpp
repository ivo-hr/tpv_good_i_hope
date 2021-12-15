#include "Bullet.h"
#include "../Game.h"

Bullet::Bullet(Game* game) : GoodObject(game)
{
	texture = nullptr;
	w = 20;
	h = 5;
}

Bullet::~Bullet() {}

void Bullet::draw()
{
	drawTexture(game->getTexture(bulletTexture));
}

void Bullet::update()
{
	pos = Point2D<double>(getX() + speed, getY());

	vector<Collider*> colisiones = game->GetCollisions(this);

	for (auto e : colisiones) {
		e->receiveBulletCollision(this);
	}
}

void Bullet::hasImpacted()
{
	cout << "ha impactado";
	alive = false;
}
