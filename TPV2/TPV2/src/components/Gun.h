

#pragma once
#include "../ecs/Component.h"

class Transform;

class Gun : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_PACMANCTRL
	//
	__CMPID_DECL__(ecs::_GUN)

		Gun();
	virtual ~Gun();
	void initComponent() override;
	void update() override;

private:
	void createStart();
	float fireRate;
	float timeLastShot;
};

