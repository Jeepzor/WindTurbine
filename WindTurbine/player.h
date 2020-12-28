#ifndef PLAYER_H
#define PLAYER_H

#include "wind_turbine.h"

class Player : public wind::Entity {
public:
	Player();
	void draw()override;
	
private:
	wind::Image sprite;
};

#endif

