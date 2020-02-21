#include <iostream>
#include <cassert>
#include "ComponentSystem/GameObject.h"
#include "ComponentSystem/Transform.h"

#define ASSERT_WITH_FAILEXIT(COND) do {if (!(COND)) exit(-1);} while(0)

int main() {
	GameObject go = GameObject();
	Transform* tf = go.getComponent<Transform*>("Transform");
	ASSERT_WITH_FAILEXIT(tf != nullptr && tf->getName() == "Transform");
}