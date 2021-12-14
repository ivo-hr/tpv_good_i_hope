#ifndef CARGAME_FINLINE_H
#define CARGAME_FINLINE_H

#include "GameObject.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class FinLine : public GameObject {

public:
    FinLine(Game* game);
    ~FinLine();

    void draw();
    void update();
};

#endif 