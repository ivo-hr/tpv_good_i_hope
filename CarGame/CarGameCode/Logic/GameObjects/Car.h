//
// Created by eys on 21/8/21.
//

#ifndef CARGAME_CAR_H
#define CARGAME_CAR_H


class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"
#include "GameObject.h"

class Car : public GameObject {

private:

    const double ACCELERATION = 1.3;
    const double DECELERATION = 0.9;
    const int VSPEED = 5;
    const int MAX_SPEED = 10;
    const int INITIAL_POWER = 3;
    const int INITIAL_COINS = 3;

    int yMov = 0;
    float xMov = 1;

    int currPower = INITIAL_POWER;

    int coins = INITIAL_COINS;

    int turbo = 0;

public:
    Car(Game* game);
    ~Car();

    void draw() override;

    void update() override;

    float getSpeed() { return xMov; };

    void MoveX(int movX);
    void MoveY(int movY);
    void Stop();
    void GetHit(int damage);
    void SlowDown(int slow);
    void AddPower();
    int Power();
    void ActivateTurbo();
    void StopTurbo();

    void AddCoins(int num);
    int GetCoins();
    bool CanBuy(int cost);

    SDL_Rect getCollider() override;
};


#endif //CARGAME_CAR_H
