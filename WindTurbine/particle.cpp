#include <string>

#include "particle.h"
#include "wind_turbine.h"
#include "math.h"
#include "color.h"
#include "graphics.h"

namespace wind {
	Particle::Particle(double x, double y, double life_time) {
		xPos = x;
		yPos = y;
		lifeTimer = 0;
		duration = life_time;
		red = 0;
		green = 0;
		blue = 0;
		alpha = 255;

		xVel = 0;
		yVel = 0;

		targetColors.push_back(new Color(0, 0, 0, 0));
	}

	void Particle::update(double dt) {
		updateLife(dt);

		if (lifeTimer < duration) {
			move(dt);
			tweenColors(dt);
		}
	}

	void Particle::setVelcoity(double x, double y) {
		xVel = x;
		yVel = y;
	}
	
	void Particle::resetPosition(double x, double y) {
		xPos = x;
		yPos = y;
	}
	
	void Particle::resetLifeTimer(double time) {
		lifeTimer = 0;
	}

	void Particle::move(double dt) {
		xPos += xVel * dt;
		yPos += yVel * dt;
	}

	void Particle::tweenColors(double dt) {
		//How many different colors it needs to loop through in it's lifetime.
		double amount = targetColors.size();
		//How much time it should spend on each color.
		double interval = duration / amount;
		
		//Which color is it currently tweening towards
		int number = static_cast<int>(lifeTimer / interval); 

		number = math.clamp(0, amount - 1, number);

		//Get the target colors
		double targetRed = targetColors[number]->red;
		double targetGreen = targetColors[number]->green;
		double targetBlue = targetColors[number]->blue;
		double targetAlpha = targetColors[number]->alpha;

		//Get the time remaining until it will get a new color
		double timeLeft = interval - std::fmod(lifeTimer, interval);

		//Calculate the speed that it needs to tween at, in order to reach the target in time.
		double red_speed = (targetRed - red) / timeLeft;
		red += red_speed * dt;
		
		double green_speed = (targetGreen - green) / timeLeft;
		green += green_speed * dt;
		
		double blue_speed = (targetBlue - blue) / timeLeft;
		blue += blue_speed * dt;
		
		double alpha_speed = (targetAlpha - alpha) / timeLeft;
		alpha += alpha_speed * dt;

		//Clamp the colors to stay within the 0-255 range.
		red = math.clamp(0, 255, red);
		green = math.clamp(0, 255, green);
		blue = math.clamp(0, 255, blue);
		alpha = math.clamp(0, 255, alpha);
	}
	
	void Particle::updateLife(double dt) {
		lifeTimer += dt;
	}

	void Particle::setColor(double r, double g, double b, double a) {
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}
	
	void Particle::setTargetColor(std::vector<Color*> target) {
		if (!target.empty()) {
			targetColors.clear();
			targetColors = target;
		}
	}

	void Particle::draw(Image* asset) {
		asset->draw(xPos, yPos, red, green, blue, alpha);
	}
}