// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/ecs.h"
#include <vector>

class NetworkSystem;

class Game {
public:
	Game();
	virtual ~Game();
	bool init();
	void start();
private:
	ecs::Manager *mngr_;
	ecs::System *fightersSys_;
	ecs::System *bulletsSys_;
	ecs::System *gameCtrlSys_;
	ecs::System *collisionSys_;
	ecs::System *renderSys_;
	NetworkSystem* netSys_;

};

