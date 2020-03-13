#include "../../Common/Window.h"

#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/State.h"

#include "../CSC8503Common/GameServer.h"
#include "../CSC8503Common/GameClient.h"

#include "../CSC8503Common/NavigationGrid.h"

#include "TutorialGame.h"
#include "NetworkedGame.h"

#include "PhysxController.h"
#include "SpherePhysicsComponent.h"

using namespace NCL;
using namespace CSC8503;
using namespace physx;

#ifdef _ORBIS
	//PS4 code
#else 
	//PC Code
#endif



int main() {
	Window*w = Window::CreateGameWindow("CSC8503 Game technology!", 1280, 720);

	if (!w->HasInitialised()) {
		return -1;
	}	

	size_t wat;

	PhysxController c = PhysxController::getInstance();
	
	w->ShowOSPointer(true);
	w->LockMouseToWindow(false);

	NetworkedGame* g = new NetworkedGame();

	NetworkBase::Initialise();

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE) && g->IfQiutGame() != true) {
		float dt = w->GetTimer()->GetTimeDeltaSeconds();

		if (dt > 1.0f) {
			std::cerr << "Skipping large time delta";
			continue; //must have hit a breakpoint or something to have a 1 second frame time!
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NEXT)) {
			w->ShowConsole(false);
		}
		
		w->SetTitle("Gametech frame time:" + std::to_string(1000.0f * dt));

		//DisplayPathfinding();

		w->SetTitle("Gametech frame time:" + std::to_string(1000.0f * dt));

		g->UpdateGame(dt);
		c.stepPhysics(true, dt);
	}
	Window::DestroyGameWindow();
}