#include <string>
#include "player.h"

void collisionCallbackFunction(wind::Collider* coll_a, wind::Collider* coll_b) {
	std::cout << "yey" << "\n";
	if (Player* test = dynamic_cast<Player*>(coll_a->getEntity())) {
		//coll_b->setVelocity(test->getVelocityX() * 0.5, test->getVelocityY() * 0.5);
		//coll_b->destroy();
	}
}


Player::Player(wind::PhysicsWorld* world) {

	//Assets
	shipImg = wind::Voxel::getInstance("game/assets/ship.png", 24);
	weaponImg = wind::Voxel::getInstance("game/assets/cannon.png", 9);
	shipImg->setScale(2);
	weaponImg->setScale(2);

	//Dimensions
	shipImg->getDimensions(width, height);
	shipImg->setAngle(wind::math.pi());
	weaponImg->getDimensions(weaponWidth, weaponHeight);
	
	//Position
	xPos = 50;
	yPos = (wind::turbine.getWindowHeight() / 2) - (height / 3);

	//Weapon
	weaponX = xPos + width / 2 - weaponWidth / 2;
	weaponY = yPos + height / 2 - weaponHeight / 2 - 24 + 9;

	//Hitbox
	collider = wind::RectangleCollider::getInstance(world, xPos, yPos, width * 0.75, height);
	collider->setOnCollide(collisionCallbackFunction);
	collider->setEntity(this);
	collider->setFilterGroup(1);


	//Particle effects
	leftThruster = new wind::ParticleEmitter("game/assets/white_particle.png", 0, 750);
	leftThruster->setDirection(wind::math.pi() / 2);
	leftThruster->setSpread(wind::math.pi() / 5);
	leftThruster->setParticleLife(3);
	leftThruster->setEmission(250);
	leftThruster->setSpeed(100,150);
	leftThruster->setPosition(xPos + width / 2, yPos + height / 2 - 24);
	leftThruster->setColors(254,253,189,255, 254,201,78,255, 176,57,0,255, 0,0,0,100, 0, 0, 0, 0);
	
	rightThruster = new wind::ParticleEmitter("game/assets/white_particle.png", 0, 750);
	rightThruster->setDirection(wind::math.pi() / 2);
	rightThruster->setSpread(wind::math.pi() / 5);
	rightThruster->setParticleLife(3);
	rightThruster->setEmission(250);
	rightThruster->setSpeed(100,150);
	rightThruster->setPosition(xPos + width / 2, yPos + height / 2 - 24);
	rightThruster->setColors(254,253,189,255, 254,201,78,255, 176,57,0,255, 0,0,0,100, 0, 0, 0, 0);


}

void Player::takeDamage() {
	health -= 1;
}

void Player::update(double dt) {
	lifeTimer += dt;
	shipAngle = wind::math.pi() + sin(lifeTimer) * 0.6; //Bind the angle to a sine wave
	updateAim();
	updateThrusters();
	leftThruster->update(dt);
	rightThruster->update(dt);
	shipImg->setAngle(shipAngle);
}

void Player::updateThrusters() {
	double tx = (xPos + width / 2) - 75 * std::cos(shipAngle + 4.2 / 2);
	double ty = (yPos + height / 2) - 75 * std::sin(shipAngle + 4.2 / 2);
	leftThruster->setPosition(tx, ty);
	leftThruster->setDirection(shipAngle - wind::math.pi() / 2);
	
	double tx2 = (xPos + width / 2) - 75 * std::cos(shipAngle + 2.3 / 2);
	double ty2 = (yPos + height / 2) - 75 * std::sin(shipAngle + 2.3 / 2);
	rightThruster->setPosition(tx2, ty2);
	rightThruster->setDirection(shipAngle - wind::math.pi() / 2);

}


void Player::updateAim() {
	aimAngle = wind::math.getAngle(weaponX + weaponWidth / 2, weaponY + weaponHeight / 2, wind::turbine.getMouseX(), wind::turbine.getMouseY());
}

double Player::getLaunchX()const {
	double offset = 60;
	return weaponX + weaponWidth / 2 + offset * cos(aimAngle);
}

double Player::getLaunchY()const {
	double offset = 60;
	return weaponY + weaponHeight / 2 + offset * sin(aimAngle);
}

void Player::draw() {
	shipImg->draw(xPos, yPos);
	weaponImg->draw(weaponX, weaponY);
	weaponImg->setAngle(aimAngle - wind::math.pi() / 2);
	leftThruster->draw();
	rightThruster->draw();
	//wind::graphics.circle(weaponX + weaponWidth / 2, weaponY + weaponHeight / 2,10);
}