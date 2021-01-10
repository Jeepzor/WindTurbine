#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <string>
#include <vector>

#include "image.h"
#include "particle.h"
#include "color.h"
#include "math.h"


namespace wind {
	class ParticleEmitter
	{
	public:
		ParticleEmitter(std::string path, double particle_life, double emission, double duration);
		void update(double dt);

		void setDirection(double angle);
		void setSpread(double amount);
		void setSpeed(double speed);
		void setSpeed(double min, double max);
		void setPosition(double x, double y);
		void draw();
		void refresh();
		
		double getX();
		double getY();

		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7, double r8, double g8, double b8, double a8);
		
	private:
		void emit(); // emits a particle

		void setStartColor(double r, double g, double b, double a); 
		double lifeTimer = 0; //How long the emitter should emit particles.
		double particleLife; //Duration of a single particle.
		double emissionRate; // Duration between each particle
		double emissionTimer = 0; // Time passed since last particle
		double emissionAmount; // Particle per second

		int maxParticles;
		int currentParticles = 0;
		int nextParticle = 0;
		int colorCount = 1;
		
		double xPos = 0;
		double yPos = 0;

		double duration;
		double direction = 0;
		double spread = math.pi() * 2;

		double startRed = 255;
		double startGreen = 255;
		double startBlue = 255;
		double startAlpha = 255;
		
		double endRed = 0;
		double endGreen = 0;
		double endBlue = 0;
		double endAlpha = 0;

		double speedMin = 0;
		double speedMax = 0;

		Image* asset;

		Particle** particles; 
		Color** colors; 
	};
}

#endif