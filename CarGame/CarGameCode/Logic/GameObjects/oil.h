#ifndef CARGAME_OIL_H
#define CARGAME_OIL_H

#include "GameObject.h"
#include "BadObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Oil : public BadObject {


public:

	Oil(Game* game);
	~Oil();

	void draw();
	void update();
	bool receiveCarCollision(Car* car) override;
	//bool receiveBulletCollision(Bullet* bullet) override;
};

#endif 