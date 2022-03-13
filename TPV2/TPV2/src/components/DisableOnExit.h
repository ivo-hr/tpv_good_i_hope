#pragma once
#include "../ecs/Component.h"

class Transform;

class DisableOnExit: public ecs::Component {
public:

	__CMPID_DECL__(ecs::_DISABLEEXIT)

		DisableOnExit();
	virtual ~DisableOnExit();
	void initComponent() override;
	void update() override;
private:
	Transform *tr_;
};

