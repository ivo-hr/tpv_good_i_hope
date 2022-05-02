// This file is part of the course TPV2@UCM - Samir Genaim

#include "NetworkSystem.h"

#include <iostream>

#include "../components/Transform.h"
#include "../components/FighterInfo.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"
#include "FightersSystem.h"
#include "BulletsSystem.h"
#include "GameCtrlSystem.h"
#include "network_messages.h"
//#include "PaddlesSystem.h"

NetworkSystem::NetworkSystem() :
	host_(false), //
	side_(0), //
	sock_(), //
	p_(), //
	sockSet_(), //
	port_(), //
	connected_(false), //
	otherPlayerAddr_() {

}

NetworkSystem::~NetworkSystem() {
	if (p_ != nullptr) {
		SDLNet_UDP_Close(sock_);
		SDLNet_FreePacket(p_);
	}
}

void NetworkSystem::recieve(const Message& m) {
	if (!host_)
		return;

	switch (m.id) {
	case _m_ROUND_START:
		tellOtherClientToStartRound();
		break;
	case _m_NEW_GAME:
		tellOtherClientToStartGame();
		break;
	case _m_BULLET_HIT_FIGHTER:
		tellOtherClientFighterHit(
			static_cast<GameCtrlSystem::Side>(
				mngr_->getComponent<FighterInfo>(m.bullet_hit.fighter_)->id_));
		break;
	default:
		break;
	}
}

void NetworkSystem::initSystem() {
}

bool NetworkSystem::connect() {

	char choice;
	bool done = false;
	bool success = false;

	std::cout << "Whats your name? ";
	std::cin >> myName;
	std::cout << std::endl;
	std::cout << std::endl;

	while (!done) {
		std::cout << "Do you want to be host, client or exit [h/c/e]? "
			<< std::endl;
		std::cin >> choice;
		switch (choice) {
		case 'h':
		case 'H':
			success = initHost();
			done = true;
			break;
		case 'c':
		case 'C':
			success = initClient();
			done = true;
			break;
		case 'e':
		case 'E':
			done = true;
			break;
		default:
			break;
		}
	}

	return success;
}

void NetworkSystem::disconnect() {
	if (!connected_)
		return;

	net::Message m;

	m.id = net::_DISCONNECTING;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_);

}

void NetworkSystem::update() {
	net::Message m;
	while (SDLNetUtils::deserializedReceive(m, p_, sock_) > 0) {
		switch (m.id) {
		case net::_CONNECTION_REQUEST:
			handleConnectionRequest();
			break;
		case net::_FIGHTER_POS:
			handleFighterPos();
			break;
		case net::_BULLETS_REC:
			handleBullets();
			break;
		case net::_START_ROUND_REQUEST:
			handleStartRoundRequest();
			break;
		case net::_START_THE_ROUND:
			handleStartTheRound();
			break;
		case net::_FIGHTER_HIT:
			handleFighterHit();
			break;
		case net::_DISCONNECTING:
			handleDisconnecting();
			break;
		default:
			break;
		}

	}

}

bool NetworkSystem::initConnection(Uint16 port) {
	sock_ = SDLNet_UDP_Open(port);
	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sockSet_ = SDLNet_AllocSocketSet(1);
	if (!sockSet_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_UDP_AddSocket(sockSet_, sock_);
	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	port_ = SDLNetUtils::getSocketPort(sock_);

	return true;
}

bool NetworkSystem::initHost() {

	Uint16 port;
	std::cout << "Enter a port number to use: ";
	if (!(std::cin >> port)) {
		std::cerr << "Invalid port" << std::endl;
		return false;
	}

	if (!initConnection(port))
		return false;

	names_[0] = myName;

	host_ = true;
	side_ = 0;
	connected_ = false;
	return true;

}

bool NetworkSystem::initClient() {

	Uint16 port;
	std::string host;

	std::cout << "Enter the host and port (separated by space) of the host: "
		<< std::endl;
	if (!(std::cin >> host >> port)) {
		std::cerr << "Invalid host/port" << std::endl;
		return false;
	}

	if (SDLNet_ResolveHost(&otherPlayerAddr_, host.c_str(), port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	host_ = false;

	initConnection(0);

	names_[1] = myName;

	net::StartRequestMsg m;

	m.id = net::_CONNECTION_REQUEST;
	string_to_chars(myName, m.name);

	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_);

	if (SDLNet_CheckSockets(sockSet_, 3000) > 0) {
		if (SDLNet_SocketReady(sock_)) {
			SDLNetUtils::deserializedReceive(m, p_, sock_);
			if (m.id == net::_REQUEST_ACCEPTED) {
				net::ReqAccMsg m;
				m.deserialize(p_->data);
				side_ = m.side;
				chars_to_string(names_[0], m.name);
				mngr_->getComponent<FighterInfo>(mngr_->getEntities(ecs::_grp_FIGHTERS)[0])->name_ = names_[0];
				host_ = false;
				connected_ = true;
			}
		}
	}

	if (!connected_) {
		std::cout << "Could not connect to the other player " << std::endl;
		return false;
	}

	return true;

}
void NetworkSystem::sendFighterTransform(Transform *tr) {
	if (!connected_)
		return;

	net::FighterPosMsg m;
	m.id = net::_FIGHTER_POS;
	m.side = side_;
	m.x = tr->pos_.getX();
	m.y = tr->pos_.getY();
	m.rot = tr->rot_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::sendBullet(const Message& m) {
	if (!connected_)
		return;

	net::BullGenMsg send;
	send.id = net::_BULLETS_REC;

	send.pos.x = m.shoot.pos.x;
	send.pos.y = m.shoot.pos.y;
	send.vel.x = m.shoot.vel.x;
	send.vel.y = m.shoot.vel.y;

	SDLNetUtils::serializedSend(send, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::handleConnectionRequest() {

	if (!connected_ && host_) {
		otherPlayerAddr_ = p_->address;
		connected_ = true;
		net::ReqAccMsg m;
		m.id = net::_REQUEST_ACCEPTED;
		m.side = 1 - side_;
		chars_to_string(names_[1], m.name);
		SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
		mngr_->getComponent<FighterInfo>(mngr_->getEntities(ecs::_grp_FIGHTERS)[1])->name_ = names_[1];
	}
}

void NetworkSystem::sendStartRoundtRequest() {
	assert(!isHost());

	net::StartRequestMsg m;

	m.id = net::_START_ROUND_REQUEST;
	m.side = side_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);

}

void NetworkSystem::sendStartGameRequest() {
	assert(!isHost());

	net::StartRequestMsg m;

	m.id = net::_START_GAME_REQUEST;
	m.side = side_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);

}

void NetworkSystem::handleFighterPos() {
	net::FighterPosMsg m;
	m.deserialize(p_->data);
	mngr_->getSystem<FightersSystem>()->changeFighterTransform(m.side, m.x, m.y, m.rot);
}

void NetworkSystem::handleBullets() {

	net::BullGenMsg m;
	m.deserialize(p_->data);

	Message send;
	send.id = _m_SHOOT;
	send.shoot.pos.x = m.pos.x;
	send.shoot.pos.y = m.pos.y;
	send.shoot.vel.x = m.vel.x;
	send.shoot.vel.y = m.vel.y;

	send.shoot.net = true;

	mngr_->getSystem<BulletsSystem>()->recieve(send);

}

//void NetworkSystem::handleBulletsVel() {
//	assert(!host_);
//	net::BulletsVelMsg m;
//	m.deserialize(p_->data);
//	mngr_->getSystem<BulletsSystem>()->changeBallVel(m.x, m.y);
//}

void NetworkSystem::handleStartRoundRequest() {
	mngr_->getSystem<GameCtrlSystem>()->startGame();
}

void NetworkSystem::handleStartTheRound() {
	assert(!host_);
	mngr_->getSystem<GameCtrlSystem>()->startGame();
}

void NetworkSystem::handleFighterHit() {
	net::BallExitMsg m;
	m.deserialize(p_->data);
	//mngr_->getSystem<GameCtrlSystem>()->(m.side);
}

void NetworkSystem::handleDisconnecting() {
	connected_ = false;
	host_ = true;
	mngr_->getSystem<GameCtrlSystem>()->stopTheGame();
}

void NetworkSystem::tellOtherClientToStartRound() {
	net::Message m;

	m.id = net::_START_THE_ROUND;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);

}

void NetworkSystem::tellOtherClientToStartGame() {
	net::Message m;

	m.id = net::_START_THE_GAME;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::tellOtherClientFighterHit(uint8_t hitId_) {
	net::BallExitMsg m;

	m.id = net::_FIGHTER_HIT;
	m.side = hitId_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);

}


void NetworkSystem::string_to_chars(std::string& str, char c_str[11]) {
	auto i = 0u;
	for (; i < str.size() && i < 10; i++) c_str[i] = str[i];
	c_str[i] = 0;
}

void NetworkSystem::chars_to_string(std::string& str, char c_str[11]) {
	c_str[10] = 0;
	str = std::string(c_str);
}
