#include <math.h>

#include "particle_emitter.h"
#include "math.h"

namespace wind {
	ParticleEmitter::ParticleEmitter(std::string asset_path, double x, double y) {
		xPos = x;
		yPos = y;
		lifeTimer = 10000;

		path = asset_path;

		emissionAmount = 100; // Particles per second
		emissionTimer = 0; // Particles per second
		emissionRate = 1 / emissionAmount; // Time between particles
		particleLife = 2; //Particle duration

		maxParticles = particleLife * emissionAmount;
		currentParticles = 0;
		direction = 0;
		spread = math.pi() / 4;

		startRed = 255;
		startGreen = 255;
		startBlue = 255;
		startAlpha = 255;

		endRed = 0;
		endGreen = 0;
		endBlue = 0;
		endAlpha = 0;

		speedMin = 10;
		speedMax = 100;
	}

	void ParticleEmitter::setDirection(double new_angle) {
		direction = new_angle;
	}

	void ParticleEmitter::setStartColor(double r, double g, double b, double a) {
		startRed = r;
		startGreen = g;
		startBlue = b;
		startAlpha = a;
	}
	
	void ParticleEmitter::setEndColor(double r, double g, double b, double a) {
		endRed = r;
		endGreen = g;
		endBlue = b;
		endAlpha = a;
	}

	void ParticleEmitter::update(double dt) {
		emissionTimer += dt;
		if (emissionTimer > emissionRate) {
			if (currentParticles < maxParticles) {
				currentParticles += 1;
				emissionTimer = 0;
				emit();
			}
			else {
				refresh();
			}
		}
		
		for (auto current_particle : particles) {
			current_particle->update(dt);
		}
	}
	
	void ParticleEmitter::draw() {
		for (auto current_particle : particles) {
			if (current_particle->alive()) {
				current_particle->draw();
			}
		}
	}

	void ParticleEmitter::refresh() {
		bool found = false;
		for (auto current_particle : particles) {
			if (!current_particle->alive() && !found) {
				found = true;
				current_particle->resetPosition(xPos, yPos);
				current_particle->setColor(startRed, startGreen, startBlue, startAlpha);
				current_particle->setTargetColor(endRed, endGreen, endBlue, endAlpha);
				
				double speed_current = (speedMax - speedMin) * math.random() + speedMin;
				double x_vel = speed_current * std::cos(direction - spread / 2 + spread * math.random());
				double y_vel = speed_current * std::sin(direction - spread / 2 + spread * math.random());
				current_particle->setVelcoity(x_vel, y_vel);

				current_particle->setLifeTimer(particleLife);
			}
		}
	}
	
	void ParticleEmitter::emit() {
		Particle* next_particle = new Particle(path, xPos, yPos, particleLife);
		next_particle->setColor(startRed, startGreen, startBlue, startAlpha);
		next_particle->setTargetColor(endRed, endGreen, endBlue, endAlpha);
		double speed_current = (speedMax - speedMin) * math.random() + speedMin;
		double x_vel = speed_current * std::cos(direction - spread / 2 + spread * math.random());
		double y_vel = speed_current * std::sin(direction - spread / 2 + spread * math.random());

		next_particle->setVelcoity(x_vel, y_vel);
		particles.push_back(next_particle);
	}
}