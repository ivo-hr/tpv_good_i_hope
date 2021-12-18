//
// Created by eys on 20/8/21.
//

#include "Game.h"
#include <stdlib.h>
#include <time.h>

Game::Game(string name, int width, int height, int roadLength) {
    this->name = name;
    this->roadLength = roadLength;
    this->width = width;
    this->height = height;
    doExit = false;
    debug = false;
    help = false;
    font = new Font("../Images/Monospace.ttf", 12);

    numRocks = 10;
    numExLives = 5;
    numCoins = 15;
    numSRocks = 3;
    numOils = 7;
    numTrucks = 3;
    numTurbos = 5;

    infobar = new Infobar(this);
}

void Game::startGame() {

    currentState = "gameplayState";
    car = new Car(this);

    car->setPosition(car->getWidth(), height / 2.0);

    srand(time(NULL));

    container = new GameObjectContainer();

    GameObjectGenerator::generate(this, numRocks, numExLives, numCoins, numSRocks, numOils, numTrucks, numTurbos);
    
    goal = new FinLine(this);

    goal->setPosition(roadLength - goal->getWidth() / 2, height / 2.0);
}

void Game::GameMenu(){
    currentState = "menuScreen";
    infobar->drawState();

    string title = "SandoKart";

    renderText(title, getWindowWidth()/2, getWindowHeight()/2);
    
    string start = "Press 'Space' to start";
    renderText(start, getWindowWidth()/2 - 10, getWindowHeight()/2 + font->getSize());

    string exit = "Press 'Esc' to quit";
    renderText(exit, getWindowWidth() / 2 - 10, getWindowHeight() / 2 + font->getSize() * 2);
}

string Game::getGameName() {
    return name;
}

Game::~Game() {
    cout << "[DEBUG] deleting game" << endl;
    delete infobar;
    delete font;
}

void Game::update() {
    car->update();

    container->update();
    container->removeDead();
}

vector<Collider*> Game::GetCollisions(GameObject* o) {

    return container->getCollisions(o);

}

bool Game::HasLost(){

    bool a = car->Power() <= 0;

    return a;
}

void Game::appendHelpInfo(string a)
{
    helpText += a + "  ";
}

void Game::addObject(GameObject* obj)
{
    cout << "añadido";
    container->add(obj);
}

void Game::draw() {

    container->draw();
    car->draw();
    goal->draw();

    infobar->drawInfo();
    infobar->drawState();

    if (help) {
        infobar->drawHelp();
    }

    if (debug) {
        container->drawDebug();
        car->drawDebug();
        goal->drawDebug();
    }

}

int Game::GetCarX()
{
    return car->getX();
}

int Game::GetCarY()
{
    return car->getY();
}

bool Game::CarCanBuy(int cost)
{
    return car->CanBuy(cost);
}

void Game::MoveCarX(int movX) {
    car->MoveX(movX);
}
void Game::MoveCarY(int movY) {
    car->MoveY(movY);
}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

int Game::getWindowWidth() {
    return width;
}

int Game::getWindowHeight() {
    return height;
}

int Game::getRoadLenght() {
    return roadLength;
}

GameObjectContainer* Game::getContainer() {
    return container;
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

void Game::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if (renderer == nullptr)
        throw string("Renderer is null");

    textureContainer = new TextureContainer(renderer);
}

void Game::renderText(string text, int x, int y, SDL_Color color) {
    font->render(renderer, text.c_str(), x, y, color);
}

bool Game::doQuit() {
    return isUserExit();
}

Texture* Game::getTexture(TextureName name) {
    return textureContainer->getTexture(name);
}

Font* Game::GetFont() {
    return font;
}

void Game::Debug(){
    debug = !debug;
}

void Game::Help()
{
    help = !help;
}

bool Game::GameEnd() {
    
    infobar->drawState();

    if (SDL_HasIntersection(&car->getCollider(), &goal->getCollider()) || car->Power() < 1) {
        currentState = "finState";
        return true;
    }
    else {
        return false;
    }
}

Point2D<int> Game::getOrigin() {
    return { int(-(car->getX() - car->getWidth())), 0 };
}

bool Game::isRebased(GameObject* toBe){
    
    return car->getX() - car->getWidth() - toBe->getWidth()  > toBe->getX();

}

int Game::GetCarCoins()
{
    return car->GetCoins();
}
