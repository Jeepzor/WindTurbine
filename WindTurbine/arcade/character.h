#ifndef CHARACTER_H
#define CHARACTER_H

#include <algorithm>
#include "../wind.h"


class Character : public wind::Entity {
public:
	void draw()override;
	void update(double dt)override;
	static Character* getInstance(wind::PhysicsWorld* world) {
		return new Character(world);
	}

	double getX() const override;
	double getY() const override;
	double getVelX() const;
	double getVelY() const;

private:
	Character(wind::PhysicsWorld* world);
	Character(const Character& other) = delete;
	const Character& operator=(const Character& other) = delete;

	void move(double dt);
	void applyFriction(double dt);
	void applyVelocity();
	void syncPosition();
	void updateDirection();
	void updateAnimation(double dt);

	double xVel;
	double yVel;
	double acceleration;
	double friction;
	double maxSpeed;
	bool goingDown;
	bool isIdle;
	wind::Collider* collider;
	wind::Animation* runUp;
	wind::Animation* runDown;
	wind::Animation* idleUp;
	wind::Animation* idleDown;
};

#endif