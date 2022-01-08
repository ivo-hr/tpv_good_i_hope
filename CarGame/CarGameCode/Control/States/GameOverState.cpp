#include "GameOverState.h"
#include "PlayingState.h"

GameOverState::GameOverState(Game *game): State(game){
    game->clearHelp();
    commandFactory->add(new NextCommand());
    commandFactory->add(new QuitCommand());
}

void GameOverState::update(){
    //  \(º^º)/
}

void GameOverState::draw(){

    vector<string> texts;

    if (game->HasLost()){
        texts = {
        "PERDISTE",
        "presiona [espacio] para reiniciar",
    };
    }
    else texts = {
        "GANASTE",
        "presiona [espacio] para reiniciar",
    };

    game->renderText(texts[0], game->getWindowWidth()/2 - 100, game->getWindowHeight()/2 - 50);

    game->drawStateName();
}

void GameOverState::next(){
     game->setState(new PlayingState(game));
     delete this;
}


