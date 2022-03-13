#include "Gun.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "Image.h"
#include "Transform.h"

Gun::Gun() : fireRate(250.f)
{
}

Gun::~Gun()
{
}

void Gun::initComponent()
{
	timeLastShot = sdlutils().currRealTime();
}

void Gun::update()
{
	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_S)) {

			if (timeLastShot + fireRate < sdlutils().currRealTime())
			{
				auto entTr = ent_->getComponent<Transform>();

				auto bullet = mngr_->addEntity();
				auto tr = bullet->addComponent<Transform>();

				auto p = entTr->getPos();
				auto vel = entTr->getVel();
				auto r = entTr->getRot();
				auto w = entTr->getWidth();
				auto h = entTr->getHeight();

				tr->init(p + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r) - Vector2D(2.0f, 10.0f),
					Vector2D(0.0f, -1.0f).rotate(r) * (vel.magnitude() + 5.0f),
					5.f, 
					20.f, 
					ent_->getComponent<Transform>()->getRot());

				bullet->addComponent<Image>(&sdlutils().images().at("bullet"));

				//Crea la bala
				sdlutils().soundEffects().at("fire").play(0, 1);
				timeLastShot = sdlutils().currRealTime();
			}
		}
	}
}
