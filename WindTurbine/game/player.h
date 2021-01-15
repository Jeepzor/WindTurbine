#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>

#include "../wind.h"

class Player : public wind::Entity {
public:
	Player(wind::PhysicsWorld* world);
	void draw()override;
	void update(double dt)override;
	double getAngle() const;
	double getLaunchX() const;
	double getLaunchY() const;
private:
	void updateThrusters();
	void updateAim();
	double width = 0;
	double height = 0;
	double weaponWidth = 0;
	double weaponHeight = 0;

	double weaponX;
	double weaponY;
	double aimAngle = 0;


	wind::Collider* collider;
	wind::Voxel* shipImg;
	wind::Voxel* weaponImg;

	wind::ParticleEmitter* leftThruster;
	wind::ParticleEmitter* rightThruster;
	
};

#endif

