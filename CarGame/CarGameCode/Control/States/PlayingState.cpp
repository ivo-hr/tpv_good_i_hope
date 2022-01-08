#include "PlayingState.h"
#include "GameOverState.h"

PlayingState::PlayingState(Game* game) : State(game)
{
	game->clearHelp();
	commandFactory->add(new HelpCommand());
	commandFactory->add(new DebugCommand());
	commandFactory->add(new MoveCommand());
	commandFactory->add(new AccCommand());
	commandFactory->add(new ShootCommand());
	commandFactory->add(new BlastCommand());
	commandFactory->add(new QuitCommand());
	commandFactory->add(new WaveCommand());

	totalTime = 0;
	initTime = SDL_GetTicks();
}

void PlayingState::update()
{
	totalTime += (SDL_GetTicks() - initTime);
	initTime = SDL_GetTicks();
	game->setElapsedTime(totalTime);

	if (game->GameEnd())
		next();

	game->update();
}

void PlayingState::draw()
{
	game->drawGameplay();
}

void PlayingState::next()
{
	game->setState(new GameOverState(game));
	delete this;
}
