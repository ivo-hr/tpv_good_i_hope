// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class GameCtrlSystem: public ecs::System {
public:

	enum Side : uint8_t {
		LEFT = 0, //
		RIGHT
	};

	enum GameState : uint8_t {
		_NEWGAME = 0,
		_PAUSED,
		_RUNNING,
		_STOPPED
	};

	__SYSID_DECL__(ecs::_sys_GAMECTRL)

	GameCtrlSystem();
	virtual ~GameCtrlSystem();


	void initSystem() override;
	void update() override;
	void recieve(const Message &m) override;

	//void requestToStartRound();
	//void requestToStartGame();
	//void startRound();
	void startGame();
	//void onBallExit(uint8_t side);
	void stopTheGame();

private:
	void handleBulletHitFighter(const Message&);

	uint8_t state_;
};

