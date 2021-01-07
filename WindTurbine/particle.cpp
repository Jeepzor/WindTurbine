#include <string>

#include "particle.h"
#include "wind_turbine.h"
#include "math.h"

namespace wind {
	Particle::Particle(std::string path, double x, double y, double life_time) : Image::Image(path) {
		xPos = x;
		yPos = y;
		lifeTimer = life_time;
		red = 0;
		green = 0;
		blue = 0;
		alpha = 255;

		xVel = 0;
		yVel = 0;
		
		targetRed = 255;
		targetGreen = 255;
		targetBlue = 255;
		targetAlpha = 255;
	}

	void Particle::update(double dt) {
		updateLife(dt);

		if (lifeTimer > 0) {
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
	
	void Particle::setLifeTimer(double time) {
		lifeTimer = time;
	}

	void Particle::move(double dt) {
		xPos += xVel * dt;
		yPos += yVel * dt;
	}

	void Particle::updatePosition() {
		setPosition(xPos, yPos);
	}

	void Particle::tweenColors(double dt) {
		double red_speed = (targetRed - red) / lifeTimer;
		red += red_speed * dt;
		
		double green_speed = (targetGreen - green) / lifeTimer;
		green += green_speed * dt;
		
		double blue_speed = (targetBlue - blue) / lifeTimer;
		blue += blue_speed * dt;
		
		double alpha_speed = (targetAlpha - alpha) / lifeTimer;
		alpha += alpha_speed * dt;

		red = math.clamp(0, 255, red);
		green = math.clamp(0, 255, green);
		blue = math.clamp(0, 255, blue);
		alpha = math.clamp(0, 255, alpha);
	}
	
	void Particle::updateLife(double dt) {
		lifeTimer -= dt;
	}

	void Particle::setColor(double r, double g, double b, double a) {
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}
	
	void Particle::setTargetColor(double r, double g, double b, double a) {
		targetRed = r;
		targetGreen = g;
		targetBlue = b;
		targetAlpha = a;
	}

	void Particle::draw() {
		SDL_SetTextureAlphaMod(asset, alpha);
		SDL_SetTextureColorMod(asset, red, green, blue);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), angle, getOriginPoint(), flip);
	}


}

//: wind::Collider::Collider(physics_world, x, y, 0)