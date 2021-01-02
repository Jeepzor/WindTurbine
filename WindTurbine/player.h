#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>

#include "wind_turbine.h"
#include "rectangle_collider.h";
#include "circle_collider.h";
class wind::PhysicsWorld;

class Player : public wind::Entity {
public:
	Player(wind::PhysicsWorld* world);
	void draw()override;
	void update(double dt)override;
	
private:
	void move(double dt);
	void applyFriction(double dt);
	void applyVelocity();
	void syncPosition();
	void updateDirection();

	double xVel;
	double yVel;
	double acceleration;
	double friction;
	double maxSpeed;
	double dir;
	wind::Collider* collider;
	wind::Animation* sprite;
};

#endif

