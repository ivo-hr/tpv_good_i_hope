
#include "AsteroidManager.h"

#include <algorithm>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../components/AsteroidMotion.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/Follow.h"
#include "../components/Generations.h"

AsteroidManager::AsteroidManager(ecs::Manager* mngr) :
	asterNum_(0), 
	score_(0), 
	asterLimit_(30), 
	counter_(1000.f),
	mngr_(mngr)  {
	lastSpawn_ = sdlutils().currRealTime();
}

AsteroidManager::~AsteroidManager() {
}



void AsteroidManager::onCollision(ecs::Entity* a)
{
	a->setAlive(false);
	asterNum_--;
	if (a->getComponent<Generations>()->getGen() > 0)
	{
		createAsteroids(2, a);
	}
}


void AsteroidManager::createAsteroids(unsigned int n) {

	if (asterNum_ < asterLimit_)
	{

		for (auto i = 0u; i < n; i++) {

			auto& rand = sdlutils().rand();

			auto e = mngr_->addEntity();
			e->addToGroup(ecs::_grp_ASTEROIDS);

			auto tr = e->addComponent<Transform>();
			auto s = rand.nextInt(0, 3);

			e->addComponent<Generations>(s);

			if (s == 0)			s = 20;
			else if (s == 1)	s = 40;
			else				s = 80;

			auto x = rand.nextInt(-s, sdlutils().width() + s);
			auto y = rand.nextInt(-s, sdlutils().height() + s);

			auto cx = rand.nextInt(sdlutils().width() / 2 - 100, sdlutils().width() / 2 + 100);
			auto cy = rand.nextInt(sdlutils().height() / 2 - 100, sdlutils().height() / 2 + 100);


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


			auto sp = rand.nextInt(1, 5) / 10.0f;

			if (rand.nextInt(0, 10) < 3)
			{
				e->addComponent<Follow>(mngr_->getHandler(ecs::_hdlr_FIGHTER)->getComponent<Transform>());
				e->addComponent<FramedImage>(&sdlutils().images().at("asteroid_g"));
			}
			else
			{
				e->addComponent<FramedImage>(&sdlutils().images().at("asteroid"));

				auto dirX = ((cx - x) / 100) * sp;
				auto dirY = ((cy - y) / 100) * sp;

				e->addComponent<AsteroidMotion>();
				e->getComponent<AsteroidMotion>()->dirSet(dirX, dirY);
			}

			e->addComponent<ShowAtOppositeSide>();

			asterNum_++;
		}
	}
}

void AsteroidManager::addAsteroidFrequently()
{
	if (mngr_->GetState() == ecs::RUNNING && 
		lastSpawn_ + counter_ < sdlutils().currRealTime())
	{
		createAsteroids(1);
		lastSpawn_ = sdlutils().currRealTime();
	}
}

void AsteroidManager::destroyAllAsteroids()
{
	auto& asteroids = mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS);

	auto n = asteroids.size();

	for (auto k = 0u; k < n; k++)
	{
		asteroids[k]->setAlive(false);
	}
	asterNum_ = 0;
}

void AsteroidManager::createAsteroids(unsigned int n, ecs::Entity* a)
{
	if (asterNum_ < asterLimit_)
	{

		for (auto i = 0u; i < n; i++) {

			auto& rand = sdlutils().rand();

			auto e = mngr_->addEntity();
			e->addToGroup(ecs::_grp_ASTEROIDS);

			auto tr = e->addComponent<Transform>();
			auto s = a->getComponent<Generations>()->getGen() - 1;

			e->addComponent<Generations>(s);

			if (s == 0)			s = 20;
			else if (s == 1)	s = 40;
			else				s = 80;

			auto cx = rand.nextInt(0, sdlutils().width());
			auto cy = rand.nextInt(0, sdlutils().height());


			tr->init(a->getComponent<Transform>()->getPos(), Vector2D(), s, s, 0.0f);

			auto sp = rand.nextInt(1, 5) / 10.0f;

			if (rand.nextInt(0, 10) < 3)
			{
				e->addComponent<Follow>(mngr_->getHandler(ecs::_hdlr_FIGHTER)->getComponent<Transform>());
				e->addComponent<FramedImage>(&sdlutils().images().at("asteroid_g"));
			}
			else
			{
				e->addComponent<FramedImage>(&sdlutils().images().at("asteroid"));

				auto dirX = ((cx - a->getComponent<Transform>()->getPos().getX()) / 100) * sp;
				auto dirY = ((cy - a->getComponent<Transform>()->getPos().getY()) / 100) * sp;

				e->addComponent<AsteroidMotion>();
				e->getComponent<AsteroidMotion>()->dirSet(dirX, dirY);
			}

			e->addComponent<ShowAtOppositeSide>();

			asterNum_++;
		}
	}
}
