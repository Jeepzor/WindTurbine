
#include "rock.h"
#include "player.h"

Rock::Rock(wind::PhysicsWorld* world, double x, double y, double direction) {
	xPos = x;
	yPos = y;
	angle = direction;

	xVel = speed * cos(angle);
	yVel = speed * sin(angle);
	rVel = 4 * wind::math.random() - 4; 
	scale = 2 * wind::math.random() + 3;
	asset = wind::Voxel::getInstance("game/assets/testrock.png", 25);
	asset->setScale(scale);
	asset->getDimensions(width, height);

	//The size of 50 fits a scale of 4, then added differing scale.
	double size_multiplier = scale / 4;
	collider = wind::CircleCollider::getInstance(world, x + width / 2, y + height / 2, 50 * size_multiplier);
	collider->setEntity(this);
	collider->setVelocity(xVel, yVel);
	collider->setFilterGroup(8);
	collider->setOnCollide([=](wind::Collider* A, wind::Collider* B) mutable {
			if (Player* test = dynamic_cast<Player*>(B->getEntity())) {
			
				//coll_b->setVelocity(test->getVelocityX() * 0.5, test->getVelocityY() * 0.5);
			}
		}
	);
}

void Rock::draw() {
	asset->draw(xPos, yPos);
	
	asset->setAngle(rotation);
}

void Rock::update(double dt) {
	rotation += rVel * dt;
	xPos = collider->getX() - width / 2;
	yPos = collider->getY() - height / 2;
	asset->setScale(scale, true);
	fall(dt);

}

void Rock::fall(double dt) {
	if (falling) {
		scale = scale - 0.5 * dt;
		if (scale < 0) {
			scale = 0;
			destroy();
		}
	}
}

void Rock::syncCollider() {

}