#include "BulletsSystem.h"
#include "Entity.h"
#include "../utils/Vector2D.h"
#include "Manager.h"
#include "GameCtrlSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "components/Image.h"
#include "components/Transform.h"

void BulletsSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_SHOOT:
		shoot({ m.shoot_data.x, m.shoot_data.y }, 
			{ m.shoot_data.velX, m.shoot_data.velY }, 
			m.shoot_data.width, 
			m.shoot_data.height, 
			m.shoot_data.rot);
		break;
	case _m_COLLISION_BULLETASTEROID:
		onCollision_BulletAsteroid(m.collision_bulast_data.b);
		break;
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_END:
		onRoundOver();
		break;
	default:
		break;
	}
}

void BulletsSystem::initSystem()
{
	timeLastShot = 0;
	fireRate = 0.25f;
}

void BulletsSystem::update()
{
	auto& bull = mngr_->getEntities(ecs::_grp_BULLETS);
	int n = bull.size();

	for (int i = 0; i < n; i++) {
		bull[i]->update();

		auto bullT = mngr_->getComponent<Transform>(bull[i]);

		if (bullT->getPos().getX() > sdlutils().width()) {
			mngr_->setAlive(bull[i], false);
		}
		else if (bullT->getPos().getX() + bullT->getHeight() < 0) {
			mngr_->setAlive(bull[i], false);
		}
		else if (bullT->getPos().getY() > sdlutils().height()) {
			mngr_->setAlive(bull[i], false);
		}
		else if (bullT->getPos().getY() + bullT->getWidth() < 0) {
			mngr_->setAlive(bull[i], false);
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, float rot)
{
	if (timeLastShot + fireRate < sdlutils().currRealTime())
	{
		auto bullet = mngr_->addEntity(ecs::_grp_BULLETS);

		auto tr = mngr_->addComponent<Transform>(bullet);

		tr->init(pos + Vector2D(width / 2.0f, height / 2.0f) - Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate(rot) - Vector2D(2.0f, 10.0f),
			Vector2D(0.0f, -1.0f).rotate(rot) * (vel.magnitude() + 5.0f),
			5.f,
			20.f,
			rot);

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

	auto& bullEnt = mngr_->getEntities(ecs::_grp_BULLETS);
	for (int i = 0; i < bullEnt.size(); i++) {
		mngr_->setAlive(bullEnt[i], false);
	}
}

void BulletsSystem::onRoundStart()
{
	active_ = true;
}
