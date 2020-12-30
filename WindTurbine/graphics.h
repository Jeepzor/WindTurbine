#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <string>

namespace wind {
	class Graphics {
	public:
		Graphics();
		void rectangle(std::string mode, int x, int y, int width, int height);
	private:

	};

	extern Graphics graphics;
}

#endif
