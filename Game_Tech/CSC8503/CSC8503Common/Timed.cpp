#include "Timed.h"
#include <iostream>
#include "GameObject.h"

void Timed::Update(float dt) {
	timeActive += dt;
	Targeted::Update(dt);
}

bool Timed::conditionCheck() {
	return timeActive >= maxTime;
}

void Timed::resetTime() {
	timeActive = 0;
}