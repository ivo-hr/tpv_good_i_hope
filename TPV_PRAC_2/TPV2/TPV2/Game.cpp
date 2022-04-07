#include "Game.h"

#include "src/game/components/Transform.h"
#include "src/game/ecs.h"
#include "src/game/Entity.h"
#include "src/sdlutils/InputHandler.h"
#include "src/sdlutils/SDLUtils.h"

#include "src/utils/Vector2D.h"
#include "src/game/System.h"
#include "src/game/Manager.h"

#include "GameCtrlSystem.h"
#include "src/game/AsteroidsSystem.h"
#include "src/game/BulletsSystem.h"
#include "src/game/CollisionsSystem.h"
#include "src/game/FighterSystem.h"
#include "src/game/RenderSystem.h"

Game::Game() {

    mngr = new ecs::Manager();

    collSys = nullptr;
    renderSys = nullptr;
    fghtrSys = nullptr;
    bulletsSys = nullptr;
    asteroidsSys = nullptr;
    gameCtrlSys = nullptr;
}

Game::~Game() {
}

void Game::init() {

    SDLUtils::init("Fighter", 800, 600, "resources/config/resources.json");


    fghtrSys = mngr->addSystem<FighterSystem>();
    bulletsSys = mngr->addSystem<BulletsSystem>();
    asteroidsSys = mngr->addSystem<AsteroidsSystem>();
    collSys = mngr->addSystem<CollisionsSystem>();
    gameCtrlSys = mngr->addSystem<GameCtrlSystem>();
    renderSys = mngr->addSystem<RenderSystem>();

}
void Game::start() {

    // a boolean to exit the loop
    bool exit = false;
    SDL_Event event;

    while (!exit) {
        Uint32 startTime = sdlutils().currRealTime();

        ih().clearState();
        while (SDL_PollEvent(&event))
            ih().update(event);

        if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
            exit = true;
            continue;
        }

        mngr->refresh();

        collSys->update();
        fghtrSys->update();
        bulletsSys->update();
        asteroidsSys->update();
        gameCtrlSys->update();

        mngr->flushMessages();

        sdlutils().clearRenderer();

        renderSys->update();

        sdlutils().presentRenderer();

        Uint32 frameTime = sdlutils().currRealTime() - startTime;

        if (frameTime < 20)
            SDL_Delay(20 - frameTime);
    }

}