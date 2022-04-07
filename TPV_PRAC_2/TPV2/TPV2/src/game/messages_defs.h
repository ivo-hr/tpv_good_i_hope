#pragma once


#include <cstdint>
#include "ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_STAR_EATEN, //
	_m_CREATE_STARS
};

//Cambiar esto y poner cada mensaje que necesitemos aaaaa


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		// _m_STAR_EATEN
		struct {
			ecs::Entity* e;
		} star_eaten_data;

		// _m_CREATE_STARS
		struct {
			unsigned int n;
		} create_stars_data;

	};
};
