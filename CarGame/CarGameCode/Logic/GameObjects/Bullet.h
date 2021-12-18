#pragma once

#include "GameObject.h"
#include "GoodObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Bullet : public GoodObject {

    int speed = 15;
    int distance = 700;

public:
    Bullet(Game* game);
    ~Bullet();

    void draw() override;
    void update() override;

    void hasImpacted();
};