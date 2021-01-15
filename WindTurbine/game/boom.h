#ifndef BOOM_H
#define BOOM_H
#include "../wind.h"

class Boom : public wind::Entity {
public:
	static Boom* getInstance(double x, double y) {
		return new Boom(x, y);
	}
	~Boom()override;
	void draw()override;
	void update(double dt)override;
private:
	Boom(double x, double y);
	Boom(const Boom& other) = delete;
	const Boom& operator=(const Boom& other) = delete;

	wind::ParticleEmitter* particles;
};

#endif