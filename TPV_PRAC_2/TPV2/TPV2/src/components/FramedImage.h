#pragma once
#include <vector>
#include "../game/Component.h"

class Transform;
class Texture;
class Vector2D;
struct SDL_Rect;

class FramedImage: public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):


	constexpr static ecs::cmpId_type id = ecs::_FRAMED_IMAGE;

	FramedImage();
	FramedImage(Texture* tex, int spritesInRow, int spritesInCol);
	virtual ~FramedImage();

	Texture* getTexture() { return tex_; };

	void setTexture(Texture *tex) {
		tex_ = tex;
	}

	SDL_Rect* getSrc() { return recorte_; };

	void initComponent() override;
	void update() override;
	void render() override;

private:
	Transform *tr_ = nullptr;
	Texture *tex_ = nullptr;

	SDL_Rect* recorte_ = nullptr;

	float lastUpdate_ = 0.f;
	float frameRate_ = 0.f;
};

