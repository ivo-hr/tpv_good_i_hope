#ifndef CARGAME_GAMEOBJECTGENERATOR_H
#define	CARGAME_GAMEOBJECTGENERATOR_H

#include "Game.h"
#include "GameObjects/Objects.h"

class GameObjectGenerator
{

	Point2D<int> static generateRandomPosition(Game* game, GameObject* o);
	void static addInRandomPosition(Game* game, GameObject* o);
	Point2D<int> static generateStaticPosition(Game* game, GameObject* o, int interval);
	void static addInStaticPosition(Game* game, GameObject* o, int interval);

public:
	static void generate(Game* game, int N_ROCKS = 0, int N_COINS = 0, int N_MONEY = 0, int N_SROCKS = 0, int N_OILS = 0, int N_TRUCKS = 0, int N_TURBOS = 0, int N_WORMHOLES = 0, int N_CLOUDS = 0)
	{
		for (int i = 0; i < N_WORMHOLES; i++)
			addInStaticPosition(game, new Wormhole(game), 500 * (i + 1));

		for (int i = 0; i < N_ROCKS; i++)
			addInRandomPosition(game, new Rock(game));

		for (int i = 0; i < N_COINS; i++)
			addInRandomPosition(game, new PowerUp(game));

		for (int i = 0; i < N_MONEY; i++)
			addInRandomPosition(game, new Coin(game));

		for (int i = 0; i < N_SROCKS; i++)
			addInRandomPosition(game, new SuperRock(game));

		for (int i = 0; i < N_OILS; i++)
			addInRandomPosition(game, new Oil(game));

		for (int i = 0; i < N_TRUCKS; i++)
			addInRandomPosition(game, new Truck(game));

		for (int i = 0; i < N_TURBOS; i++)
			addInRandomPosition(game, new Turbo(game));

		for (int i = 0; i < N_CLOUDS; i++)
			addInRandomPosition(game, new Cloud(game));
	}
};

#endif // !CARGAME_GAMEOBJECTGENERATOR_H
