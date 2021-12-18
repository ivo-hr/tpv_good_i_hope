#ifndef CARGAME_BADOBJECT_H
#define CARGAME_BADOBJECT_H

#include "GameObject.h"

class Game;

class BadObject : public GameObject {
protected:
    bool alive;
public:
    static int instances;
    BadObject(Game *game) : GameObject(game) {
        alive = true;
        waveValue = -150;
    };
    
    ~BadObject() override = default;
    void update() override{};



    bool toDelete() override;
    void onEnter() override;
    void onDelete() override;
    void static reset();
};


#endif //CARGAME_BADOBJECT_H
