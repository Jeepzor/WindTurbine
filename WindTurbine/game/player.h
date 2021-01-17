#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>

#include "../wind.h"

class Player : public wind::Entity {
public:
	Player(wind::PhysicsWorld* world);
	void draw()override;
	void update(double dt)override;
	void takeDamage();
	int getHealth() { return health; }
	double getAngle()const { return aimAngle; };
	double getShipAngle()const { return shipAngle; };
	double getLaunchX() const;
	double getLaunchY() const;
	void reset();

private:
	void updateThrusters();
	void updateAim();
	void reduceDamageAlpha(double dt);
	void checkAlive();

	double width = 0;
	double height = 0;
	double weaponWidth = 0;
	double weaponHeight = 0;

	double weaponX;
	double weaponY;
	double lifeTimer = 0;
	double aimAngle = 0;
	double shipAngle = 0;
	double damageAlpha = 0;

	int health = 10;

	wind::Collider* collider;
	wind::Voxel* shipImg;
	wind::Voxel* weaponImg;
	wind::Image* damaged;
	wind::ParticleEmitter* leftThruster;
	wind::ParticleEmitter* rightThruster;
};

#endif

