#pragma once

#include "State.h"

class PlayingState : public State
{

	int totalTime, initTime;

public:
	PlayingState(Game* game);
	~PlayingState() = default;

	void update();
	void draw();
	void next();

	string getStateName() const { return "Playing state"; }
};