
#include "rock.h"
#include "player.h"

Rock::Rock(wind::PhysicsWorld* world, double x, double y, double direction) {
	xPos = x;
	yPos = y;
	angle = direction;

	asset = wind::Voxel::getInstance("game/assets/testrock.png", 25);
	asset->setScale(4);
	asset->getDimensions(width, height);

	collider = wind::CircleCollider::getInstance(world, x + width / 2, y + height / 2, 50);
	collider->setEntity(this);
	collider->setOnCollide([=](wind::Collider* A, wind::Collider* B) mutable {
			if (Player* test = dynamic_cast<Player*>(B->getEntity())) {
			
				//coll_b->setVelocity(test->getVelocityX() * 0.5, test->getVelocityY() * 0.5);
			}
		}
	);
}

double rotR = 0;
void Rock::draw() {
	asset->draw(xPos, yPos);
	asset->setAngle(rotR);
}

void Rock::update(double dt) {
	rotR += dt;
}

void Rock::syncCollider() {

}