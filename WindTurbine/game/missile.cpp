#include <string>
#include "missile.h"
#include "rock.h"

//void collisionCallbackFunction(wind::Collider* coll_a, wind::Collider* coll_b) {
	//std::cout << "yey" << "\n";
	//if (Player* test = dynamic_cast<Player*>(coll_a->getEntity())) {
		//coll_b->setVelocity(test->getVelocityX() * 0.5, test->getVelocityY() * 0.5);
		//coll_b->destroy();
	//}
//}


Missile::Missile(wind::PhysicsWorld* world, double x, double y, double a) {
	xPos = x;
	yPos = y;
	angle = a;

	xVel = speed * cos(angle);
	yVel = speed * sin(angle);

	//Assets
	asset = wind::Voxel::getInstance("game/assets/missile.png", 11);
	asset->setAngle(angle);
	asset->setScale(1);

	//Dimensions
	asset->getDimensions(width, height);

	//Hitbox
	collider = wind::CircleCollider::getInstance(world, xPos, yPos, 10);
	//collider->setOnCollide(collisionCallbackFunction);
	collider->setEntity(this);
	collider->setVelocity(xVel, yVel);
	collider->setFilterGroup(1);

	collider->setOnCollide([=](wind::Collider* A, wind::Collider* B) mutable {
		if (Rock* rock = dynamic_cast<Rock*>(B->getEntity())) {
			this->destroy();
			rock->destroy();
			B->destroy();
			A->destroy();
			//coll_b->setVelocity(test->getVelocityX() * 0.5, test->getVelocityY() * 0.5);
			//coll_b->destroy();
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