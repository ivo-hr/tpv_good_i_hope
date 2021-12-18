#pragma once
#include "GameObject.h"
#include "BadObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class SuperRock : public BadObject {


public:

    SuperRock(Game* game);
    ~SuperRock();

    void draw();
    void update() {};
    bool receiveCarCollision(Car* car) override;
    bool receiveBulletCollision(Bullet* bullet) override;
};

