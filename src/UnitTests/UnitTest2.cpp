#include <iostream>
#include <cassert>


#define ASSERT_WITH_FAILEXIT(COND) do { if (!(COND)) exit(-1); } while(0)
int main() {
	ASSERT_WITH_FAILEXIT(true);
}