// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrl.h"

#include <algorithm>
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Image.h"
#include "AsteroidMotion.h"
#include "ShowAtOppositeSide.h"
#include "FramedImage.h"
#include "Transform.h"
#include "State.h"

State::State()
{
}

State::~State()
{
}

void State::initComponent()
{
}

void State::update()
{
}

void State::render()
{
	ecs::States state = mngr_->GetState();

	if (state == ecs::NEWGAME)
	{
		sdlutils().msgs().at("NewGame").render(20, sdlutils().height() - 45);
	}
	else if (state == ecs::RUNNING)
	{
		sdlutils().msgs().at("Running").render(20, sdlutils().height() - 45);
	}
	else if (state == ecs::PAUSED)
	{
		sdlutils().msgs().at("Paused").render(20, sdlutils().height() - 45);
	}
	else if (state == ecs::GAMEOVER)
	{
		sdlutils().msgs().at("GameOver").render(20, sdlutils().height() - 45);
	}

}
