#pragma once
#include "State.h"

class MenuState : public State{

public:
    MenuState(Game *game);
    ~MenuState() =default;

    void update();
    void draw();
    void next();

    string getStateName() const {
        return "Menu state";
    };

};