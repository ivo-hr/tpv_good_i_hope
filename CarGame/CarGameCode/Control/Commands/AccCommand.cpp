#include "AccCommand.h"

void AccCommand::execute()
{
    if (bAc && !bDec)
        game->MoveCarX(1);
    else if (bDec && !bAc)
        game->MoveCarX(-1);
    else
        game->MoveCarX(0);
}

bool AccCommand::parse(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        bool v = (event.type == SDL_KEYDOWN);
        SDL_Keycode key = event.key.keysym.sym;
        switch (key) {
        case SDLK_RIGHT:
            bAc = v;
            return true;
        case SDLK_LEFT:
            bDec = v;
            return true;
        default:
            break;
        }
    }
    return false;
}
