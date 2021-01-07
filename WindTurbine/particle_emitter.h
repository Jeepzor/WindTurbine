#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <string>
#include <vector>

#include "image.h"
#include "particle.h"


namespace wind {
	class ParticleEmitter
	{
	public:
		ParticleEmitter(std::string path, double xPos, double yPos);
		void update(double dt);
		void setStartColor(double r, double g, double b, double a);
		void setEndColor(double r, double g, double b, double a);
		void setDirection(double angle);
		void draw();
		void refresh();
		
	private:
		void emit();

		double lifeTimer; //How long the emitter should emit particles.
		double particleLife; //Duration of a single particle.
		double emissionRate; // Duration between each particle
		double emissionTimer; // Time passed since last particle
		double emissionAmount; // Particle per second

		int maxParticles;
		int currentParticles;
		
		double xPos;
		double yPos;

		double direction;
		double spread;

		double startRed;
		double startGreen;
		double startBlue;
		double startAlpha;
		
		double endRed;
		double endGreen;
		double endBlue;
		double endAlpha;

		double speedMin;
		double speedMax;

		std::string path;

		std::vector<Particle*> particles;
	};
}

#endif