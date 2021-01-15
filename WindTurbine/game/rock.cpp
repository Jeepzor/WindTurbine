
#include "rock.h"
#include "player.h"
#include "play_module.h"

Rock::Rock(PlayModule* play_module, double x, double y, double direction) {
	playModule = play_module;
	equationFont = new wind::Font("../assets/bit.ttf", 42);
	xPos = x;
	yPos = y;
	angle = direction;
	xVel = speed * cos(angle);
	yVel = speed * sin(angle);
	rVel = 4 * wind::math.random() - 4; 
	scale = 2 * wind::math.random() + 3;

	//Math component
	digit1 = floor(8 * wind::math.random() + 1 + 0.5);
	digit2 = floor(8 * wind::math.random() + 1 + 0.5);
	
	equation = std::to_string(digit1) + " X " + std::to_string(digit2);
	result = digit1 * digit2;

	//Assets
	asset = wind::Voxel::getInstance("game/assets/testrock.png", 25);
	asset->setScale(scale);
	asset->getDimensions(width, height);

	//The size of 50 fits a scale of 4, then added differing scale.
	double size_multiplier = scale / 4;
	collider = wind::CircleCollider::getInstance(playModule->getWorld(), x + width / 2, y + height / 2, 50 * size_multiplier);
	collider->setEntity(this);
	collider->setVelocity(xVel, yVel);
	collider->setFilterGroup(8);
	collider->setOnCollide([=](wind::Collider* A, wind::Collider* B) mutable {
			if (Player* player = dynamic_cast<Player*>(B->getEntity())) {
				collider->setVelocity(speed * cos(player->getShipAngle() + wind::math.pi()), speed * sin(player->getShipAngle() + wind::math.pi()));
				player->takeDamage();
				//coll_b->setVelocity(test->getVelocityX() * 0.5, test->getVelocityY() * 0.5);
			}
		}
	);
}

void Rock::draw() {
	asset->draw(xPos, yPos);
	
	asset->setAngle(rotation);
	drawText();
}

void Rock::drawText() const {
	wind::graphics.setColor(0, 0, 0);
	equationFont->draw(equation, xPos + 2, yPos + 2);

	wind::graphics.setColor(225, 25, 25);
	equationFont->draw(equation, xPos, yPos);
	wind::graphics.clearColor();
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