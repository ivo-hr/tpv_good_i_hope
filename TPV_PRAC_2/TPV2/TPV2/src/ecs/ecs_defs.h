// This file is part of the course TPV2@UCM - Samir Genaim

// DO NOT USE/MODIFY THIS FILE, IT IS JUST AN EXAMPLE OF HOW YOUR
// game/ecs_defs.h SHOULD LOOK LIKE
//
// Note that the backslash \ after each line below is very important
// when using #define, if you remove it then put all at the same
// line of #define
//

#pragma once

// Components list - must have at least one element
//
#define _CMPS_LIST_ \
	_TRANSFORM, \
	_IMAGE, \
	_FRAMED_IMAGE, \
	_ASTER_TYPE

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	_grp_BULLETS, \
	_grp_ASTEROID

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    _hdlr_FGHTR, \
	_hdlr_GAMEINFO
// Systems list - must have at least one element
//
#define _SYS_LIST_ \
    _sys_COLLISION, \
	_sys_RENDER, \
	_sys_BULLET, \
	_sys_ASTEROID, \
	_sys_CTRL, \
	_sys_FIGHTER


