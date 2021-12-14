#include "GameObject.h"
#include "../Game.h"

void GameObject::drawTexture(Texture* texture)
{
	int dX = game->getOrigin().getX();
	int dY = game->getOrigin().getY();

	SDL_Rect c = getCollider();
	SDL_Rect textureBox = { c.x + dX, c.y + dY, c.w, c.h };

	texture->render(textureBox);
}

void GameObject::drawDebug()
{
	int dX = game->getOrigin().getX();
	int dY = game->getOrigin().getY();

	SDL_Rect c = getCollider();
	SDL_Rect box = { c.x + dX, c.y + dY, c.w, c.h };

	c = getCenter();
	SDL_Rect center = { c.x + dX, c.y + dY, c.w, c.h };

	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 255, 255);
	SDL_RenderDrawRect(game->getRenderer(), &center);

	SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(game->getRenderer(), &box);

	SDL_SetRenderDrawColor(game->getRenderer(), 255, 255, 255, 255);
}

void GameObject::setPosition(double x, double y)
{
	pos = Point2D<double>(x, y);
}

SDL_Rect GameObject::getCollider()
{
	return { int(getX() - getWidth() / 2),
		int(getY() - getHeight() / 2),
		getWidth(),
		getHeight() };
}

SDL_Rect GameObject::getCenter()
{
	return { int(getX() - 1),
		int(getY() - 1),
		2,
		2 };
}

bool GameObject::collide(SDL_Rect other)
{
	return SDL_HasIntersection(&getCollider(), &other);
}