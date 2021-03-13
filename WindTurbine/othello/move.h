#ifndef MOVE_H
#define MOVE_H

struct Move
{
	Move(int xPos, int yPos) { x = xPos, y = yPos; };
	Move(int xPos, int yPos, int val) { x = xPos, y = yPos, value = val; };
	int x;
	int y;
	int value = 0;
};

#endif

