#ifndef CARGAME_COIN_H
#define CARGAME_COIN_H

#include "GameObject.h"
#include "GoodObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class PowerUp : public GoodObject {


public:
    PowerUp(Game* game);
    ~PowerUp();

    void draw();
    void update();
    bool receiveCarCollision(Car* car) override;
};



#endif 