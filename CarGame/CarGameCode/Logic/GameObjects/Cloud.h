#ifndef CARGAME_CLOUD_H
#define CARGAME_CLOUD_H

#include "GameObject.h"
#include "GoodObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Cloud : public GoodObject {
private:
	int movement = 5;
public:
	Cloud(Game* game);
	~Cloud();

	void draw();
	void update();
	bool receiveCarCollision(Car* car) override;
};

#endif 