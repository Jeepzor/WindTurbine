#include <math.h>

#include "particle_emitter.h"
#include "math.h"

namespace wind {
	ParticleEmitter::ParticleEmitter(std::string asset_path, double emitter_duration, double buffer) {
		if (emitter_duration == 0) {
			duration = 99999999999999999;
		}
		else {
			duration = emitter_duration;
		}

		asset = Image::getInstance(asset_path);

		maxParticles = buffer; // Maximum allowed particles
	
		particles = new Particle * [maxParticles];

		Color* temp_color = new Color(0, 0, 0, 0);
		colors = new Color * [1];
		colors[0] = temp_color;
	}
	
	void ParticleEmitter::setEmission(double amount) {
		emissionAmount = amount;
		emissionRate = 1 / emissionAmount;
	}
	
	void ParticleEmitter::setParticleLife(double duration) {
		particleLife = duration;
	}

	void ParticleEmitter::setDirection(double new_angle) {
		direction = new_angle;
	}
	
	void ParticleEmitter::setSpread(double amount) {
		spread = amount;
	}

	void ParticleEmitter::setSpeed(double speed) {
		setSpeed(speed, speed);
	}

	void ParticleEmitter::setSpeed(double min, double max) {
		speedMin = min;
		speedMax = max;
	}

	void ParticleEmitter::setPosition(double x, double y) {
		xPos = x;
		yPos = y;
	}

	double ParticleEmitter::getX() {
		return xPos;
	}	
	
	double ParticleEmitter::getY() {
		return yPos;
	}
	
	

	void ParticleEmitter::update(double dt) {
		emissionTimer += dt;
		int particles_per_frame = static_cast<int>(dt / emissionRate) + 1;
		if (emissionTimer > emissionRate) {
			emissionTimer = 0;
			for (int i = 1; i <= particles_per_frame; i++){
				if (currentParticles < maxParticles) {
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
			particles[i]->draw(asset);
		}
	}

	void ParticleEmitter::refresh() {
		particles[nextParticle]->resetPosition(xPos, yPos);
		particles[nextParticle]->setColor(startRed, startGreen, startBlue, startAlpha);
		particles[nextParticle]->setTargetColor(colors, colorCount);
				
		double speed_current = (speedMax - speedMin) * math.random() + speedMin;
		double angle = (direction - spread / 2) + (spread * math.random());
		double x_vel = speed_current * std::cos(angle);
		double y_vel = speed_current * std::sin(angle);
		particles[nextParticle]->setVelcoity(x_vel, y_vel);

		particles[nextParticle]->refresh();

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
		next_particle->setTargetColor(colors, colorCount);
		double speed_current = (speedMax - speedMin) * math.random() + speedMin;
		double angle = (direction - spread / 2) + (spread * math.random());
		double x_vel = speed_current * std::cos(angle);
		double y_vel = speed_current * std::sin(angle);
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
		Color* temp_color = new Color(r2, g2, b2, a2);
		colors = new Color * [1];
		colors[0] = temp_color;
		colorCount = 1;
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3) {
		setStartColor(r, g, b, a);
		
		colors = new Color * [2];
		colors[0] = new Color(r2, g2, b2, a2);
		colors[1] = new Color(r3, g3, b3, a3);
		colorCount = 2;

	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4) {
		setStartColor(r, g, b, a);

		colors = new Color * [3];
		colors[0] = new Color(r2, g2, b2, a2);
		colors[1] = new Color(r3, g3, b3, a3);
		colors[2] = new Color(r4, g4, b4, a4);
		colorCount = 3;
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5) {
		setStartColor(r, g, b, a);

		colors = new Color * [4];
		colors[0] = new Color(r2, g2, b2, a2);
		colors[1] = new Color(r3, g3, b3, a3);
		colors[2] = new Color(r4, g4, b4, a4);
		colors[3] = new Color(r5, g5, b5, a5);
		colorCount = 4;
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6) {
		setStartColor(r, g, b, a);

		colors = new Color * [5];
		colors[0] = new Color(r2, g2, b2, a2);
		colors[1] = new Color(r3, g3, b3, a3);
		colors[2] = new Color(r4, g4, b4, a4);
		colors[3] = new Color(r5, g5, b5, a5);
		colors[4] = new Color(r6, g6, b6, a6);
		colorCount = 5;
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7) {
		setStartColor(r, g, b, a);

		colors = new Color * [6];
		colors[0] = new Color(r2, g2, b2, a2);
		colors[1] = new Color(r3, g3, b3, a3);
		colors[2] = new Color(r4, g4, b4, a4);
		colors[3] = new Color(r5, g5, b5, a5);
		colors[4] = new Color(r6, g6, b6, a6);
		colors[5] = new Color(r7, g7, b7, a7);
		colorCount = 6;
	}

	void ParticleEmitter::setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7, double r8, double g8, double b8, double a8) {
		setStartColor(r, g, b, a);

		colors = new Color * [7];
		colors[0] = new Color(r2, g2, b2, a2);
		colors[1] = new Color(r3, g3, b3, a3);
		colors[2] = new Color(r4, g4, b4, a4);
		colors[3] = new Color(r5, g5, b5, a5);
		colors[4] = new Color(r6, g6, b6, a6);
		colors[5] = new Color(r7, g7, b7, a7);
		colors[6] = new Color(r8, g8, b8, a8);
		colorCount = 7;
	}
}