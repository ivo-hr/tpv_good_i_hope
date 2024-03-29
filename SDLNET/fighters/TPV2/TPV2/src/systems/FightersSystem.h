// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include "../ecs/System.h"

namespace ecs {
class Entity;
}

struct Transform;

class FightersSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_FIGHTERS)

	FightersSystem();
	virtual ~FightersSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;
	void changeFighterTransform(uint8_t side, float x, float y, float rot);
private:
	void handleGameStart(const Message&);
	void handleGameOver(const Message&);
	void handleBulletHitFighter(const Message&);

	Transform *tr0_;
	Transform *tr1_;

	std::array<ecs::Entity*, 2> fighters_;

	bool running_;
};

