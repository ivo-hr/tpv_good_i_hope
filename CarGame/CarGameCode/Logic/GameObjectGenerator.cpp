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

Point2D<int> GameObjectGenerator::generateStaticPosition(Game* game, GameObject* o, int interval)
{
	if (interval < game->getRoadLenght())
		return Point2D<int>(interval, (game->getWindowHeight()/2));
	else return Point2D<int>(0, 0);
}

void GameObjectGenerator::addInStaticPosition(Game* game, GameObject* o, int interval)
{
	Point2D<int> punto = generateStaticPosition(game, o, interval);

	o->setPosition(punto.getX(), punto.getY());

	game->getContainer()->add(o);


	if (punto == Point2D<int>(0, 0))
		delete o;


}
