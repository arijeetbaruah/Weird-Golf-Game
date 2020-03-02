#include "offForward.h"

offForward::offForward() {
	setName("offForward");
	maxShots = 3;
}

void offForward::Apply() {
	dynamic_cast<Player*>(this->getParent())->setIsOffset(true);
}

void offForward::Remove() {
	dynamic_cast<Player*>(this->getParent())->setIsOffset(false);
}

void offForward::Start() {

}
