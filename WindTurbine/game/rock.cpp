
#include "rock.h"
#include "player.h"
#include "play_module.h"
int Rock::counter = 1;

Rock::Rock(PlayModule* play_module, double x, double y, double direction) {
	counter++;
	playModule = play_module;
	equationFont = new wind::Font("game/assets/bit.ttf", 42);
	xPos = x;
	yPos = y;
	angle = direction;
	xVel = speed * cos(angle);
	yVel = speed * sin(angle);
	rVel = 4 * wind::math.random() - 4; 
	scale = 2 * wind::math.random() + 3;

	//Math component
	digit1 = counter;
	digit2 = static_cast<int>(8 * wind::math.random() + 1 + 0.5);
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

	//Collision Callback Function
	collider->setOnCollide([=](wind::Collider* A, wind::Collider* B) mutable {
			if (Player* player = dynamic_cast<Player*>(B->getEntity())) {
				collider->setVelocity(speed * cos(player->getShipAngle() + wind::math.pi()), speed * sin(player->getShipAngle() + wind::math.pi()));
				player->takeDamage();
			}
		}
	);
}

Rock::~Rock() {
	if (!falling) { // Falling rocks already have had their bodies destroyed.
		collider->destroy();
	}
	delete equationFont;
	delete asset;
}

void Rock::draw() {
	asset->draw(xPos, yPos);
	asset->setAngle(rotation);
	drawText();
}

void Rock::drawText() const {
	if (!falling) {
		wind::graphics.setColor(0, 0, 0);
		equationFont->draw(equation, xPos + 2, yPos + 2);
		wind::graphics.setColor(225, 25, 25);
		equationFont->draw(equation, xPos, yPos);
		wind::graphics.clearColor();
	}
}

void Rock::update(double dt) {
	fall(dt);
	rotation += rVel * dt;
	asset->setScale(scale, true);
	if (!falling) {
		xPos = collider->getX() - width / 2;
		yPos = collider->getY() - height / 2.5;
		checkOutOfBounds();
	}
}

void Rock::checkOutOfBounds() {
	if (xPos > wind::turbine.getWindowWidth() + 300 ||
		xPos < -300 ||
		yPos < -300 ||
		yPos > wind::turbine.getWindowHeight() + 300) {
			destroy();
	}
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