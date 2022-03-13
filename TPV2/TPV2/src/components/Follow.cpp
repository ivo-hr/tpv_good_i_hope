#include "Follow.h"

#include <cassert>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrl.h"
#include "Transform.h"


Follow::Follow() :
	tr_(), lastUpdate_() {
}


Follow::~Follow() {
}

void Follow::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);

	lastUpdate_ = sdlutils().currRealTime();
}

void Follow::update() {

	// update every 50ms
	if (lastUpdate_ + 50 > sdlutils().currRealTime())
		return;

	lastUpdate_ = sdlutils().currRealTime();

	tr_->getVel() = dir;

}

void Follow::dirSet(float x, float y)
{
	dir = new Vector2D(x, y);
}


