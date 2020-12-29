#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>

#include "wind_turbine.h"

class Player : public wind::Entity {
public:
	Player();
	void draw()override;
	void update(double dt)override;
	
private:
	void move(double dt);
	void applyFriction(double dt);
	void applyVelocity(double dt);
	void updateDirection();

	double xVel;
	double yVel;
	double acceleration;
	double friction;
	double maxSpeed;
	double dir;
	wind::Animation* sprite;
};

#endif

