

#include "FighterCtrl.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() :
		tr_(nullptr) {
}

FighterCtrl::~FighterCtrl() {
}

void FighterCtrl::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void FighterCtrl::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		auto &vel_ = tr_->getVel();
		auto rot = tr_->getRot();

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT))
		{
			tr_->setRot(rot + 5.0f);
		} 
		if (ihldr.isKeyDown(SDL_SCANCODE_LEFT))
		{
			tr_->setRot(rot - 5.0f);
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
