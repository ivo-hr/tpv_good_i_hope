#pragma once

#include "Command.h"

class AccCommand : public Command {

    bool bDec = false;
    bool bAc = false;
public:

    const string INFO_STRING = "[LEFT/RIGHT] to Decelerate / Accelerate";

    AccCommand() {
        info_string = INFO_STRING;
    }
    ~AccCommand() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;
};