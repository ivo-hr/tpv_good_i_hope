#include "CollisionsSystem.h"
#include "Manager.h"
#include "components/Transform.h"
#include "../utils/Collisions.h"

void CollisionsSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_ROUND_START:
		active_ = true;
		break;
	case _m_ROUND_END:
		active_ = false;
		break;
	default:
		break;
	}
}

void CollisionsSystem::initSystem()
{
}

void CollisionsSystem::update()
{

	if (active_)
	{
		auto& asteroids = mngr_->getEntities(ecs::_grp_ASTEROID);
		auto a = asteroids.size();

		auto& bullets = mngr_->getEntities(ecs::_grp_BULLETS);
		auto b = bullets.size();

		//For each asteroid
		for (auto i = 0u; i < a; i++)
		{
			if (mngr_->isAlive(asteroids[i])) {

				auto astTR = mngr_->getComponent<Transform>(asteroids[i]);

				auto fghtr = mngr_->getHandler(ecs::_hdlr_FGHTR);
				auto fighterTR = mngr_->getComponent<Transform>(fghtr);

				//We check if it collides with the fighter
				if (Collisions::collidesWithRotation(fighterTR->getPos(), fighterTR->getWidth(), fighterTR->getHeight(), fighterTR->getRot(),
					astTR->getPos(), astTR->getWidth(), astTR->getHeight(), astTR->getRot())) {

					Message m;
					m.id = _m_COLLISION_ASTEROIDFIGHTER;
					mngr_->send(m);

					break;

				}


				//We check if a bullet collides with it
				for (auto l = 0u; l < b; l++)
				{
					if (mngr_->isAlive(bullets[l])) {

						auto bullTR = mngr_->getComponent<Transform>(bullets[l]);

						if (Collisions::collidesWithRotation(bullTR->getPos(), bullTR->getWidth(), bullTR->getHeight(), bullTR->getRot(),
							astTR->getPos(), astTR->getWidth(), astTR->getHeight(), astTR->getRot())) {

							Message m;
							m.id = _m_COLLISION_BULLETASTEROID;
							m.collision_bulast_data.a = asteroids[i];
							m.collision_bulast_data.b = bullets[l];

							mngr_->send(m);

						}
					}
				}
			}
		}
	}
}

void CollisionsSystem::onRoundOver()
{
}

void CollisionsSystem::onRoundStart()
{
}
