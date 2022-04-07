#pragma once

#include "../../sdlutils/SDLUtils.h"
#include  "../Component.h"


class asteroidTypeGen : public ecs::Component {

public:
	asteroidTypeGen(int generation, int type);
	virtual ~asteroidTypeGen();

	int gen_ = 0;
	int typ_ = 0;
};

