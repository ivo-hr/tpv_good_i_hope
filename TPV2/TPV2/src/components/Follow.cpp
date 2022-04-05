#include "Follow.h"

#include <cassert>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrl.h"
#include "Transform.h"


Follow::Follow(Transform* fighter) :
	tr_(), fighterTR_(fighter), lastUpdate_() {
}


Follow::~Follow() {
}

void Follow::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);

	lastUpdate_ = sdlutils().currRealTime();

	tr_->getVel() = Vector2D(1, 1);
}

void Follow::update() {

	// update every 50ms
	if (lastUpdate_ + 50 > sdlutils().currRealTime())
		return;

	auto v = tr_->getVel();
	auto p = tr_->getPos();
	auto q = fighterTR_->getPos();

	lastUpdate_ = sdlutils().currRealTime();

	//Calculate in which direction the asteroid should turn
	tr_->getVel() = v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);

}

