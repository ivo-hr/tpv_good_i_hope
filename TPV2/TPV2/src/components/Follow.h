// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;
class Follow : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_STARMOTION
	//
	__CMPID_DECL__(ecs::_FOLLOW)

		Follow(Transform* fighter);
	virtual ~Follow();
	void initComponent() override;
	void update() override;

private:
	Transform* tr_;
	Transform* fighterTR_;
	Uint32 lastUpdate_;
};

