#include "MenuState.h"
#include "PlayingState.h"

MenuState::MenuState(Game *game): State(game){

    game->clearHelp();
    commandFactory->add(new HelpCommand());
    commandFactory->add(new NextCommand());
    commandFactory->add(new QuitCommand());
}

void MenuState::update(){
    //  \(º^º)/
}

void MenuState::draw(){
    string texts= "Güelcom tu SandoKart \n presiona [espacio] para empezar \n [h] = ayuda";

    game->renderText(texts, game->getWindowWidth()/2 - 100, game->getWindowHeight()/2 - 50);

    game->drawHelp();
    game->drawStateName();
}

void MenuState::next(){
     game->setState(new PlayingState(game));
     delete this;
}


