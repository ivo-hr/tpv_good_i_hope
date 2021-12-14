#pragma once

#include "Command.h"

class ShootCommand : public Command {

public:

    const string INFO_STRING = "[S] to shoot";

    ShootCommand() {
        info_string = INFO_STRING;
    }
    ~ShootCommand() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;
};