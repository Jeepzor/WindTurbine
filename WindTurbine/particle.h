#ifndef PARTICLE_H
#define PARTICLE_H

#include<vector> 
#include <memory>

#include "image.h"
#include "color.h"

namespace wind {
	class Particle 
	{
	public:
		friend class ParticleEmitter;
		~Particle();
	private:
		void setTargetColor(std::vector<std::shared_ptr<Color>>& target, int size);
		Particle(double xPos, double yPos, double life_time);
		void update(double dt);
		void draw(Image* asset);
		void setColor(double r, double g, double b, double a);
		void setVelcoity(double xVel, double yVel);
		void resetPosition(double x, double y);
		void refresh();
		bool alive() { return lifeTimer < duration; };
		void move(double dt);
		void updateLife(double dt);
		void tweenColors(double dt);
		void addColor(Color* new_color);

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
		std::vector<std::shared_ptr<wind::Color>> targetColors;
		//Color** targetColors;

	};
}

#endif
