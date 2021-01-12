#include "image.h"

namespace wind {

	Image::~Image() {
		SDL_DestroyTexture(asset);
	}
}