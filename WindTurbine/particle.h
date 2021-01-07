#ifndef PARTICLE_H
#define PARTICLE_H
#include "image.h"

namespace wind {
	class Particle : public Image
	{
	public:
		Particle(std::string path, double xPos, double yPos, double life_time);

		void draw() override;
		void setColor(double r, double g, double b, double a);
		void setTargetColor(double r, double g, double b, double a);
		void setVelcoity(double xVel, double yVel);
		void resetPosition(double x, double y);
		void setLifeTimer(double time);
		void update(double dt);
		bool alive() { return lifeTimer > 0; };
	private:
		void move(double dt);
		void updatePosition();
		void updateLife(double dt);
		void tweenColors(double dt);

		double lifeTimer;

		double xVel;
		double yVel;

		double xPos;
		double yPos;

		double red;
		double green;
		double blue;
		double alpha;	
		
		double targetRed;
		double targetGreen;
		double targetBlue;
		double targetAlpha;

	};
}

#endif
