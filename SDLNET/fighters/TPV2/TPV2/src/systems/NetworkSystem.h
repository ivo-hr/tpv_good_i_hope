// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>
#include <string>
#include <array>

#include "../ecs/System.h"
#include "network_messages.h"

struct Transform;

class NetworkSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_NETWORK)

	NetworkSystem();
	virtual ~NetworkSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;

	bool connect();
	void disconnect();

	inline Uint8 getSide() {
		return side_;
	}

	inline bool isReday() {
		return connected_;
	}

	inline bool isHost() {
		return host_;
	}

	inline Uint16 getPort() {
		return port_;
	}

	void sendFighterTransform(Transform *tr);
	void sendBullet(const Message& m);
	void sendStartRoundtRequest();
	void sendStartGameRequest();

	std::string myName = "waiting";
	std::string hostName = "wainting";
	std::array<std::string, 2> names_ = { "waiting", "waiting" };

private:

	bool initHost();
	bool initClient();
	bool initConnection(Uint16 port);

	void handleConnectionRequest(net::Message m);
	void handleFighterPos();
	void handleBullets();
	void handleStartRoundRequest();
	void handleStartTheRound();
	void handleFighterHit();
	void handleDisconnecting();

	void tellOtherClientToStartRound();
	void tellOtherClientToStartGame();
	void tellOtherClientFighterHit(uint8_t hitId_);

	void string_to_chars(std::string& str, char c_str[11]);

	void chars_to_string(std::string& str, char c_str[11]);

	bool host_;
	Uint8 side_; // 0 left 1 right
	UDPsocket sock_;
	UDPpacket *p_;
	SDLNet_SocketSet sockSet_;
	Uint16 port_;

	bool connected_;
	IPaddress otherPlayerAddr_;

};

