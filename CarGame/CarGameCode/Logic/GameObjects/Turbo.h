#pragma once

#include "GameObject.h"
#include "GoodObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Turbo : public GoodObject {


public:
    Turbo(Game* game);
    ~Turbo();

    void draw();
    void update();
    bool receiveCarCollision(Car* car) override;
};


