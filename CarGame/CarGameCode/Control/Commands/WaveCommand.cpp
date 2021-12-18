#include "WaveCommand.h"

bool WaveCommand::parse(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_w)
			return true;
	}
	return false;
}

void WaveCommand::execute()
{
	if (game->CarCanBuy(cost)) {
		game->getContainer()->waveObjects();
	}
}