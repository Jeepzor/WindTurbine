#ifndef COLLIDER_H
#define COLLIDER_H

#include <string>

namespace wind {
	class Collider{
	public:
		Collider(double x, double y, int width, int height);
	private:
		int width;
		int height;
		double yPos;
		double xPos;
	};

}
#endif
