#ifndef CARGAME_COMMANDFACTORY_H
#define CARGAME_COMMANDFACTORY_H

#include "Commands/Command.h"
#include "Commands/QuitCommand.h"
#include "Commands/MoveCommand.h"
#include "Commands/AccCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/ShootCommand.h"

#include <vector>

class CommandFactory {

	vector<Command*> availableCommands;
	Game* game;

public:
	CommandFactory(Game* g) {
		game = g;
		//game->clearHelp();
	}

	~CommandFactory() {
		for (auto c : availableCommands)
			delete c;
	}

	Command* getCommand(SDL_Event& even) {
		for (auto c : availableCommands) {
			if (c->parse(even)) return c;
		}
		return nullptr;
	}

	void add(Command* c) {
		c->bind(game);
		availableCommands.push_back(c);
	}

	string HelpText() {
		string h = "";

		for (auto c : availableCommands) {
			h += c->GetInfoString() + "  ";
		}

		return h;

	}

};

#endif // !CARGAME_COMMANDFACTORY_H
