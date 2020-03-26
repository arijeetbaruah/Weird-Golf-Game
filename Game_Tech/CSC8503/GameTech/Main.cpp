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



#ifdef WIN32
	//PC Code
#else 
	//PS4 code
#endif

#ifdef _ORBIS
	//PS4 code
#else 
	//PC Code
#endif

int main(int argc, char* argv[]) 
{
	Window*w = Window::CreateGameWindow("CSC8503 Game technology!", WIDTH, HEIGHT);

	if (!w->HasInitialised()) {
		return -1;
	}	

	size_t wat;

	
	
	w->ShowOSPointer(true);
	w->LockMouseToWindow(false);

	NetworkedGame* g = new NetworkedGame();

	PhysxController c = PhysxController::getInstance();

	NetworkBase::Initialise();
	while (w->UpdateWindow() && g->IfQuitGame() != true) {
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
		

		//DisplayPathfinding();
		w->SetTitle("Gametech frame Rate: " + std::to_string(1/dt));

		g->UpdateGame(dt);
		if (!g->isPaused() || !g->isSolo())
			c.stepPhysics(true, dt);
	}

	g->EndSession();
	Window::DestroyGameWindow();
}