#include <iostream>
#include <cassert>
#include "ComponentSystem/GameObject.h"

#define ASSERT_WITH_FAILEXIT(COND) do {if (!(COND)) exit(-1);} while(0)

int main() {
	GameObject go = GameObject();
	Component* tf = go.getComponent("Transform");
	ASSERT_WITH_FAILEXIT(tf != nullptr);
}