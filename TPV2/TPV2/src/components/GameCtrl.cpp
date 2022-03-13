// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrl.h"

#include <algorithm>
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Image.h"
#include "StarMotion.h"
#include "AsteroidMotion.h"
#include "ShowAtOppositeSide.h"
#include "FramedImage.h"
#include "Transform.h"



GameCtrl::GameCtrl() :
		currNumOfStars_(0), //
		score_(0), //
		starsLimit_(30) {
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
					createStart(std::min(5u, starsLimit_ - currNumOfStars_));
				}
				else if (mngr_->GetState() == ecs::PAUSED)
				{
					mngr_->SetState(ecs::RUNNING);
					createStart(std::min(5u, starsLimit_ - currNumOfStars_));
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

void GameCtrl::createStart(unsigned int n) {

	for (auto i = 0u; i < n; i++) {
		// Always use the random number generator provided by SDLUtils
		//
		auto &rand = sdlutils().rand();

		// add and entity to the manager
		//
		auto e = mngr_->addEntity();
		e->addToGroup(ecs::_grp_ASTEROIDS);

		// add a Transform component, and initialise it with random
		// size and position
		//
		auto tr = e->addComponent<Transform>();
		auto s = rand.nextInt(50, 100);//size

		auto x = rand.nextInt(-s, sdlutils().width() + s);
		auto y = rand.nextInt(-s, sdlutils().height() + s);

		auto cx = rand.nextInt(sdlutils().width()/2 - 100, sdlutils().width()/2 + 100);
		auto cy = rand.nextInt(sdlutils().height()/2 - 100, sdlutils().height()/2 + 100);


		if (rand.nextInt(0, 2) == 0) {

			if (y < sdlutils().height() && y > 0)
			{
				if (rand.nextInt(0, 2) == 0) {
					x = -s;
				}
				else x = sdlutils().width() + s;
			}

			else if (x < sdlutils().width() && x > 0)
			{
				if (rand.nextInt(0, 2) == 0) {
					y = -s;
				}
				else y = sdlutils().height() + s;
			}
		}
		else {

			if (x < sdlutils().width() && x > 0)
			{
				if (rand.nextInt(0, 2) == 0) {
					y = -s;
				}
				else y = sdlutils().height() + s;
			}

			else if (y < sdlutils().height() && y > 0)
			{
				if (rand.nextInt(0, 2) == 0) {
					x = -s;
				}
				else x = sdlutils().width() + s;
			}

			
		}
		

		tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);


		auto sp = rand.nextInt(1, 10)/10.0f;

		auto dirX = ((cx - x)/100) * sp;
		auto dirY = ((cy - y) / 100) * sp;
		
		
		// add an Image Component
		//
		e->addComponent<FramedImage>(&sdlutils().images().at("asteroid"));

		// add a StarMotion component to resize/rotare the star
		//
		//e->addComponent<StarMotion>();
		e->addComponent<AsteroidMotion>();
		e->addComponent<ShowAtOppositeSide>();
		e->getComponent<AsteroidMotion>()->dirSet(dirX, dirY);
		currNumOfStars_++;
	}
}
