//Enrique Juan Gamboa
//Javier Enrique Villegas Montelongo

#include "Game.h"

#include "../components/GameCtrl.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/Hearts.h"
#include "../components/Gun.h"
#include "../components/State.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "AsteroidManager.h"

using ecs::Entity;
using ecs::Manager;

Game::Game() :
		mngr_(nullptr) {
}

Game::~Game() {
	delete mngr_;
	delete astermngr_;
}

void Game::init() {

	SDLUtils::init("Demo", 800, 600, "resources/config/resources.json");

	mngr_ = new Manager();
	astermngr_ = new AsteroidManager(mngr_);


	auto fighter = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_FIGHTER, fighter);
	auto tr = fighter->addComponent<Transform>();
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	fighter->addComponent<Image>(&sdlutils().images().at("fighter"));
	fighter->addComponent<FighterCtrl>();
	fighter->addComponent<ShowAtOppositeSide>();
	fighter->addComponent<DeAcceleration>();
	fighter->addComponent<Hearts>(&sdlutils().images().at("heart"));
	fighter->addComponent<Gun>();


	auto &asteroids = mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS);
	auto n = asteroids.size();
	for (auto i = 0u; i < n; i++) {
		auto e = asteroids[i];
		if (e->isAlive()) {

			auto eTR = e->getComponent<Transform>();
		}
	}
	
	auto ginfo = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_GAMEINFO, ginfo);
	ginfo->addComponent<GameCtrl>(astermngr_);
	ginfo->addComponent<State>();
}

void Game::start() {

	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		astermngr_->addAsteroidFrequently();
		checkCollisions();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Game::checkCollisions() {

	auto fighterTR = mngr_->getHandler(ecs::_hdlr_FIGHTER)->getComponent<Transform>();
	auto& asteroids = mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS);

	auto n = asteroids.size();
	for (auto i = 0u; i < n; i++)
	{
		if (asteroids[i]->isAlive()) {

			auto astTR = asteroids[i]->getComponent<Transform>();

			if (Collisions::collidesWithRotation(fighterTR->getPos(), fighterTR->getWidth(), fighterTR->getHeight(), fighterTR->getRot(),
				astTR->getPos(), astTR->getWidth(), astTR->getHeight(), astTR->getRot())) {

				mngr_->getHandler(ecs::_hdlr_FIGHTER)->getComponent<Hearts>()->takeLive(1);

				auto& bullets = mngr_->getEntitiesByGroup(ecs::_grp_BULLETS);
				auto a = bullets.size();

				for (auto j = 0u; j < a; j++)
				{
					bullets[j]->setAlive(false);
				}

				if (mngr_->getHandler(ecs::_hdlr_FIGHTER)->getComponent<Hearts>()->GetLives() == 0)
				{
					mngr_->SetState(ecs::GAMEOVER);
					mngr_->getHandler(ecs::_hdlr_FIGHTER)->getComponent<Hearts>()->resetLives();
				}
				else
				{
					mngr_->SetState(ecs::PAUSED);
				}

				astermngr_->destroyAllAsteroids();

				auto s = 50.0f;
				auto x = (sdlutils().width() - s) / 2.0f;
				auto y = (sdlutils().height() - s) / 2.0f;
				fighterTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

				break;

			}

			auto& bullets = mngr_->getEntitiesByGroup(ecs::_grp_BULLETS);
			auto a = bullets.size();

			for (auto l = 0u; l < a; l++)
			{
				if (bullets[l]->isAlive()) {

					auto bullTR = bullets[l]->getComponent<Transform>();

					if (Collisions::collidesWithRotation(bullTR->getPos(), bullTR->getWidth(), bullTR->getHeight(), bullTR->getRot(),
						astTR->getPos(), astTR->getWidth(), astTR->getHeight(), astTR->getRot())) {

						bullets[l]->setAlive(false);

						astermngr_->onCollision(asteroids[i]);

					}
				}
			}
		}
	}
}