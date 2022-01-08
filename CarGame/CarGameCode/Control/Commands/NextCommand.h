#pragma once

#include "Command.h"

class NextCommand : public Command {

    bool bUp = false;
    bool bDown = false;
public:

    const string INFO_STRING = "[Space] to continue";

    NextCommand() {
        info_string = INFO_STRING;
    }
    ~NextCommand() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;
};