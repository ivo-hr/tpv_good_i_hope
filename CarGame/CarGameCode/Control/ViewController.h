//
// Created by eys on 20/8/21.
//

#ifndef CARGAME_VIEWCONTROLLER_H
#define CARGAME_VIEWCONTROLLER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "CommandFactory.h"
#include "Commands/QuitCommand.h"
#include "Commands/MoveCommand.h"
#include "Commands/AccCommand.h"
#include "Commands/DebugCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/ShootCommand.h"
#include "Commands/WaveCommand.h"


#include "../Logic/Game.h"

const int FRAME_RATE = 30;

enum State { ini, running, fin };

class ViewController {
private:
    Game* game;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    State state;

    CommandFactory* commandFactory;

    void initSDL();
public:
    ViewController(Game* game);

    ~ViewController();

    void run();
    void handleEvents();
    void clearBackground();

    unsigned int frameDuration();
};


#endif //CARGAME_VIEWCONTROLLER_H
