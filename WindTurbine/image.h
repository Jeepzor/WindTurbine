#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "drawable.h"

namespace wind {
	class Image : public Drawable {
	public:
		~Image()override;

		static Image* getInstance(std::string path) {
			return new Image(path);
		}

	private:
		Image(std::string path) : Drawable(path) {};
		Image(const Image& other) = delete;
		const Image& operator=(const Image& other) = delete;
	};

}
#endif