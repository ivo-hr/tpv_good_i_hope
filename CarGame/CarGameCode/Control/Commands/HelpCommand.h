#pragma once

#ifndef CARGAME_HELPCOMMAND_H
#define CARGAME_HELPCOMMAND_H

#include "Command.h"

class HelpCommand : public Command {

public:
    const string INFO_STRING = "[H] to toggle this";

    HelpCommand() {
        info_string = INFO_STRING;
    };
    ~HelpCommand() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;
};


#endif //CARGAME_HELPCOMMAND_H