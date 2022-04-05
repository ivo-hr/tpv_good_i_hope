// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"

enum States
{
	NEWGAME,
	RUNNING,
	PAUSED,
	GAMEOVER
};

class State: public ecs::Component {

protected:

	States currentState_;

public:

	__CMPID_DECL__(ecs::_STATE)

		State();
	virtual ~State();

	void initComponent() override;
	void update() override;
	void render() override;

	States GetState() { return currentState_; };
	void SetState(States newState) { currentState_ = newState; };

};

