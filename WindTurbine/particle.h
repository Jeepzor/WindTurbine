#ifndef PARTICLE_H
#define PARTICLE_H

#include<vector> 

#include "image.h"
#include "color.h"

namespace wind {
	class Particle 
	{
	public:
		Particle(double xPos, double yPos, double life_time);

		void draw(Image* asset);
		void setColor(double r, double g, double b, double a);
		void setTargetColor(Color* target[], int size);
		void setVelcoity(double xVel, double yVel);
		void resetPosition(double x, double y);
		void resetLifeTimer(double time);
		void update(double dt);
		bool alive() { return lifeTimer < duration; };
	private:
		void move(double dt);
		void updateLife(double dt);
		void tweenColors(double dt);

		double duration;
		double lifeTimer;
		double colorCount;
		double currentColor;
		double interval; //How much time it should spend on each color. 

		double xVel;
		double yVel;

		double xPos;
		double yPos;

		double red;
		double green;
		double blue;
		double alpha;
		Color** targetColors;

	};
}

#endif
