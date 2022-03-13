// This file is part of the course TPV2@UCM - Samir Genaim

#include "DeAcceleration.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"

#include "Transform.h"

DeAcceleration::DeAcceleration() : tr_(nullptr) {
}

DeAcceleration::~DeAcceleration() {
}

void DeAcceleration::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DeAcceleration::update() {

	auto& vel_ = tr_->getVel();
	vel_ = vel_ * 0.995f;

	if (vel_.magnitude() < 0.05f)
		vel_ = vel_ * 0;

}
