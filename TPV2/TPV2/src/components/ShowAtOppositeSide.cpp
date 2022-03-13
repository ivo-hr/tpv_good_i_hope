// This file is part of the course TPV2@UCM - Samir Genaim

#include "ShowAtOppositeSide.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

ShowAtOppositeSide::ShowAtOppositeSide() :
		tr_() {
}

ShowAtOppositeSide::~ShowAtOppositeSide() {
}

void ShowAtOppositeSide::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update() {
	auto &pos = tr_->getPos();

	// check left/right borders
	if (pos.getX() < -tr_->getWidth()) 
	{
		pos.setX(sdlutils().width());
	} 
	else if (pos.getX() > sdlutils().width()) 
	{
		pos.setX(-tr_->getWidth());
	}

	// check upper/lower borders
	if (pos.getY() < -tr_->getHeight())
	{
		pos.setY(sdlutils().height());
	} 
	else if (pos.getY() > sdlutils().height())
	{
		pos.setY(-tr_->getHeight());
	}
}
