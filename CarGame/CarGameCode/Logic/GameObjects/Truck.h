#ifndef CARGAME_TRUCK_H
#define CARGAME_TRUCK_H

#include "GameObject.h"
#include "BadObject.h"

class Truck;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Truck : public BadObject {


public:

	Truck(Game* game);
	~Truck();

	void draw();
	void update() ;
	bool receiveCarCollision(Car* car) override;
	bool receiveBulletCollision(Bullet* bullet) override;
};

#endif 