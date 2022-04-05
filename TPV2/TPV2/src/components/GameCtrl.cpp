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
#include "../game/AsteroidManager.h"



GameCtrl::GameCtrl(AsteroidManager* ast) :
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
			if (mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>()->GetState() != RUNNING)
			{
				if (mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>()->GetState() == NEWGAME)
				{
					mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>()->SetState(RUNNING);
					astman_->createAsteroids(10);
				}
				else if (mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>()->GetState() == PAUSED)
				{
					mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>()->SetState(RUNNING);
					astman_->createAsteroids(10);
				}
				else if (mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>()->GetState() == GAMEOVER)
				{
					mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>()->SetState(NEWGAME);
				}
			}
		}
	}
}

void GameCtrl::render() {

}
