#include "TestBuff.h"
#include "Script.h"
#include <functional>
#include <iostream>
#include "GameObject.h"
#include "ShotTracker.h"

TestBuff::TestBuff() {
	setName("TestBuff");
	maxShots = 5;
}

void TestBuff::Apply() {
	Script* ct = new Script();
	ct->setName("Cout");
	ct->setLambda([](GameObject* go) {
		ShotTracker* st = go->getComponent<ShotTracker*>("ShotTracker");
		if (st != NULL)
			std::cout << "Number of Shots: " << st->getShots() << std::endl; 
	});
	this->getParent()->addComponent(ct);
}

void TestBuff::Remove() {
	this->getParent()->getComponent<Script*>("Cout")->toRemove = true;
}
