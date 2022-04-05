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
	recorte_ = new SDL_Rect{ 0, 0, 85, 100 };

	lastUpdate_ = sdlutils().currRealTime();
}

FramedImage::FramedImage(Texture* tex, int spritesInRow, int spritesInCol) : 
	tr_(), tex_(tex), frameRate_(50.f)
{
	recorte_ = new SDL_Rect{ 0, 0, tex->width() / spritesInRow, tex->height() / spritesInCol };

	lastUpdate_ = sdlutils().currRealTime();
}

FramedImage::~FramedImage() {

	delete recorte_;
}

void FramedImage::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr); 

}

void FramedImage::update()
{
	//If enough time passes...
	if (lastUpdate_ + frameRate_ <= sdlutils().currRealTime())
	{
		recorte_->x += recorte_->w;

		if (recorte_->x >= tex_->width());
		{
			recorte_->x = 0;

			recorte_->y += recorte_->h;

			if (recorte_->y >= tex_->height())
			{
				recorte_->y = 0;
			}
		}

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
