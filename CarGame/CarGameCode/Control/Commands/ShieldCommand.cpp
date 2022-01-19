#include "ShieldCommand.h"
#include "../../Logic/GameObjects/Bullet.h"

bool ShieldCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		bool v = (event.type == SDL_KEYDOWN);
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_m && game->CarCanBuy(cost)) {
			shieldActive = v;
			return true;
		}
	}
	return false;
}


void ShieldCommand::execute()
{
	game->shieldCar(shieldActive);
}
