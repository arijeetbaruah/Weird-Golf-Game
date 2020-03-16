#include "offForward.h"

offForward::offForward() {
	setName("offForward");
	maxShots = 3;
}

void offForward::Apply() {
#ifdef WIN32
	dynamic_cast<Player*>(this->getParent())->setIsOffset(true);
#else 
	Player* temp= (Player*)(this->getParent());
	temp->setIsOffset(true);
#endif

}

void offForward::Remove() {
#ifdef WIN32
	dynamic_cast<Player*>(this->getParent())->setIsOffset(true);
#else 
	Player* temp = (Player*)(this->getParent());
	temp->setIsOffset(false);
#endif

}
