#include "RenderSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "components/Transform.h"
#include "GameCtrlSystem.h"
#include "Manager.h"

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

void RenderSystem::onRoundStart()
{
}

void RenderSystem::onRoundOver()
{
}

void RenderSystem::onGameStart()
{
}

void RenderSystem::onGameOver()
{
}

void RenderSystem::drawMsgs()
{
}

void RenderSystem::drawAsteroids()
{
}

void RenderSystem::drawFighter()
{
	auto fghtr = mngr_->getHandler(ecs::_hdlr_fighter);
}

void RenderSystem::drawBullets()
{
}

void RenderSystem::drawHealth()
{
}

void RenderSystem::draw(Texture* tx)
{
}
