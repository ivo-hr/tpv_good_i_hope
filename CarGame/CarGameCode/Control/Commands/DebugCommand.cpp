#include "DebugCommand.h"

bool DebugCommand::parse(SDL_Event& event) 
{
	if (event.type == SDL_KEYDOWN) 
	{
		SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_e)
			return true;
	}
	return false;
}

void DebugCommand::execute()
{
	game->Debug();
}