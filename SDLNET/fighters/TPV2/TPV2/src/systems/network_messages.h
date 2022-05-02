// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../sdlutils/SDLNetUtils.h"

namespace net {

enum MsgId : Uint8 {
	_CONNECTION_REQUEST, //
	_REQUEST_ACCEPTED, //
	_REQUEST_REFUSED, //
	_FIGHTER_POS, //
	_BULLETS_REC, //
	_START_ROUND_REQUEST, //
	_START_GAME_REQUEST, //
	_START_THE_GAME, //
	_START_THE_ROUND, //
	_FIGHTER_HIT, //
	_GAME_OVER, //
	_DISCONNECTING, //
}; 



struct Message {
	Uint8 id;

	//
	_IMPL_SERIALIAZION_(id)
};

struct ReqAccMsg: Message {

	Uint8 side;
	char name[11];

	_IMPL_SERIALIAZION_WITH_BASE_(Message, side, name)
};

struct FighterPosMsg: Message {

	Uint8 side;
	float x;
	float y;
	float rot;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y,rot)
};

struct BulletsPosMsg: Message {

	Uint8 side;
	float x;
	float y;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y)
};

struct BulletsVelMsg: Message {

	Uint8 side;
	float x;
	float y;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y)
};

struct StartRequestMsg: Message {

	Uint8 side;
	char name[11];

	_IMPL_SERIALIAZION_WITH_BASE_(Message, side, name)
};

struct BallExitMsg: Message {

	Uint8 side;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side)
};


struct BullGenMsg: Message{
		struct {
			float x;
			float y;
		} pos;
		struct {
			float x;
			float y;
		} vel;

		_IMPL_SERIALIAZION_WITH_BASE_(Message, pos.x, pos.y, vel.x, vel.y)
};



}

