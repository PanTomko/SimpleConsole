#include "Keyboard.h"

using namespace sc;

Keyboard::Keyboard(){}

Keyboard * sc::Keyboard::getInstance() {
	static Keyboard instance;
	return &instance;
}

Keyboard::~Keyboard(){}
