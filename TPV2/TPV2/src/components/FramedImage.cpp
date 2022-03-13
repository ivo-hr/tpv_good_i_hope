#include "FramedImage.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

FramedImage::FramedImage() :
		tr_(), tex_(), frameRate_(50.f) {
}

FramedImage::FramedImage(Texture *tex) :
		tr_(), tex_(tex), frameRate_(50.f) {
}

FramedImage::~FramedImage() {
	for (Vector2D* vec : frames_) {
		delete vec;
	}
}

void FramedImage::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	recorte_ = new SDL_Rect{ 0, 0, 85, 100 };
	assert(tr_ != nullptr); 

	lastUpdate_ = sdlutils().currRealTime();

	//Save all pairs of coordinates in a vector for easy access
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			frames_.push_back(new Vector2D(i, j));
		}
	}
}

void FramedImage::update()
{
	//If enough time passes...
	if (lastUpdate_ + frameRate_ <= sdlutils().currRealTime())
	{
		//We update the index of the current frame
		currIndex_++;
		if (currIndex_ == frames_.size())
			currIndex_ = 0;

		//We set the rect to select the sprite according to the vector2 in the current index
		recorte_->x = 85 * frames_[currIndex_]->getX();
		recorte_->y = 100 * frames_[currIndex_]->getY();

		//Update the timer
		lastUpdate_ = sdlutils().currRealTime();
	}

}

void FramedImage::render() {

	SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getWidth(),
			tr_->getHeight());

	assert(tex_ != nullptr);
	tex_->render(*recorte_, dest, tr_->getRot(), nullptr, SDL_FLIP_NONE);

}
