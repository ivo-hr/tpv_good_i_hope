#include "BlastCommand.h"

void BlastCommand::execute()
{
    if (game->CarCanBuy(cost)) {

        for (Collider* c : game->GetCollisions(new SDL_Rect({ game->GetCarX() + x - range / 2, y - range / 2, range, range })))
        {
            c->blast();
        }
    }
}

bool BlastCommand::parse(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_GetMouseState(&x, &y);
        return true;
    }
    return false;
}
