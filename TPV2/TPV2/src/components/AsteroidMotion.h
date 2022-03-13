// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;
class AsteroidMotion : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_STARMOTION
	//
	__CMPID_DECL__(ecs::_ASTROMOTION)

		AsteroidMotion();
	virtual ~AsteroidMotion();
	void dirSet(float x, float y);
	void initComponent() override;
	void update() override;

	


private:
	Transform* tr_;
	Uint32 lastUpdate_;
	Vector2D dir;
};

