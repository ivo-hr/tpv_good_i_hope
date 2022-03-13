#include "FramedImage.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

FramedImage::FramedImage() :
		tr_(), tex_(), counter_(5.f) {
}

FramedImage::FramedImage(Texture *tex) :
		tr_(), tex_(tex), counter_(5.f) {
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

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//Creamos el vector del cual sacaremos todos los sprites por separado
			frames_.push_back(new Vector2D(i, j));
		}
	}
}

void FramedImage::update()
{
	counter_--;
	if (counter_ <= 0)
	{
		currIndex_++;
		if (currIndex_ == frames_.size())
			currIndex_ = 0;
		recorte_->x = 85 * frames_[currIndex_]->getX();
		recorte_->y = 100 * frames_[currIndex_]->getY();
		counter_ = 5.f;
	}
}

void FramedImage::render() {

	SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getWidth(),
			tr_->getHeight());

	assert(tex_ != nullptr);
	tex_->render(*recorte_, dest, tr_->getRot(), nullptr, SDL_FLIP_NONE);

}
