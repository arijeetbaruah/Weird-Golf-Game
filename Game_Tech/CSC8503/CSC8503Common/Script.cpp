#include "Script.h"
Script::Script() {
	this->lambda = [](GameObject*){};
}

//Lamda expression must take in a GameObject* as a parameter so the script can access parent variables
Script::Script(std::function<void(GameObject*)> script) {
	this->lambda = script;
}

//Lamda expression must take in a GameObject* as a parameter so the script can access parent variables
void Script::setLambda(std::function<void(GameObject*)> func) {
	this->lambda = func;
}

//Set function to do nothing
void Script::nullLambda() {
	lambda = [](GameObject*) {};
}

//Lamda expression must take in a GameObject* as a parameter so the script can access parent variables
void Script::setLateLambda(std::function<void(GameObject*)> func) {
	lateLambda = [](GameObject*) {};
}

//Set function to do nothing
void Script::nullLateLambda() {
	lateLambda = [](GameObject*) {};
}

//Call the Lambda when the Update method is called
void Script::Update(float dt) {
	this->lambda(this->getParent());
}

//Call the LateLambda when the LateUpdate method is called
void Script::LateUpdate() {
	this->lateLambda(this->getParent());
}