#include <iostream>
#include <cassert>

#include "..//../include/Common/Vector2.h"
using namespace NCL::Maths;

#define ASSERT_WITH_FAILEXIT(COND) do { if (!(COND)) exit(-1); } while(0)

int main() {
	Vector2* vec = new Vector2(3, 4);
	ASSERT_WITH_FAILEXIT((vec->x == 3) && (vec->y == 4));
}