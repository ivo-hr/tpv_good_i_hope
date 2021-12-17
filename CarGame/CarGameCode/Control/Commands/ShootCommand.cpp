#include "ShootCommand.h"
#include "../../Logic/GameObjects/Bullet.h"

bool ShootCommand::parse(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        if (key == SDLK_s)
            return true;
    }
    return false;
}

void ShootCommand::execute()
{
    if (game->CarCanBuy(cost)) {
        Bullet* bulet = new Bullet(game);
        bulet->setPosition(game->GetCarX(), game->GetCarY());
        game->addObject(bulet);
    }
}
