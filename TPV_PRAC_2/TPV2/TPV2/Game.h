#pragma once

#include "src/ecs/ecs.h"

class ecs::Manager;
class System;

class Game {
public:

    Game();
    virtual ~Game();

    void init();

    void start();

private:

    ecs::Manager* mngr;

    ecs::System* collSys;
    ecs::System* renderSys;
    ecs::System* fghtrSys;
    ecs::System* bulletsSys;
    ecs::System* asteroidsSys;
    ecs::System* gameCtrlSys;
};