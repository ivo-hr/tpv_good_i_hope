// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"

class AsteroidManager;

class GameCtrl: public ecs::Component {
public:

	__CMPID_DECL__(ecs::_GAMECTRL)

	GameCtrl(AsteroidManager* ast);
	virtual ~GameCtrl();

	inline void onStarDeath() {
		currNumOfStars_--;
	}

	inline void onStarEaten() {
		currNumOfStars_--;
		score_++;
	}

	void initComponent() override;
	void update() override;
	void render() override;

private:

	AsteroidManager* astman_;

	unsigned int currNumOfStars_;
	unsigned int score_;
	unsigned int starsLimit_;
};

