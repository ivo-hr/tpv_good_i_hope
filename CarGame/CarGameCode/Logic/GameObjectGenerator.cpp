#include "GameObjectGenerator.h"


Point2D<int> GameObjectGenerator::generateRandomPosition(Game* game, GameObject* o)
{
	return Point2D<int>(rand() % (game->getRoadLenght() + o->getWidth()) + o->getWidth() / 2,
		rand() % (game->getWindowHeight() - o->getHeight() - 22) + (o->getHeight() / 2 + 22));
}

void GameObjectGenerator::addInRandomPosition(Game* game, GameObject* o)
{
	Point2D<int> punto = generateRandomPosition(game, o);

	o->setPosition(punto.getX(), punto.getY());

	if (!game->getContainer()->hasCollision(o))
	{
		game->getContainer()->add(o);
	}
	else
	{
		delete o;
	}
}
