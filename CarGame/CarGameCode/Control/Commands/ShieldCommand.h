#pragma once

#include "Command.h"

class ShieldCommand : public Command {

private:
	bool shieldActive;

public:

	const string INFO_STRING = "[S] to shoot";

	ShieldCommand() {
		cost = 0;
		info_string = INFO_STRING;
	}
	~ShieldCommand() = default;
	bool parse(SDL_Event& event) override;
	void execute() override;
};