
#include "play_module.h"
#include "player.h"

double timer = 0;
double rate = 0.3;
PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","paused" };
	eventOn = { "play" };
	initOn = { "play" };
	cleanOn = { "restart" };

	particleEmitter = new wind::ParticleEmitter("../assets/particle.png", 0, 2000);
	particleEmitter->setColors(255,255,255,255, 255,0,0,255, 0,0,255,255, 0,255,0,255, 0,255,255,255, 255,255,0,255, 255,0,255,255, 255,255,255, 0);
	particleEmitter->setEmission(50);
	particleEmitter->setParticleLife(1);
	particleEmitter->setSpread(1);
	particleEmitter->setSpeed(200);

	double our_dt = 0; // Debug, remove later

	//TODO add removal of collider from physicsWorld in their destructor
	worldA = new wind::PhysicsWorld(0, 0);
	bodyA = wind::RectangleCollider::getInstance(worldA, 30, 30, 40, 600);
	bodyB = wind::RectangleCollider::getInstance(worldA, 700, 400, 75, 75);

	//bodyC = new wind::RectangleCollider(worldA, 500, 300, 10, 200);
	bodyD = wind::RectangleCollider::getInstance(worldA, 1100, 330, 25, 75);
	bodyE = wind::CircleCollider::getInstance(worldA, 750, 300, 35);
	wind::PolyPoints rectangle = wind::PolyPoints(0, 0, 200, 50);
	wind::PolyPoints octagon = wind::PolyPoints(-100,-100, 0,50, 50,100, 100,20, -20,80, -40, 180, 60, 50, 120, 120);

	bodyG = wind::PolygonCollider::getInstance(worldA, 600, 30, octagon);
	bodyF = wind::PolygonCollider::getInstance(worldA, 480, 230, octagon);
	bodyF->setRotation(1);

	//bodyA->setVelocity(100, 0);
	//bodyB->setVelocity(-200, 0);
	//bodyC->setVelocity(-200, 0);
	//bodyD->setVelocity(-200, 0); 
	//bodyE->setVelocity(-200, 0);
	//bodyF->setVelocity(0, 0);
	fpsFont = new wind::Font("../assets/bit.ttf", 32);
	bodyG->setVelocity(-50, 50);
	bg = wind::Image::getInstance("../assets/bg.png");
	testPlayer = new Player(worldA);
}

void PlayModule::keyPressed(std::string key) {
	std::cout << "Key [" << key << "] was pressed" << "\n";
	if (key == "1") {
		wind::state.setCurrentState("paused");
	}
	else if (key == "3") {
		bodyG->setVelocity(200, 0);
	}
	else if (key == "4") {
		bodyG->setVelocity(-200, 0);
	}
}

void PlayModule::keyReleased(std::string key) {
	std::cout << "Key [" << key << "] was released" << "\n";
}

void PlayModule::mousePressed(int button) {
	std::cout << "button [" << button << "] was pressed" << "\n";

	std::cout << wind::turbine.getMousePosition().x << " " << wind::turbine.getMousePosition().y << "\n";
	std::cout << wind::turbine.getMouseX() << " " << wind::turbine.getMouseY()<< "\n";
}

void PlayModule::mouseReleased(int button) {
	std::cout << "button [" << button << "] was released" << "\n";
}

void PlayModule::update(double dt) {
	timer += dt;
	if (timer >= rate) {
		timer = 0;
		our_dt = dt;
	}
	particleEmitter->setPosition(testPlayer->getX(), testPlayer->getY());
	particleEmitter->update(dt);
	testPlayer->update(dt);
	worldA->update(dt);

	double angle_test = wind::math.getAngle(testPlayer->getX(), testPlayer->getY(), wind::turbine.getMouseX(), wind::turbine.getMouseY());

	particleEmitter->setDirection(angle_test);
}

void PlayModule::draw() {
	bg->draw();
	testPlayer->draw();
	worldA->draw();
	wind::graphics.setColor(255, 0, 0);
	//wind::graphics.circle("line", 300, 300, 40);
	//wind::graphics.circle("line", 400, 400, 400);
	//std::cout << "State is drawing" << "\n";
	particleEmitter->draw();
	wind::graphics.setColor(255, 0, 0);
	fpsFont->draw("DT            " + std::to_string(our_dt), 30, 30);
}

void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";

}
