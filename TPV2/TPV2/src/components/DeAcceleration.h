
#pragma once
#include "../ecs/Component.h"

class Transform;

class DeAcceleration : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_PACMANCTRL
	//
	__CMPID_DECL__(ecs::_DEACC)

		DeAcceleration();
	virtual ~DeAcceleration();
	void initComponent() override;
	void update() override;

private:
	void createStart();
	Transform* tr_;
};

