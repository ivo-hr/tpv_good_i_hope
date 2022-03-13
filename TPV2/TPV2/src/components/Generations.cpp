#include "Generations.h"

#include <cassert>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrl.h"
#include "Transform.h"


Generations::Generations(int gennum) :
	gen_(gennum) {
}


Generations::~Generations() {
}


