#ifndef ROCK_H
#define ROCK_H


#include "../wind.h"

class Rock : public wind::Entity {
public:
	static Rock* getInstance(wind::PhysicsWorld* physics_world, double x, double y, double angle) {
		return new Rock(physics_world, x, y, angle);
	}

	void draw()override;
	void update(double dt)override;
private:
	Rock(wind::PhysicsWorld* world, double x, double y, double angle);
	Rock(const Rock& other) = delete;
	const Rock& operator=(const Rock& other) = delete;

	void syncCollider();

	double width = 0;
	double height = 0;
	double angle = 0;
	double xVel = 0;
	double yVel = 0;
	double speed = 100;

	wind::Collider* collider;
	wind::Voxel* asset;
};

#endif

