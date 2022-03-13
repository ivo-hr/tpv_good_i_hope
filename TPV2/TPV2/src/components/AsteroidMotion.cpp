#include "AsteroidMotion.h"

#include <cassert>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrl.h"
#include "Transform.h"


AsteroidMotion::AsteroidMotion() :
	tr_(), lastUpdate_() {
}

void AsteroidMotion::dirSet(float x, float y)
{
	dir = new Vector2D(x, y);
}

AsteroidMotion::~AsteroidMotion() {
}

void AsteroidMotion::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);

	lastUpdate_ = sdlutils().currRealTime();
}

void AsteroidMotion::update() {

	// update every 50ms
	if (lastUpdate_ + 50 > sdlutils().currRealTime())
		return;

	lastUpdate_ = sdlutils().currRealTime();

	tr_->getVel() = dir;

}


