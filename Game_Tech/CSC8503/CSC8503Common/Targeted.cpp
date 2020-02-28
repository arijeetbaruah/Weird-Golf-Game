#include "Targeted.h"

void Targeted::Update(float dt) {
	if (!applied) {
		this->Apply();
		applied = true;
	}
	if (conditionCheck()) {
		this->Remove();
		toRemove = true;
	}
}