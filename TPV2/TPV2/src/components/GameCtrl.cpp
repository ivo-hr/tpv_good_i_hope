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
#include "../game/AsteroidManager.h"



GameCtrl::GameCtrl(AsteroidManager* ast) :
		currNumOfStars_(0), //
		score_(0), //
		starsLimit_(30),
		astman_(ast)  {
}

GameCtrl::~GameCtrl() {
}

void GameCtrl::initComponent() {
}

void GameCtrl::update() {
	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_SPACE))
		{
			if (mngr_->GetState() != ecs::RUNNING)
			{
				if (mngr_->GetState() == ecs::NEWGAME)
				{
					mngr_->SetState(ecs::RUNNING);
					astman_->createAsteroids(10);
				}
				else if (mngr_->GetState() == ecs::PAUSED)
				{
					mngr_->SetState(ecs::RUNNING);
					astman_->createAsteroids(10);
				}
				else if (mngr_->GetState() == ecs::GAMEOVER)
				{
					mngr_->SetState(ecs::NEWGAME);
				}
			}
		}
	}
}

void GameCtrl::render() {

}
