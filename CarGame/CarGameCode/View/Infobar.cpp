#include "Infobar.h"

void Infobar::drawInfo()
{

    int x = game->font->getSize() / 2;
    int y = game->font->getSize() / 2;


    SDL_Rect rect = { 0, 0, game->getWindowWidth(),
                     int(game->font->getSize() * 1.8) };
	Box(rect, BLACK).render(game->renderer);

    string s = "Pos: " + to_string(int(game->car->getX())) + " "
        + to_string(int(game->car->getY()));

    game->renderText(s, x, y);

    s = to_string(int(game->car->Power()))
        + "  " + to_string(game->car->getSpeed())
        + "  " + to_string((int)(game->roadLength - (game->car->getX() + game->car->getWidth() / 2)));

    game->renderText(s, x + game->getWindowWidth() / 7, y);

}

void Infobar::drawHelp()
{
    int x = game->font->getSize() / 2;
    int y = game->font->getSize() / 2;

    SDL_Rect rect = { 0, int(game->font->getSize() * 1.8), game->getWindowWidth(),
                     int(game->font->getSize() * 1.8) };
    Box(rect, BLACK).render(game->renderer);

    string s = game->helpText;

    game->renderText(s, x, y + int(game->font->getSize() * 1.8));
}

void Infobar::drawState()
{
	int x = game->font->getSize() / 2;
	int y = game->font->getSize() / 2;


	SDL_Rect rect = { 0, game->getWindowHeight() - game->font->getSize() * 1.5, game->getWindowWidth(),
					 int(game->font->getSize() * 1.8) };
	Box(rect, BLACK).render(game->renderer);

    string s = ("Current State: " + game->currentState);
    game->renderText(s, x, game->getWindowHeight() - game->font->getSize() * 1.5);

    if (game->car != nullptr)
    {
        s = ("Coins: " + to_string(game->GetCarCoins()));
        game->renderText(s, x + 250, game->getWindowHeight() - game->font->getSize() * 1.5);
    }
}
