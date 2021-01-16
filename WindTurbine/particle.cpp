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
		std::shared_ptr<wind::Color> smart_ptr();
		addColor(new Color(0, 0, 0, 0));

		currentColor = -1;

		interval = duration / colorCount;
	}

	Particle::~Particle() {

	}

	void Particle::addColor(Color* new_color) {
		std::shared_ptr<wind::Color> smart_ptr(new_color);
		targetColors.push_back(smart_ptr);
	}

	void Particle::update(double dt) {
		updateLife(dt);
		move(dt);
		tweenColors(dt);
	}

	void Particle::setVelcoity(double x, double y) {
		xVel = x;
		yVel = y;
	}
	
	void Particle::resetPosition(double x, double y) {
		xPos = x;
		yPos = y;
	}
	
	void Particle::refresh() {
		lifeTimer = 0;
		currentColor = -1;
	}

	void Particle::move(double dt) {
		xPos += xVel * dt;
		yPos += yVel * dt;
	}

	void Particle::tweenColors(double dt) {	
		//Which color is it currently tweening towards
		int number = static_cast<int>(lifeTimer / interval); 

		if (number < 0) {
			number = 0; 
		}
		else if (number > colorCount - 1) {
			number = colorCount - 1;
		}
		double targetRed;
		double targetGreen;
		double targetBlue;
		double targetAlpha;
		if (number > currentColor) {
			currentColor = number;
			targetRed = targetColors[number]->red;
			targetGreen = targetColors[number]->green;
			targetBlue = targetColors[number]->blue;
			targetAlpha = targetColors[number]->alpha;

			red_speed = (targetRed - red) / interval;
			green_speed = (targetGreen - green) / interval;
			blue_speed = (targetBlue - blue) / interval;
			alpha_speed = (targetAlpha - alpha) / interval;
		}
		
		//number = math.clamp(0, amount - 1, number);

		//Get the target colors
		

		//Get the time remaining until it will get a new color
		//double timeLeft = interval - std::fmod(lifeTimer, interval);

		//Calculate the speed that it needs to tween at, in order to reach the target in time.
		
		red += red_speed * dt;
		green += green_speed * dt;
		blue += blue_speed * dt;
		alpha += alpha_speed * dt;

		//Clamp the colors to stay within the 0-255 range.
		
		
		if (red < 0){ 
			red = 0;
		} else if (red > 255){ red = 255;}

		if (green < 0) { 
			green = 0;
		}else if (green > 255) {green = 255;}

		if (blue < 0) {
			blue = 0;
		} else if (blue > 255) {
			blue = 255;
		}

		if (alpha < 0) { 
			alpha = 0; 
		} else if (alpha > 255) {
			alpha = 255;
		}

		
		
		/*
			red = math.clamp(0, 255, red);
			green = math.clamp(0, 255, green);
			blue = math.clamp(0, 255, blue);
			alpha = math.clamp(0, 255, alpha);
		*/
		
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
	
	void Particle::setTargetColor(std::vector<std::shared_ptr<Color>>& target, int size) {
		targetColors.clear();
		for (int i = 0; i < size; i++)
		{
			targetColors.push_back(target[i]);
		}
		colorCount = size;
		interval = duration / colorCount;
	}

	void Particle::draw(Image* asset) {
		asset->draw(xPos, yPos, red, green, blue, alpha);
	}
}