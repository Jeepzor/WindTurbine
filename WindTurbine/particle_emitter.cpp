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
		spread = 0;

		startRed = 255;
		startGreen = 255;
		startBlue = 255;
		startAlpha = 255;

		endRed = 0;
		endGreen = 0;
		endBlue = 0;
		endAlpha = 0;

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
				current_particle->setColor(startRed, startBlue, startGreen, startAlpha);
				current_particle->setTargetColor(endRed, endBlue, endGreen, endAlpha);
				current_particle->resetPosition(xPos, yPos);
				current_particle->setLifeTimer(particleLife);
				current_particle->setVelcoity(math.random() * 200 - 100, math.random() * 200 - 100);
			}
		}
	}
	
	void ParticleEmitter::emit() {
		Particle* next_particle = new Particle(path, xPos, yPos, particleLife);
		next_particle->setColor(startRed, startBlue, startGreen, startAlpha);
		next_particle->setTargetColor(endRed, endBlue, endGreen, endAlpha);
		next_particle->setVelcoity(math.random() * 200 - 100, math.random() * 200 - 100);
		particles.push_back(next_particle);
	}
}