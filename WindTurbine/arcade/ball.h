#ifndef BALL_H
#define BALL_H

#include <algorithm>
#include "../wind.h"


class Ball : public wind::Entity {
public:
	void draw()override;
	void update(double dt)override;
	static Ball* getInstance(wind::PhysicsWorld* world, double x, double y) {
		return new Ball(world, x, y);
	}

	double getX() const override;
	double getY() const override;
	void setVelocity(double x, double y);
	void bounce();

private:
	Ball(wind::PhysicsWorld* world, double x, double y);
	Ball(const Ball& other) = delete;
	const Ball& operator=(const Ball& other) = delete;

	void applyFriction(double dt);
	void applyVelocity();
	void syncPosition();
	bool allowed = true;
	double xVel;
	double yVel;
	double friction;
	double elasticity;
	double width;
	double height;

	wind::Collider* collider;
	wind::Image* asset;

};

#endif