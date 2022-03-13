#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;
class AsteroidMotion : public ecs::Component {
public:

	__CMPID_DECL__(ecs::_ASTROMOTION)

		AsteroidMotion();
	virtual ~AsteroidMotion();
	void initComponent() override;
	void update() override;

	void dirSet(float x, float y);

private:
	Transform* tr_;
	Uint32 lastUpdate_;
	Vector2D dir;
};

