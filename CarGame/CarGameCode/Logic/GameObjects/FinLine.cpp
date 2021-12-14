#include "FinLine.h"
#include "../Game.h"
FinLine::FinLine(Game* game) : GameObject(game)
{
	texture = nullptr;
	w = 50;
	h = game->getWindowHeight();
}

FinLine::~FinLine() {}

void FinLine::draw()
{
	drawTexture(game->getTexture(goalTexture));
}

void FinLine::update() {}
