#pragma once
#include "../ecs/Component.h"

class Transform;

class FighterCtrl: public ecs::Component {
public:

	__CMPID_DECL__(ecs::_FIGHTERCTRL)

	FighterCtrl();
	virtual ~FighterCtrl();
	void initComponent() override;
	void update() override;

private:
	Transform *tr_;
};

