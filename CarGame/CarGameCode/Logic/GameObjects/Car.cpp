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
}

void Car::MoveY(int movY) {

    yMov = movY * VSPEED;

}

void Car::Stop()
{
    xMov = 0;
}

void Car::update() {
    
    if ((yMov > 0 && getY() >= game->getWindowHeight() - h / 2)) yMov = 0;
    else if ((yMov < 0 && getY() <= (h / 2) + 22)) yMov = 0;

    if (xMov > 10)
        xMov = 10;
    else if (xMov < 1) 
        xMov = 1;

    vector<Collider*> colisiones = game->GetCollisions(this);

    for (auto e : colisiones) {
        e->receiveCarCollision(this);
    }

    if (turbo > 0)
    {
        turbo--;
        xMov = 20;
    }

    pos = Point2D<double>(getX() + xMov, getY() + yMov);

}

void Car::GetHit(int damage){
    if (!shielded) {
		currPower -= damage;
		SlowDown(1);
    }
    else {
        coins--;
        if (coins <= 0) shielded = false;
    }
}

void Car::SlowDown(int slow) {

    xMov = slow;
}

void Car::AddPower()
{
    currPower++;
}

int Car::Power()
{
    return currPower;
}

void Car::ActivateTurbo()
{
    turbo = 150;
}

void Car::StopTurbo()
{
    turbo = 0;
}

void Car::telePort(int distance) {
    if (!teleporting) {
        pos = Point2D<double>(getX() + distance + xMov, getY() + yMov);
        teleporting = true;
    }
}

void Car::AddCoins(int num)
{
    coins += num;
}

int Car::GetCoins()
{
    return coins;
}

bool Car::CanBuy(int cost)
{
    if (coins <= cost)
        return false;

    if (!shielded)
        coins -= cost;

    return true;
}

Car::~Car() {};

void Car::draw() {
    if (!shielded)
    drawTexture(game->getTexture(carTexture));
    else
    drawTexture(game->getTexture(shieldCarTexture));

}

SDL_Rect Car::getCollider() {
    return { int(getX() - getWidth()),
             int(getY() - getHeight() / 2),
             getWidth(),
             getHeight() };
}

