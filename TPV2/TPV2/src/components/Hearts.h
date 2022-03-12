

#pragma once
#include "../ecs/Component.h"

class Texture;


class Hearts : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_PACMANCTRL
	//
	__CMPID_DECL__(ecs::_HEARTS)

	Hearts();
	Hearts(Texture* heart);
	virtual ~Hearts();
	void initComponent() override;
	void update() override;
	void render() override;

	void takeLive(int amount);
	void resetLives();
	int GetLives() { return lives; };

private:
	void createStart();
	Texture* hearts_;
	int lives = 3;
};

