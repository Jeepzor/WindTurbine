#include <string>
#include <iostream>

#include "module.h"

namespace wind {
	Module::Module() {
		updateOn;
		drawOn;
		eventOn;
	}

	void Module::handleEvents() {

	}

	void Module::update(double dt) {

	}

	void Module::draw() {

	}

	void Module::clean() {

	}

	bool Module::inUpdateList(std::string state) {
		return(exist(updateOn, state));
	}
	
	bool Module::inDrawList(std::string state) {
		return(exist(updateOn, state));
	}
	
	bool Module::inEventList(std::string state) {
		return(exist(updateOn, state));
	}

	//Returns true if the module is subscribed to that state.
	bool Module::exist(std::vector<std::string> list, std::string state) {
		if (std::find(list.begin(), list.end(), state) != list.end())
		{
			return true;
		}
		else {
			return false;
		}
	}
}