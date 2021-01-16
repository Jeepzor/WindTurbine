#ifndef STAR_H
#define STAR_H


#include "../wind.h"

class Star : public wind::Entity {
public:
	static Star* getInstance(double x, double y) {
		return new Star(x, y);
	}
	~Star() override;
	void draw()override;
	void update(double dt)override;
private:
	Star(double x, double y);
	Star(const Star& other) = delete;
	const Star& operator=(const Star& other) = delete;

	wind::Image* asset;

	double scale;
	
	double speed;
	double xVel = 0;
	double yVel = 0;
};

#endif
