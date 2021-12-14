#pragma once

#ifndef CARGAME_DEBUGCOMMAND_H
#define CARGAME_DEBUGCOMMAND_H

#include "Command.h"

class DebugCommand : public Command {

public:
	const string INFO_STRING = "[E] to enable debug mode";

	DebugCommand() {
		info_string = INFO_STRING;
	}
	~DebugCommand() = default;
	bool parse(SDL_Event& event) override;
	void execute() override;
};

#endif //CARGAME_DEBUGCOMMAND_H
