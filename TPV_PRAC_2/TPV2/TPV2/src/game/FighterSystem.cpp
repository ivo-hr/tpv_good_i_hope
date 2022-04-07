#include "FighterSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "Manager.h"
#include "GameCtrlSystem.h"
#include "components/Image.h"
#include "components/Transform.h"
#include "../sdlutils/InputHandler.h"

void FighterSystem::receive(const Message& m)
{
}

void FighterSystem::initSystem()
{
	hearts = &sdlutils().images().at("heart");

	auto fghtr = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_FGHTR, fghtr);

	mngr_->addComponent<Image>(fghtr, &sdlutils().images().at("fighter"));

	int width = 40, height = 40;

	fghtrTR = mngr_->addComponent<Transform>(fghtr);

	fghtrTR->init({ sdlutils().width() / 2 - width / 2, sdlutils().height() / 2 - height / 2 }, { 0, 0 }, width, height, 0);
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
}

void FighterSystem::onCollision_FighterAsteroid()
{
	health--;
}

void FighterSystem::onRoundOver()
{
}

void FighterSystem::onRoundStart()
{
}
