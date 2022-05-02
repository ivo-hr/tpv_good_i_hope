// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <string>
#include "../ecs/Component.h"

struct FighterInfo: public ecs::Component {

	__CMPID_DECL__(ecs::_FIGHTERID)

	FighterInfo() :
			id_(0), lastShoot_(0), shootRate_(250), name_() {
	}

	FighterInfo(uint8_t id, std::string name) :
			id_(id), lastShoot_(0), shootRate_(250), name_(name) {
	}

	virtual ~FighterInfo() {
	}

	uint8_t id_;
	uint32_t lastShoot_;
	uint32_t shootRate_;

	std::string name_;
};

