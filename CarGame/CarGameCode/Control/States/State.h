#pragma once

#include "../CommandFactory.h"

class Game;

class State {

protected:

	Game* game;

	CommandFactory* commandFactory;

public:
	State(Game* game) : game(game) {
		commandFactory = new CommandFactory(game);
	};

	virtual ~State() {
		delete commandFactory;
	};

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void next() = 0;

	virtual string getStateName() const = 0;

	void handleEvents() 
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			Command* command = commandFactory->getCommand(event);
			if (command != nullptr) {
				command->execute();
				break;
			}
		}
	};
};