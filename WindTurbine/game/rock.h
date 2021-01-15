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
	void setFalling() { falling = true; };
private:
	Rock(wind::PhysicsWorld* world, double x, double y, double angle);
	Rock(const Rock& other) = delete;
	const Rock& operator=(const Rock& other) = delete;

	void fall(double dt);
	void syncCollider();

	bool falling = false;

	double scale;
	double width = 0;
	double height = 0;
	double angle = 0;
	double speed = 100;
	double xVel = 0;
	double yVel = 0;
	double rVel = 0;
	double rotation = 0;

	wind::Collider* collider;
	wind::Voxel* asset;
};

#endif

