#ifndef CARGAME_GOODOBJECT_H
#define CARGAME_GOODOBJECT_H

#include "GameObject.h"

class Game;

class GoodObject : public GameObject {
protected:
    bool alive;
public:
    static int instances;
    GoodObject(Game* game) : GameObject(game) {
        alive = true;
    };

    ~GoodObject() override = default;
    void update() override{};

    bool toDelete() override;
    void onEnter() override;
    void onDelete() override;
    void static reset();
};


#endif //CARGAME_GOODOBJECT_H
