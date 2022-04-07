#pragma once

#include <cstdint>
#include "ecs.h"
#include "Entity.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_SHOOT, //
	_m_COLLISION_BULLETASTEROID, //
	_m_COLLISION_ASTEROIDFIGHTER, //
	_m_ROUND_START, //
	_m_ROUND_END
};

//Cambiar esto y poner cada mensaje que necesitemos aaaaa


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		// _m_SHOOT
		struct {
			float x, y, velX, velY;
			double width, height;
			float rot;
		} shoot_data;

		// _m_COLLISION_BULLETASTEROID
		struct {
			ecs::Entity* b;
			ecs::Entity* a;
		} collision_bulast_data;

		// _m_COLLISION_ASTEROIDFIGHTER
		/*struct {
		} collision_astfig_data;*/

		// _m_ROUND_START
		/*struct {
		} roundstart_data;*/

		// _m_ROUND_END
		/*struct {
		} roundover_data;*/

	};
};
