//
//
// Created by eys on 20/8/21.
//

#ifndef CARGAME_GAME_H
#define CARGAME_GAME_H

#include <iostream>
#include <string>
#include <vector>

#include "../View/TextureContainer.h"
#include "../View/Texture.h"
#include "../View/Box.h"
#include "../View/Font.h"
#include "../View/Infobar.h"

#include "GameObjectGenerator.h"
#include "GameObjectContainer.h"
#include "GameObjects/Car.h"
#include "GameObjects/FinLine.h"



using namespace std;

class Game {

    friend class Infobar;


private:
    string name;
    bool doExit;
    int roadLength;
    int width, height;
    Car* car = nullptr;
    FinLine* goal = nullptr;
    int numRocks;
    int numExLives;
    int numCoins;
    int numSRocks;
    int numOils;
    int numTrucks;
    int numTurbos;
    bool debug;
    bool help;
    string helpText;

    TextureContainer* textureContainer;
    GameObjectContainer* container;
    SDL_Renderer* renderer = nullptr;
    Font* font;
    Infobar* infobar;

public:

    Game(string name, int width, int height, int roadLength);
    ~Game();
    
    void startGame();
    void update();

    void appendHelpInfo(string a);

    void addObject(GameObject* obj);

    void draw();

    int GetCarX();
    int GetCarY();
    bool CarCanBuy(int cost);
    int GetCarCoins();

    void MoveCarX(int movX);
    void MoveCarY(int movY);
    void setUserExit();
    bool isUserExit();
    bool doQuit();
    vector<Collider*> GetCollisions(GameObject* o);
    bool HasLost();

    int getWindowWidth();
    int getWindowHeight();
    int getRoadLenght();
    GameObjectContainer* getContainer();

    Point2D<int> getOrigin();

    string getGameName();

    void GameMenu();
    bool GameEnd();

    void setRenderer(SDL_Renderer* renderer);
    void loadTextures();
    Texture* getTexture(TextureName name);
    SDL_Renderer* getRenderer();
    void renderText(string text, int x, int y, SDL_Color color = { 0,0,0 });
    Font* GetFont();

    void Debug();
    void Help();

    bool isRebased(GameObject* toBe);

    string currentState = "didNotWork :(";

};


#endif //CARGAME_GAME_H
