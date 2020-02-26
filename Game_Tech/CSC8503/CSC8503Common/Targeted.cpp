#include "Targeted.h"

void Targeted::Update(float dt) {
	if (!applied)
		this->Apply();
	if (conditionCheck())
		this->remove();
}