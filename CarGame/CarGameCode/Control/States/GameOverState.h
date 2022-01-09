#pragma once
#include "State.h"

class GameOverState : public State{

public:
    GameOverState(Game *game);
    ~GameOverState() =default;

    void update();
    void draw();
    void next();

    string getStateName() const {
        return "Game Over state";
    };

};