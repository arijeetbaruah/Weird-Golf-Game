#include "Timed.h"
#include <iostream>

void Timed::Update(float dt) {
	timeActive += dt;
	Targeted::Update(dt);
	std::cout << "Timed" << std::endl;
}

bool Timed::conditionCheck() {
	return timeActive >= maxTime;
}

void Timed::resetTime() {
	timeActive = 0;
}