#include "SingleTest.h"
#include <iostream>


SingleTest::SingleTest(){}
SingleTest::~SingleTest() {}

void SingleTest::printD() {
	std::cout << "Dll" << std::endl;
}

SingleTest * SingleTest::getInstance() {
	static SingleTest instance;
	return &instance;
}