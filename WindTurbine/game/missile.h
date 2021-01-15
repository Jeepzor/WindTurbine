#ifndef MISSILE_H
#define MISSILE_H


#include "../wind.h"

class PlayModule;

class Missile : public wind::Entity {
public:
	static Missile* getInstance(PlayModule* playModule, double x, double y, double angle) {
		return new Missile(playModule, x, y, angle);
	}

	void draw()override;
	void update(double dt)override;
private:
	Missile(PlayModule* playModule, double x, double y, double angle);
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

	PlayModule* playModule;
	wind::Collider* collider;
	wind::Voxel* asset;
	wind::ParticleEmitter* thruster;
};

#endif

