#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;
class Follow : public ecs::Component {
public:

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

