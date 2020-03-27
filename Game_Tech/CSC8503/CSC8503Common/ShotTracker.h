#pragma once
#include "Component.h"
#include <iostream>
class ShotTracker : public Component {
	public:
		ShotTracker() {
			setName("ShotTracker");
		}
		void Update(float dt) {}
		void addShots() { shots++; }
		void addShots(int num) { shots += num; }
		void setShots(int num) { shots = num; }
		int getShots() { return shots; };
	protected:
		int shots = 0;
};