#pragma once

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"


class AsteroidManager {
public:


		AsteroidManager(ecs::Manager* mngr);	//Class constructor
	virtual ~AsteroidManager();					//class destroyer

	void onCollision(ecs::Entity* a);			//Collision consecuences
	void addAsteroidFrequently();				//Regular asteroid spawner
	void destroyAllAsteroids();					//Asteroids destroyer
	void createAsteroids(unsigned int n);		//Initial asteroids creator

private:
	void createAsteroids(unsigned int n, ecs::Entity* a);	//Division asteroid creator
	
	unsigned int asterNum_;		//Current asteroid number
	unsigned int asterLimit_;	//Max number of  asteroids

	float counter_;				//Time counter since last spawn
	float lastSpawn_;			//Last spawn time

protected:
	ecs::Manager* mngr_;		//Pointer to  current game manager
};
