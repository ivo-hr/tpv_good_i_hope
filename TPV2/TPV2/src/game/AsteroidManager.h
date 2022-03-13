#pragma once

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"


class AsteroidManager {
public:


		AsteroidManager(ecs::Manager* mngr);
	virtual ~AsteroidManager();

	void onCollision(ecs::Entity* a);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void createAsteroids(unsigned int n);

private:
	void createAsteroids(unsigned int n, ecs::Entity* a);
	
	unsigned int asterNum_;
	unsigned int score_;
	unsigned int asterLimit_;

	float counter_;
	float lastSpawn_;

protected:
	ecs::Manager* mngr_; //  a pointer to the manager, should not be deleted on destruction
};
