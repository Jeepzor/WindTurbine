
#ifndef OTHELLO_MODULE_H
#define OTHELLO_MODULE_H


#include "../wind.h"
#include "board.h"

class OthelloModule : public wind::GameModule {
public:
	static OthelloModule* getInstance() {
		return new OthelloModule();
	}
	void mousePressed(int button) override;
	void keyPressed(std::string key) override;
	void update(double dt) override;
	void draw() override;
	void clean() override;
	std::string getName() override { return "OthelloModule"; }

private:
	OthelloModule();
	OthelloModule(const OthelloModule& other) = delete;
	const OthelloModule& operator=(const OthelloModule& other) = delete;

	wind::Image* pauseImg;
	Board* board;
	bool lock = true;
};

#endif


