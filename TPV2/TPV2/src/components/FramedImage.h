#pragma once
#include <vector>
#include "../ecs/Component.h"

class Transform;
class Texture;
class Vector2D;
struct SDL_Rect;

class FramedImage: public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_IMAGE
	//
	__CMPID_DECL__(ecs::_FRAMEDIMAGE)

		FramedImage();
	FramedImage(Texture* tex, int spritesInRow, int spritesInCol);
	virtual ~FramedImage();

	void setTexture(Texture *tex) {
		tex_ = tex;
	}

	void initComponent() override;
	void update() override;
	void render() override;

private:
	Transform *tr_;
	Texture *tex_;

	SDL_Rect* recorte_;

	float lastUpdate_;
	float frameRate_;
};

