#ifndef MISSILE_H
#define MISSILE_H


#include "../wind.h"

class wind::PhysicsWorld;

class Missile : public wind::Entity {
public:
	static Missile* getInstance(wind::PhysicsWorld* physics_world, double x, double y, double angle) {
		return new Missile(physics_world, x, y, angle);
	}

	void draw()override;
	void update(double dt)override;
private:
	Missile(wind::PhysicsWorld* world, double x, double y, double angle);
	Missile(const Missile& other) = delete;
	const Missile& operator=(const Missile& other) = delete;

	void syncCollider();
	void updateThruster(double dt);

	double width = 0;
	double height = 0;
	double angle = 0;
	double xVel = 0;
	double yVel = 0;
	double speed = 100;

	wind::Collider* collider;
	wind::Voxel* asset;
	wind::ParticleEmitter* thruster;
};

#endif

