#include "RenderSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "components/Transform.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "Entity.h"
#include "FighterSystem.h"
#include "components/FramedImage.h"
#include "components/Image.h"

void RenderSystem::receive(const Message& m)
{
}

void RenderSystem::initSystem()
{
}

void RenderSystem::update()
{
	drawMsgs();
	drawHealth();
	drawAsteroids();
	drawFighter();
	drawBullets();
}

void RenderSystem::drawMsgs()
{
	auto state = mngr_->getSystem<GameCtrlSystem>()->getState();

	if (state != GameCtrlSystem::RUNNING)
	{

		if (state == GameCtrlSystem::GAMEOVER)
		{
			auto& t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
				(sdlutils().height() / 2 + t.height() * 2));
		}

		if (state == GameCtrlSystem::NEWGAME)
		{
			auto& t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width() / 2),
				sdlutils().height() / 2 + t.height() * 2);
		}
	}
}

void RenderSystem::drawAsteroids()
{
	if (mngr_->getSystem<GameCtrlSystem>()->getState() == GameCtrlSystem::RUNNING)
	{
		auto asteroids = mngr_->getEntities(ecs::_grp_ASTEROID);

		for (auto a : asteroids)
		{
			auto trans = mngr_->getComponent<Transform>(a);

			SDL_Rect dest = build_sdlrect(trans->getPos(), trans->getWidth(),
				trans->getHeight());

			auto cut = mngr_->getComponent<FramedImage>(a)->getSrc();

			mngr_->getComponent<FramedImage>(a)->getTexture()->render(*cut, dest,
				trans->getRot(), nullptr, SDL_FLIP_NONE);

		}
	}
}

void RenderSystem::drawFighter()
{
	if (mngr_->getSystem<GameCtrlSystem>()->getState() == GameCtrlSystem::RUNNING)
	{
		auto fghtr = mngr_->getHandler(ecs::_hdlr_FGHTR);
		auto trans = mngr_->getComponent<Transform>(fghtr);

		SDL_Rect dest = build_sdlrect(trans->getPos(), trans->getWidth(), trans->getHeight());

		mngr_->getComponent<Image>(fghtr)->tex_->render(dest, trans->getRot());
	}
}

void RenderSystem::drawBullets()
{
	if (mngr_->getSystem<GameCtrlSystem>()->getState() == GameCtrlSystem::RUNNING)
	{
		auto bullet = mngr_->getEntities(ecs::_grp_BULLETS);

		for (auto a : bullet)
		{
			auto trans = mngr_->getComponent<Transform>(a);

			SDL_Rect dest = build_sdlrect(trans->getPos(), trans->getWidth(),
				trans->getHeight());

			mngr_->getComponent<Image>(a)->tex_->render(dest,
				trans->getRot());

		}
	}
}

void RenderSystem::drawHealth()
{
	auto health = mngr_->getSystem<FighterSystem>()->health;

	for (int i = 0; i < health; i++)
	{
		auto hearts = mngr_->getSystem<FighterSystem>()->getHearts();

		hearts->render({ 10 + i * 50, 10, 50, 50 });
	}
}
