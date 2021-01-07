#include <string>

#include "particle.h"
#include "wind_turbine.h"
#include "math.h"

namespace wind {
	Particle::Particle(std::string path, double x, double y, double life_time) : Image::Image(path) {
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
	}

	void Particle::update(double dt) {
		updateLife(dt);

		if (lifeTimer < duration) {
			move(dt);
			updatePosition();
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

	void Particle::updatePosition() {
		setPosition(xPos, yPos);
	}

	void Particle::tweenColors(double dt) {
		double amount = targetColors.size();
		double interval = duration / amount;
		
		int number = (lifeTimer / interval);
		double targetRed = targetColors[number]->red;
		double targetGreen = targetColors[number]->green;
		double targetBlue = targetColors[number]->blue;
		double targetAlpha = targetColors[number]->alpha;
		double timeLeft = std::fmod(interval,lifeTimer);

		//std::cout << targetRed << " " << targetGreen << " " << targetBlue << " " << targetAlpha << "\n";
		double red_speed = (targetRed - red) / timeLeft;
		red += red_speed * dt;
		
		double green_speed = (targetGreen - green) / timeLeft;
		green += green_speed * dt;
		
		double blue_speed = (targetBlue - blue) / timeLeft;
		blue += blue_speed * dt;
		
		double alpha_speed = (targetAlpha - alpha) / timeLeft;
		alpha += alpha_speed * dt;

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
		targetColors = target;
	}

	void Particle::draw() {
		SDL_SetTextureAlphaMod(asset, alpha);
		SDL_SetTextureColorMod(asset, red, green, blue);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), angle, getOriginPoint(), flip);
	}


}

//: wind::Collider::Collider(physics_world, x, y, 0)