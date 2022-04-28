#pragma once

#include "../sdlutils/SDLUtils.h"
#include  "../game/Component.h"


class asteroidTypeGen : public ecs::Component {

public:

	constexpr static ecs::cmpId_type id = ecs::_ASTER_TYPE;

	asteroidTypeGen(int generation, int type);
	virtual ~asteroidTypeGen();

	int gen_ = 0;
	int typ_ = 0;
};

