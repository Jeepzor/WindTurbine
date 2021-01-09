#include <math.h>

#include "particle_emitter.h"
#include "math.h"

namespace wind {
	ParticleEmitter::ParticleEmitter(std::string asset_path, double particle_life, double emission, double emitter_duration) {
		xPos = 0;
		yPos = 0;
		duration = emitter_duration;

		asset = new Image(asset_path);

		emissionAmount = emission; // Particles per second
		emissionTimer = 0; // Particles per second
		emissionRate = 1 / emissionAmount; // Time between particles
		particleLife = particle_life; //Particle duration

		maxParticles = particleLife * emissionAmount; // Maximum allowed particles
		currentParticles = 0; //Amount of particles currently in existance
		nextParticle = 0; // Next particle to refresh
	
		particles = new Particle * [maxParticles];
		direction = 0;
		spread = math.pi() / 4;

		startRed = 255;
		startGreen = 255;
		startBlue = 255;
		startAlpha = 255;

		speedMin = 60;
		speedMax = 100;
	}

	void ParticleEmitter::setDirection(double new_angle) {
		direction = new_angle;
	}

	double ParticleEmitter::getX() {
		return xPos;
	}	
	
	double ParticleEmitter::getY() {
		return yPos;
	}
	
	void ParticleEmitter::setPosition(double x, double y) {
		xPos = x;
		yPos = y;
	}

	void ParticleEmitter::update(double dt) {
		emissionTimer += dt;
		int particles_per_frame = static_cast<int>(dt / emissionRate);
		if (emissionTimer > emissionRate) {
			for (int i = 1; i <= particles_per_frame; i++){
				if (currentParticles < maxParticles) {
					emissionTimer = 0;
					emit();
					currentParticles += 1;
				}
				else {
					refresh();
				}
			}
		}
		for (int i = 0; i < currentParticles; i++) {
			particles[i]->update(dt);
		}
	}
	
	void ParticleEmitter::draw() {

		for (int i = 0; i < currentParticles; i++) {
			if (particles[i]->alive()) { // TODO, can this be skipped for performance?
				particles[i]->draw(asset);
			}
		}
	}

	void ParticleEmitter::refresh() {
		particles[nextParticle]->resetPosition(xPos, yPos);
		particles[nextParticle]->setColor(startRed, startGreen, startBlue, startAlpha);
		particles[nextParticle]->setTargetColor(colors);
				
		double speed_current = (speedMax - speedMin) * math.random() + speedMin;
		double x_vel = speed_current * std::cos(direction - spread / 2 + spread * math.random());
		double y_vel = speed_current * std::sin(direction - spread / 2 + spread * math.random());
		particles[nextParticle]->setVelcoity(x_vel, y_vel);

		particles[nextParticle]->resetLifeTimer(particleLife);

		if (nextParticle < (maxParticles - 1)) {
			nextParticle++;
		}
		else {
			nextParticle = 0;
		}
	}
	
	void ParticleEmitter::emit() {
		Particle* next_particle = new Particle(xPos, yPos, particleLife);
		next_particle->setColor(startRed, startGreen, startBlue, startAlpha);
		next_particle->setTargetColor(colors);
		double speed_current = (speedMax - speedMin) * math.random() + speedMin;
		double x_vel = speed_current * std::cos(direction - spread / 2 + spread * math.random());
		double y_vel = speed_current * std::sin(direction - spread / 2 + spread * math.random());
		next_particle->setVelcoity(x_vel, y_vel);

		particles[currentParticles] = next_particle;
	}

	void ParticleEmitter::setStartColor(double r, double g, double b, double a) {
		startRed = r;
		startGreen = g;
		startBlue = b;
		startAlpha = a;
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2) {
		setStartColor(r, g, b, a);
		colors.push_back(new Color(r2, g2, b2, a2));
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3) {
		setStartColor(r, g, b, a);
		colors.push_back(new Color(r2, g2, b2, a2));
		colors.push_back(new Color(r3, g3, b3, a3));
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4) {
		setStartColor(r, g, b, a);
		colors.push_back(new Color(r2, g2, b2, a2));
		colors.push_back(new Color(r3, g3, b3, a3));
		colors.push_back(new Color(r4, g4, b4, a4));
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5) {
		setStartColor(r, g, b, a);
		colors.push_back(new Color(r2, g2, b2, a2));
		colors.push_back(new Color(r3, g3, b3, a3));
		colors.push_back(new Color(r4, g4, b4, a4));
		colors.push_back(new Color(r5, g5, b5, a5));
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6) {
		setStartColor(r, g, b, a);
		colors.push_back(new Color(r2, g2, b2, a2));
		colors.push_back(new Color(r3, g3, b3, a3));
		colors.push_back(new Color(r4, g4, b4, a4));
		colors.push_back(new Color(r5, g5, b5, a5));
		colors.push_back(new Color(r6, g6, b6, a6));
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7) {
		setStartColor(r, g, b, a);
		colors.push_back(new Color(r2, g2, b2, a2));
		colors.push_back(new Color(r3, g3, b3, a3));
		colors.push_back(new Color(r4, g4, b4, a4));
		colors.push_back(new Color(r5, g5, b5, a5));
		colors.push_back(new Color(r6, g6, b6, a6));
		colors.push_back(new Color(r7, g7, b7, a7));
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7, double r8, double g8, double b8, double a8) {
		setStartColor(r, g, b, a);
		colors.push_back(new Color(r2, g2, b2, a2));
		colors.push_back(new Color(r3, g3, b3, a3));
		colors.push_back(new Color(r4, g4, b4, a4));
		colors.push_back(new Color(r5, g5, b5, a5));
		colors.push_back(new Color(r6, g6, b6, a6));
		colors.push_back(new Color(r7, g7, b7, a7));
		colors.push_back(new Color(r8, g8, b8, a8));
	}
}