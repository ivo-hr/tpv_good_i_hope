#include "FighterSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "Manager.h"
#include "GameCtrlSystem.h"
#include "BulletsSystem.h"
#include "components/Image.h"
#include "components/Transform.h"
#include "../sdlutils/InputHandler.h"

void FighterSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_END:
		onRoundOver();
		break;
	case _m_COLLISION_ASTEROIDFIGHTER:
		onCollision_FighterAsteroid();
		break;
	default:
		break;
	}
}

void FighterSystem::initSystem()
{
	hearts = &sdlutils().images().at("heart");

	auto fghtr = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_FGHTR, fghtr);

	mngr_->addComponent<Image>(fghtr, &sdlutils().images().at("fighter"));

	int width = 50, height = 50;

	fghtrTR = mngr_->addComponent<Transform>(fghtr);

	fghtrTR->init(Vector2D
		(sdlutils().width() / 2 - width / 2, sdlutils().height() / 2 - height / 2 ), { 0, 0 }, width, height, 0);
}

void FighterSystem::update()
{
	auto& pos = fghtrTR->getPos();
	auto& vel_ = fghtrTR->getVel();

	if (mngr_->getSystem<GameCtrlSystem>()->getState() == GameCtrlSystem::RUNNING)
	{
		auto& ihldr = ih();

		if (ihldr.keyDownEvent()) {

			auto rot = fghtrTR->getRot();

			if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT))
			{
				fghtrTR->setRot(rot + 5.0f);
			}
			if (ihldr.isKeyDown(SDL_SCANCODE_LEFT))
			{
				fghtrTR->setRot(rot - 5.0f);
			}
			if (ihldr.isKeyDown(SDL_SCANCODE_UP))
			{

				auto newVel = vel_ + Vector2D(0, -1).rotate(rot) * 0.2f;

				float speed = std::min(newVel.magnitude() + 1.0f, 3.f);

				vel_ = Vector2D(0, -speed).rotate(rot);

				sdlutils().soundEffects().at("thrust").play(0, 1);

			}
			if (ihldr.isKeyDown(SDL_SCANCODE_S))
			{
				Message m;
				m.id = _m_SHOOT;
				m.shoot_data.x = fghtrTR->getPos().getX();
				m.shoot_data.y = fghtrTR->getPos().getY();

				m.shoot_data.velX = fghtrTR->getVel().getX();
				m.shoot_data.velY = fghtrTR->getVel().getY();

				m.shoot_data.width = fghtrTR->getWidth();
				m.shoot_data.height = fghtrTR->getHeight();

				m.shoot_data.rot = fghtrTR->getRot();

				mngr_->getSystem<BulletsSystem>()->receive(m);
			}
		}
	}

	// check left/right borders
	if (pos.getX() < -fghtrTR->getWidth())
	{
		pos.setX(sdlutils().width());
	}
	else if (pos.getX() > sdlutils().width())
	{
		pos.setX(-fghtrTR->getWidth());
	}

	// check upper/lower borders
	if (pos.getY() < -fghtrTR->getHeight())
	{
		pos.setY(sdlutils().height());
	}
	else if (pos.getY() > sdlutils().height())
	{
		pos.setY(-fghtrTR->getHeight());
	}

	vel_ = vel_ * 0.995f;

	if (vel_.magnitude() < 0.05f)
		vel_ = vel_ * 0;


	auto ast = mngr_->getHandler(ecs::_hdlr_FGHTR);

	ast->update();
}

void FighterSystem::onCollision_FighterAsteroid()
{
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	fghtrTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	health--;

	Message m;
	m.id = _m_ROUND_END;
	mngr_->send(m);
}

void FighterSystem::onRoundOver()
{
	active_ = false;
}

void FighterSystem::onRoundStart()
{
	active_ = true;
}
