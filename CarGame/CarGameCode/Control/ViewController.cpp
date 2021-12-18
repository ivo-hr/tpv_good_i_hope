//
// Created by eys on 20/8/21.
//

#include "ViewController.h"

ViewController::ViewController(Game* _game) {

    //state = state.Ini;

    game = _game;
    cout << "[DEBUG] frame duration: " << frameDuration() << " ms" << endl;
    initSDL();

    game->setRenderer(renderer);
    game->loadTextures();

    //game->clearHelp();
    commandFactory = new CommandFactory(game);
    commandFactory->add(new QuitCommand());
    commandFactory->add(new MoveCommand());
    commandFactory->add(new AccCommand());
    commandFactory->add(new DebugCommand());
    commandFactory->add(new HelpCommand());
    commandFactory->add(new ShootCommand());
    commandFactory->add(new WaveCommand());

}

void ViewController::run() {

    int time = 0;

    while (!game->doQuit()) {

        uint32_t startTime = 0;
        uint32_t frameTime;

        switch (state) {

            //________________________

        case ini:

            clearBackground();
            game->GameMenu();

            SDL_RenderPresent(renderer);
            //SDL_Delay(2000);

            handleEvents();
            time = SDL_GetTicks();
            break;

            //________________________

        case running:

            game->startGame();

            while (!game->GameEnd() && !game->doQuit()) {
                frameTime = SDL_GetTicks() - startTime;
                handleEvents();
                if (frameTime >= frameDuration()) {
                    clearBackground();
                    game->update();
                    game->draw();
                    SDL_RenderPresent(renderer);
                    startTime = SDL_GetTicks();
                }
                else {
                    SDL_Delay(frameDuration() - frameTime);
                }
            }

            time = SDL_GetTicks() - time;
            state = fin;

            break;

            //________________________

        case fin:

            clearBackground();

            if (game->HasLost()) {
                game->renderText("You Lost...", 50, 50, BLACK);

                game->currentState = "endStateLoser";
            }
            else {
                game->renderText("You Won!", 50, 50, BLACK);
                game->renderText("Your time: " + to_string(time), 50, 70, BLACK);

                game->currentState = "endStateWinner";
            }
            SDL_RenderPresent(renderer);

            SDL_Delay(500);

            handleEvents();

            break;

            //________________________

        default:
            state = ini;
            break;
        }
    }
}

void ViewController::clearBackground() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void ViewController::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            
            if (state == fin) {
                state = ini;
            }
            else if (state == ini) {
                state = running;
            }

        }

        Command* command = commandFactory->getCommand(event);
        if (command != nullptr) {
            command->execute();
            break;
        }
    }
}

uint32_t ViewController::frameDuration() {
    return 1000 / FRAME_RATE;
}

void ViewController::initSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(game->getGameName().c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game->getWindowWidth(),
        game->getWindowHeight(),
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == nullptr || renderer == nullptr)
        throw string("Error creating SDL window or renderer");

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, &screenSurface->clip_rect, 0xFF);
    SDL_UpdateWindowSurface(window);
}

ViewController::~ViewController() {
    delete commandFactory;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
