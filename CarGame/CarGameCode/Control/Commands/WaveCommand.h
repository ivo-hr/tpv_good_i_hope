#pragma once

#include "Command.h"

class WaveCommand : public Command {

public:
	const string INFO_STRING = "[W] to wave Objects";

	WaveCommand() {
		cost = 3;
		info_string = INFO_STRING;
	}
	~WaveCommand() = default;
	bool parse(SDL_Event& event) override;
	void execute() override;
};

