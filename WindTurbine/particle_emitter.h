#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <string>
#include <vector>

#include "image.h"
#include "particle.h"
#include "color.h"


namespace wind {
	class ParticleEmitter
	{
	public:
		ParticleEmitter(std::string path, double particle_life, double emission, double duration);
		void update(double dt);

		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7);
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7, double r8, double g8, double b8, double a8);

		void setDirection(double angle);
		void setPosition(double x, double y);
		void draw();
		void refresh();
		
		double getX();
		double getY();
		
	private:
		void emit(); // emits a particle

		void setStartColor(double r, double g, double b, double a); 
		double lifeTimer; //How long the emitter should emit particles.
		double particleLife; //Duration of a single particle.
		double emissionRate; // Duration between each particle
		double emissionTimer; // Time passed since last particle
		double emissionAmount; // Particle per second

		int maxParticles;
		int currentParticles;
		int nextParticle;
		
		double xPos;
		double yPos;

		double duration;
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

		Image* asset;

		std::vector<Particle*> particles;
		std::vector<Color*> colors;
	};
}

#endif