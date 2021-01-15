#ifndef MISSILE_H
#define MISSILE_H


#include "../wind.h"

class PlayModule;

class Missile : public wind::Entity {
public:
	static Missile* getInstance(PlayModule* playModule, double x, double y, double angle, std::string input_text) {
		return new Missile(playModule, x, y, angle, input_text);
	}

	~Missile()override;

	void draw()override;
	void update(double dt)override;
private:
	Missile(PlayModule* playModule, double x, double y, double angle, std::string input_text);
	Missile(const Missile& other) = delete;
	const Missile& operator=(const Missile& other) = delete;

	void syncCollider();
	void updateThruster(double dt);
	void checkOutOfBounds();

	double width = 0;
	double height = 0;
	double angle = 0;
	double xVel = 0;
	double yVel = 0;
	double speed = 100;
	int number;
	std::string input;
	PlayModule* playModule;
	wind::Collider* collider;
	wind::Voxel* asset;
	wind::ParticleEmitter* thruster;
};

#endif

