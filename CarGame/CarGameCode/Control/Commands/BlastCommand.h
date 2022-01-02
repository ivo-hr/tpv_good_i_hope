#pragma once

#include "Command.h"

class BlastCommand : public Command {

    int range;
    int x;
    int y;

public:

    const string INFO_STRING = "[Click] to Delete bad objects";

    BlastCommand() {
        range = 300;
        cost = 3;
        info_string = INFO_STRING;
    }
    ~BlastCommand() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;
};

