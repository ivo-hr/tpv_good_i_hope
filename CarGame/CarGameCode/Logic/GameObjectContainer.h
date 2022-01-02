#ifndef CARGAME_GAMEOBJECTCONTAINER_H
#define CARGAME_GAMEOBJECTCONTAINER_H

#include "../Logic/GameObjects/GameObject.h"
#include <vector>
using namespace std;

class GameObject;
class Collider;

class GameObjectContainer {
    vector<GameObject*> gameObjects;
public:

    GameObjectContainer(){};
    ~GameObjectContainer();
    void update();
    void draw();
    void drawDebug();
    void add(GameObject *gameObject);
    void removeDead();
    void waveObjects();
    vector<Collider*> getCollisions(GameObject *g);
    vector<Collider*> getCollisions(SDL_Rect* r);
    bool hasCollision(GameObject *g);
};


#endif //CARGAME_GAMEOBJECTCONTAINER_H
