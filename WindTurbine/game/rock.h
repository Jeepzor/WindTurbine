#ifndef ROCK_H
#define ROCK_H


#include "../wind.h"

class PlayModule;
class Rock : public wind::Entity {

public:
	static int counter;

	static Rock* getInstance(PlayModule* play_module, double x, double y, double angle) {
		return new Rock(play_module, x, y, angle);
	}
	~Rock()override;
	void draw()override;
	void update(double dt)override;
	void setFalling() { falling = true; };
	int getResult() { return result; };
private:
	Rock(PlayModule* play_module, double x, double y, double angle);
	Rock(const Rock& other) = delete;
	const Rock& operator=(const Rock& other) = delete;
	void drawText() const;
	void fall(double dt);
	void checkOutOfBounds();

	bool falling = false;

	double scale;
	double width = 0;
	double height = 0;
	double angle = 0;
	double speed = 100;
	double xVel = 0;
	double yVel = 0;
	double rVel = 0;
	double rotation = 0;
	int id;
	int digit1;
	int digit2;
	int result;

	std::string equation;
	wind::Font* equationFont;
	PlayModule* playModule;
	wind::Collider* collider;
	wind::Voxel* asset;
};

#endif

