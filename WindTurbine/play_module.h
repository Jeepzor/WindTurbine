#ifndef PLAY_MODULE_H
#define PLAY_MODULE_H

#include "wind.h"

class PlayModule : public wind::GameModule {
public:
	PlayModule();
	void keyPressed(std::string key);
	void keyReleased(std::string key);
	void mousePressed(int button);
	void mouseReleased(int button);
	void update(double dt);
	void draw();
	void clean();
	std::string getName() { return "playing"; };

private:
	wind::Image* bg;
	wind::Entity* testPlayer;
	wind::PhysicsWorld* worldA;
	wind::Collider* bodyA;
	wind::Collider* bodyB;
	wind::Collider* bodyC;
	wind::Collider* bodyD;
	wind::Collider* bodyE;
	wind::Collider* bodyF;
	wind::Collider* bodyG;
	wind::Font* fpsFont;
	wind::ParticleEmitter* particleEmitter;
};

#endif


