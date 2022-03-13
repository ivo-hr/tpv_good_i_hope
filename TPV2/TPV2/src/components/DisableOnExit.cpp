#include "DisableOnExit.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

DisableOnExit::DisableOnExit() :
		tr_() {
}

DisableOnExit::~DisableOnExit() {
}

void DisableOnExit::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DisableOnExit::update() {
	auto &pos = tr_->getPos();

	// check left/right borders
	if (pos.getX() < -tr_->getWidth() || 
		pos.getX() > sdlutils().width() || 
		pos.getY() < -tr_->getHeight() ||
		pos.getY() > sdlutils().height())
	{
		ent_->setAlive(false);
	}
}
