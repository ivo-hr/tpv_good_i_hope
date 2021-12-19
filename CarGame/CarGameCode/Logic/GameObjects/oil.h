#ifndef CARGAME_OIL_H
#define CARGAME_OIL_H

#include "GameObject.h"
#include "BadObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Oil : public BadObject {

protected:
	bool slowed = false;
	bool colliding = false;
	Car* kar;
public:

	Oil(Game* game);
	~Oil();

	void draw();
	void update();
	bool receiveCarCollision(Car* car) override;
	void recoverSpeed(Car* car);
};

#endif 