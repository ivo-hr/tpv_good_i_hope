#include "Car.h"
#include "../Game.h"

Car::Car(Game* game) : GameObject(game) {
    texture = nullptr;
    w = 100;
    h = 50;
}


void Car::MoveX(int movX) {
    if (movX < 0) {
        xMov *= DECELERATION;
    }
    else if (movX > 0) {
        xMov *= ACCELERATION;
    }

    if (xMov > 10)
        xMov = 10;
    else if (xMov < 1) xMov = 1;
}

void Car::MoveY(int movY) {

    yMov = movY * VSPEED;

}

void Car::update() {
    
    if ((yMov > 0 && getY() >= game->getWindowHeight() - h / 2)) yMov = 0;
    else if ((yMov < 0 && getY() <= (h / 2) + 22)) yMov = 0;

    pos = Point2D<double>(getX() + xMov, getY() + yMov);

    vector<Collider*> colisiones = game->GetCollisions(this);

    for (auto e: colisiones) {
        e->receiveCarCollision(this);
    }
}

void Car::GetHit(){
    currPower--;
    xMov = 1;
}

void Car::AddPower()
{
    currPower++;
}

int Car::Power() {
    return currPower;
}

void Car::AddCoins(int num)
{
    coins += num;
}

int Car::GetNumCoins()
{
    return coins;
}

Car::~Car() {};

void Car::draw() {
    drawTexture(game->getTexture(carTexture));
}

SDL_Rect Car::getCollider() {
    return { int(getX() - getWidth()),
             int(getY() - getHeight() / 2),
             getWidth(),
             getHeight() };
}

