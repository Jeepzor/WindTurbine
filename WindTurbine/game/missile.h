#ifndef MISSILE_H
#define MISSILE_H


#include "../wind.h"

class Missile : public wind::Entity {
public:
	static Missile* getInstance(wind::PhysicsWorld* physics_world, std::vector<wind::Entity*> &entities, double x, double y, double angle) {
		return new Missile(physics_world, entities, x, y, angle);
	}

	void draw()override;
	void update(double dt)override;
private:
	Missile(wind::PhysicsWorld* world, std::vector<wind::Entity*> &entities, double x, double y, double angle);
	Missile(const Missile& other) = delete;
	const Missile& operator=(const Missile& other) = delete;

	void explode();
	void syncCollider();
	void updateThruster(double dt);

	double width = 0;
	double height = 0;
	double angle = 0;
	double xVel = 0;
	double yVel = 0;
	double speed = 100;

	std::vector<wind::Entity*>* entities;
	wind::Collider* collider;
	wind::Voxel* asset;
	wind::ParticleEmitter* thruster;
};

#endif

