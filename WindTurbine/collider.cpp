#include "collider.h"

namespace wind {
	Collider::Collider(double x, double y, int collider_width, int collider_height) {
		width = collider_width;
		height = collider_height;
		xPos = x;
		yPos = y;
	}
}
