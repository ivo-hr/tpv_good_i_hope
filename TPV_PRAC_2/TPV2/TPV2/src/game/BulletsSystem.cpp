#include "BulletsSystem.h"
#include "Entity.h"
#include "../utils/Vector2D.h"
#include "Manager.h"
#include "GameCtrlSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "components/Image.h"
#include "components/Transform.h"

void BulletsSystem::receive(const Message& m)
{
}

void BulletsSystem::initSystem()
{
	timeLastShot = 0;
	fireRate = 0.25f;
}

void BulletsSystem::update()
{
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, float rot)
{
	if (timeLastShot + fireRate < sdlutils().currRealTime())
	{
		auto bullet = mngr_->addEntity(ecs::_grp_BULLETS);


		auto tr = mngr_->addComponent<Transform>(bullet);

		tr->init(pos, vel, width, height, rot);

		mngr_->addComponent<Image>(bullet, &sdlutils().images().at("bullet"));

		sdlutils().soundEffects().at("fire").play(0, 1);
		timeLastShot = sdlutils().currRealTime();
	}
}

void BulletsSystem::onCollision_BulletAsteroid(ecs::Entity* b)
{
	mngr_->setAlive(b, false);
}

void BulletsSystem::onRoundOver()
{
	active_ = false;
}

void BulletsSystem::onRoundStart()
{
	active_ = true;
}
