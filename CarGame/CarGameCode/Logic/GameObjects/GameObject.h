#ifndef CARGAME_GAMEOBJECT_H
#define CARGAME_GAMEOBJECT_H

#include "Collider.h"

class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class GameObject : public Collider
{
protected:
	Point2D<double> pos;
	int w, h;
	int waveValue;

	Game* game;
	Texture* texture;

	void drawTexture(Texture* texture);

public:

	GameObject(Game* game) : game(game) {}
	virtual ~GameObject() {}

	virtual void draw() = 0;
	virtual void drawDebug();
	virtual void update() = 0;

	virtual bool toDelete() { return false; }
	virtual void onEnter() {}
	virtual void onDelete() {}

	void setPosition(double x, double y);

	int getWidth() { return w; }
	int getHeight() { return h; }

	int getX() { return pos.getX(); }
	int getY() { return pos.getY(); }
	virtual SDL_Rect getCollider();
	virtual SDL_Rect getCenter();

	bool collide(SDL_Rect other);
	bool wave() override;
};

#endif // !CARGAME_GAMEOBJECT_H
