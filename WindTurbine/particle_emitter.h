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
		/// <summary>
		/// Initialize Particle Emitter.
		/// </summary>
		/// <param name="path">File-Path to an image.png.</param>
		/// <param name="duration">Sets the duration for the emitter. Passing in '0' makes it infinite</param>
		/// <param name="buffer">Maximum number of particles that can be active at any given moment.</param>
		ParticleEmitter(std::string path, double duration, int buffer);

		///Destructor
		~ParticleEmitter();

		//Update the emitter, pass in delta-time.
		void update(double dt);

		/// <summary>
		/// Set the direction of the emitter in radians.
		/// </summary>
		/// <param name="angle"> = in radians</param>
		void setDirection(double angle);

		/// <summary>
		/// Set the spread of the emitter in radians.
		/// </summary>
		/// <param name="amount"> = in radians</param>
		void setSpread(double amount);

		/// <summary>
		/// Set the speed of each particle.
		/// </summary>
		/// <param name="speed"> = pixels per second.</param>
		void setSpeed(double speed);

		/// <summary>
		/// Set the minimum and maximum speed of each particle. Particles set their speed to a random number which is clamped by the parameters.
		/// </summary>
		/// <param name="min"> = Minimum pixels per second.</param>
		/// <param name="max"> = Maximum pixels per second.</param>
		void setSpeed(double min, double max);
		
		/// <summary>
		/// Sets the X and Y position of the emitter. This does not affect particles which already have been spawned.
		/// </summary>
		/// <param name="x">= Position on the X-axis.</param>
		/// <param name="y">= Position on the Y-axis.</param>
		void setPosition(double x, double y);

		/// <summary>
		/// Sets the amount of particles that are emitted per second.
		/// </summary>
		/// <param name="amount"> = Particles per second.</param>
		void setEmission(double amount);

		/// <summary>
		/// Sets the life time of each particle.
		/// </summary>
		/// <param name="duration"> = seconds of duration.</param>
		void setParticleLife(double duration);
	
		void draw(); //Draws all particles
		
		double getX(); //Returns the X - position of the emitter.
		double getY(); //Returns the Y - position of the emitter.

		// Pass in sets of 4 arguments (minimum of 2 sets, maximum of 8 sets) which represents an RGBA-value. The particle will evenly interpolate to each of the colors (in the passed in order).
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2); 
		// Pass in sets of 4 arguments (minimum of 2 sets, maximum of 8 sets) which represents an RGBA-value. The particle will evenly interpolate to each of the colors (in the passed in order).
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3); 
		// Pass in sets of 4 arguments (minimum of 2 sets, maximum of 8 sets) which represents an RGBA-value. The particle will evenly interpolate to each of the colors (in the passed in order).
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4); 
		// Pass in sets of 4 arguments (minimum of 2 sets, maximum of 8 sets) which represents an RGBA-value. The particle will evenly interpolate to each of the colors (in the passed in order).
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5); 
		// Pass in sets of 4 arguments (minimum of 2 sets, maximum of 8 sets) which represents an RGBA-value. The particle will evenly interpolate to each of the colors (in the passed in order).
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6);
		// Pass in sets of 4 arguments (minimum of 2 sets, maximum of 8 sets) which represents an RGBA-value. The particle will evenly interpolate to each of the colors (in the passed in order).
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7); 
		// Pass in sets of 4 arguments (minimum of 2 sets, maximum of 8 sets) which represents an RGBA-value. The particle will evenly interpolate to each of the colors (in the passed in order).
		void setColors(double r, double g, double b, double a, double r2, double g2, double b2, double a2, double r3, double g3, double b3, double a3, double r4, double g4, double b4, double a4, double r5, double g5, double b5, double a5, double r6, double g6, double b6, double a6, double r7, double g7, double b7, double a7, double r8, double g8, double b8, double a8); 
		
	private:
		void emit(); // emits a particle
		void refresh(); //Recycles dead particles from the pool.

		void setStartColor(double r, double g, double b, double a); //Sets the initial color values of just spawned particles
		double lifeTimer = 0; //How long the emitter should emit particles.
		double particleLife = 0; //Duration of a single particle.
		double emissionRate = 0; // Duration between each particle
		double emissionTimer = 0; // Time passed since last particle
		double emissionAmount = 0; // Particle per second

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

		std::vector<std::shared_ptr<wind::Particle>> particles;;
		std::vector<std::shared_ptr<wind::Color>> colors;;
	};
}

#endif