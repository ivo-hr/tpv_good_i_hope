#ifndef CARGAME_COLLIDER_H
#define CARGAME_COLLIDER_H

class Car;
class Bullet;

class Collider {

public:
    virtual bool receiveCarCollision(Car *car){
        return false;
    };
    virtual bool receiveBulletCollision(Bullet* bullet) {
        return false;
    };
    virtual bool wave() {
        return false;
    };
    virtual bool blast() {
        return false;
    };
};

#endif //CARGAME_COLLIDER_H