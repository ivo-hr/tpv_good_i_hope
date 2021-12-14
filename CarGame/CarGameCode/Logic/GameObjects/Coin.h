#ifndef CARGAME_MONEY_H
#define CARGAME_MONEY_H

#include "GameObject.h"
#include "GoodObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Coin : public GoodObject {

public:
    Coin(Game* game);
    ~Coin();

    void draw();
    void update();
    bool receiveCarCollision(Car* car) override;
};

#endif 