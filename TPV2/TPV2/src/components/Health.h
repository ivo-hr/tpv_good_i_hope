

#pragma once
#include "../ecs/Component.h"

class Texture;


class Health : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_PACMANCTRL
	//
	__CMPID_DECL__(ecs::_HEARTS)

	Health();
	Health(Texture* heart);
	virtual ~Health();
	void initComponent() override;
	void update() override;
	void render() override;

	void takeLive(int amount);
	void resetLives();
	int GetLives() { return lives; };

private:
	Texture* hearts_;
	int lives = 3;
};

