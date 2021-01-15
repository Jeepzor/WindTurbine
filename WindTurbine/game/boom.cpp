#include <string>
#include "boom.h"

Boom::Boom(double x, double y) {
	xPos = x;
	yPos = y;

	//Particles
	particles = new wind::ParticleEmitter("game/assets/white_particle.png", 0.5, 600);
	particles->setDirection(wind::math.pi() / 2);
	particles->setSpread(7);
	particles->setParticleLife(2);
	particles->setEmission(300);
	particles->setSpeed(20, 70);
	particles->setPosition(xPos, yPos);
	particles->setColors(254, 253, 189, 255, 254, 201, 78, 255, 176, 57, 0, 255, 0, 0, 0, 100, 0, 0, 0, 0);

	wind::hibernate.it([=]() {this->destroy(); }, 2.5);
}

Boom::~Boom() {
	std::cout << "boom deleted";
	delete particles;
}


void Boom::update(double dt) {
	particles->update(dt);
}


void Boom::draw() {
	particles->draw();
}