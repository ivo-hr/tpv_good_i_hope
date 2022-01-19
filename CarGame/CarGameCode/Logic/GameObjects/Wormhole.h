#ifndef CARGAME_WORMHOLE_H
#define CARGAME_WORMHOLE_H

#include "GameObject.h"
#include "GoodObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Wormhole : public GoodObject {

public:
	Wormhole(Game* game);
	~Wormhole();

	void draw();
	void update();
	bool receiveCarCollision(Car* car) override;
};

#endif 