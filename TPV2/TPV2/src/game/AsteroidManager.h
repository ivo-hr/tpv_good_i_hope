#pragma once

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"


class AsteroidManager {
public:


		AsteroidManager();
	virtual ~AsteroidManager();

	void onCollision(ecs::Entity* a);

private:
	void createAsteroids(unsigned int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	
	unsigned int asterNum_;
	unsigned int score_;
	unsigned int asterLimit_;

protected:
	ecs::Entity* ent_; // a pointer to the entity, should not be deleted on destruction
	ecs::Manager* mngr_; //  a pointer to the manager, should not be deleted on destruction
};

