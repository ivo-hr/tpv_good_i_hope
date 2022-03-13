
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

//Method  initialization  and constructor
AsteroidManager::AsteroidManager(ecs::Manager* mngr) :
	asterNum_(0), 
	asterLimit_(30), 
	counter_(1000.f),
	mngr_(mngr)  {
	lastSpawn_ = sdlutils().currRealTime();
}

//Destructor
AsteroidManager::~AsteroidManager() {
}


//Asteroid deletion on collision
void AsteroidManager::onCollision(ecs::Entity* a)
{
	//Kill asteroid
	a->setAlive(false);

	//Less asteroids in-game
	asterNum_--;

	//Next asteroid generation spawn
	if (a->getComponent<Generations>()->getGen() > 0)
	{
		createAsteroids(2, a);
	}
}

//Initial asteroids creation
void AsteroidManager::createAsteroids(unsigned int n) {

	//If not yet max  asteroids
	if (asterNum_ < asterLimit_)
	{
		//Create asteroids until maxed out
		for (auto i = 0u; i < n; i++) {

			auto& rand = sdlutils().rand();			//Random number generator

			//Entity creation and integration to group
			auto e = mngr_->addEntity();
			e->addToGroup(ecs::_grp_ASTEROIDS);

			auto tr = e->addComponent<Transform>();	//Current asteroid Transform

			//Size and generation
			auto s = rand.nextInt(0, 3);			

			e->addComponent<Generations>(s);

			if (s == 0)			s = 20;
			else if (s == 1)	s = 40;
			else				s = 80;

			//Starting position
			auto x = rand.nextInt(-s, sdlutils().width() + s);
			auto y = rand.nextInt(-s, sdlutils().height() + s);

			//Direction point
			auto cx = rand.nextInt(sdlutils().width() / 2 - 100, sdlutils().width() / 2 + 100);
			auto cy = rand.nextInt(sdlutils().height() / 2 - 100, sdlutils().height() / 2 + 100);

			//Translation of starting position outside view, randomized  axis priority
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

			
			tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);	//Initialization of the asteroid


			auto sp = rand.nextInt(1, 5) / 10.0f;				//Speed of  the asteroid

			//Asteroid type maker

			//Asteroid that follows
			if (rand.nextInt(0, 10) < 3)
			{
				e->addComponent<Follow>(mngr_->getHandler(ecs::_hdlr_FIGHTER)->getComponent<Transform>());	//Following  component
				e->addComponent<FramedImage>(&sdlutils().images().at("asteroid_g"));						//Image
			}

			//Normal asteroid
			else
			{
				e->addComponent<FramedImage>(&sdlutils().images().at("asteroid"));							//Image

				//Asteroid direction
				auto dirX = ((cx - x) / 100) * sp;
				auto dirY = ((cy - y) / 100) * sp;

				e->addComponent<AsteroidMotion>();															//Moving component
				e->getComponent<AsteroidMotion>()->dirSet(dirX, dirY);										//Direction setter
			}

			e->addComponent<ShowAtOppositeSide>();															//Toroidal movement component

			asterNum_++;																					//Current asteroid increase
		}
	}
}

//Regular asteroid spawner
void AsteroidManager::addAsteroidFrequently()
{
	//If time  passed and in appropiate game state
	if (mngr_->GetState() == ecs::RUNNING && 
		lastSpawn_ + counter_ < sdlutils().currRealTime())
	{
		createAsteroids(1);
		//Timer reset
		lastSpawn_ = sdlutils().currRealTime();
	}
}

//Asteroid destroyer
void AsteroidManager::destroyAllAsteroids()
{
	auto& asteroids = mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS);		//Asteroid group

	auto n = asteroids.size();												//Group size

	//Kill every asteroid in group
	for (auto k = 0u; k < n; k++)
	{
		asteroids[k]->setAlive(false);
	}
	asterNum_ = 0;															//Reset current asteroids number
}

//generational asteroid creation
void AsteroidManager::createAsteroids(unsigned int n, ecs::Entity* a)
{
	//If not reached max asteroids yet
	if (asterNum_ < asterLimit_)
	{
		//Create asteroids until indicated	(everything same as initial asteroid creation)
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

			
				tr->init(a->getComponent<Transform>()->getPos(), Vector2D(), s, s, 0.0f);		//!CHANGE! Spawning position of old asteroid

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
