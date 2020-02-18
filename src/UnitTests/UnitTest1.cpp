#include <iostream>
#include <cassert>

#include "../../include/Common/Vector2.h"

int main() {
	Vector2 vec = new Vector2(3, 4);
	assert((vec.x == 3) && (vec.y == 4));
}