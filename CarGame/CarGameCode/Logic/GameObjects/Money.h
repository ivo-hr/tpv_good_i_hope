#ifndef CARGAME_MONEY_H
#define CARGAME_MONEY_H

#include "GameObject.h"
#include "GoodObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Money : public GoodObject {


public:
    Money(Game* game);
    ~Money();

    void draw();
    void update();
    bool receiveCarCollision(Car* car) override;
};

#endif 