#include "HelpCommand.h"

bool HelpCommand::parse(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        if (key == SDLK_h)
            return true;
    }
    return false;


}

void HelpCommand::execute()
{
    game->Help();


}

