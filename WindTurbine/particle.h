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
		~Particle();

		void draw(Image* asset);
		void setColor(double r, double g, double b, double a);
		void setTargetColor(Color* target[], int size);
		void setVelcoity(double xVel, double yVel);
		void resetPosition(double x, double y);
		void refresh();
		void update(double dt);
		bool alive() { return lifeTimer < duration; };
	private:
		void move(double dt);
		void updateLife(double dt);
		void tweenColors(double dt);

		int colorCount = 1;
		
		double duration;
		double lifeTimer;
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

		double red_speed = 0;
		double green_speed = 0;
		double blue_speed = 0;
		double alpha_speed = 0;
		Color** targetColors;

	};
}

#endif
