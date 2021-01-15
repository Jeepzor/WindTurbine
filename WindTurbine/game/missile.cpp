#include <string>
#include "play_module.h"
#include "missile.h"
#include "rock.h"
#include "boom.h"


Missile::Missile(PlayModule* play_module, double x, double y, double a) {
	xPos = x;
	yPos = y;
	angle = a;

	playModule = play_module;

	xVel = speed * cos(angle);
	yVel = speed * sin(angle);

	//Assets
	asset = wind::Voxel::getInstance("game/assets/missile.png", 11);
	asset->setAngle(angle);
	asset->setScale(1);

	//Dimensions
	asset->getDimensions(width, height);

	//Hitbox
	collider = wind::CircleCollider::getInstance(playModule->getWorld(), xPos, yPos, 10);
	//collider->setOnCollide(collisionCallbackFunction);
	collider->setEntity(this);
	collider->setVelocity(xVel, yVel);
	collider->setFilterGroup(1);

	collider->setOnCollide([=](wind::Collider* A, wind::Collider* B) mutable {
		if (Rock* rock = dynamic_cast<Rock*>(B->getEntity())) {
				playModule->addEntity(Boom::getInstance(this->getX(), this->getY()));
				this->destroy();
				rock->setFalling();
				B->destroy();
				A->destroy();
			}
		}
	);

	//Particles
	thruster = new wind::ParticleEmitter("game/assets/white_particle.png", 0, 50);
	thruster->setDirection(wind::math.pi() / 2);
	thruster->setSpread(wind::math.pi() / 7);
	thruster->setParticleLife(1);
	thruster->setEmission(50);
	thruster->setSpeed(50, 70);
	thruster->setPosition(xPos + width / 2, yPos + height / 2 - 24);
	thruster->setColors(220,220,255,255, 0,0,0,0);
}


void Missile::update(double dt) {
	syncCollider();
	updateThruster(dt);
}

void Missile::syncCollider() {
	xPos = collider->getX() - width / 2;
	yPos = collider->getY() - height / 2;
}

void Missile::updateThruster(double dt) {
	thruster->update(dt);
	thruster->setPosition(xPos + width / 2 - xVel * 0.2, yPos + height / 2 + 5 - yVel * 0.2);
	thruster->setDirection(angle);
}

void Missile::draw() {
	thruster->draw();
	asset->draw(xPos, yPos);
}