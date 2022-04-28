// This file is part of the course TPV2@UCM - Samir Genaim

#include "Image.h"

#include <cassert>

#include "../game/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../game/Manager.h"

Image::Image() :
		tex_() {
}

Image::Image(Texture *tex) :
		tex_(tex) {
}

Image::~Image() {
}
