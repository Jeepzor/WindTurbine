#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "drawable.h"

namespace wind {
	class Image : public Drawable {
	public:
		~Image()override;

		/// <summary>
		/// Used to instantiate new Animations.
		/// </summary>
		/// <param name="path"> = Path to the file</param>
		/// <returns>Pointer to an Image</returns>
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