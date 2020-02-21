// LogTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "./Common/Window.h"

#include "./Logger/Logger.h"

#include "./AI/StateMachine.h"
#include "./AI//StateTransition.h"
#include "./AI//State.h"

#include "PxPhysicsAPI.h"
#include "GolfGame.h"

using namespace physx;

int main()
{
	std::unique_ptr<Logger> log = std::unique_ptr<Logger>(new Logger("main"));
	Window* w = Window::CreateGameWindow("CSC8503 Game technology!", 1280, 720);

	if (!w->HasInitialised()) {
		return -1;
	}

	w->ShowOSPointer(false);
	w->LockMouseToWindow(false);

	std::unique_ptr<GolfGame> g = std::unique_ptr<GolfGame>(new GolfGame());

	if (g->hasError() != 0) {
		log->error(g->hasError());
		return g->hasError();
	}

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
		float dt = w->GetTimer()->GetTimeDeltaSeconds();

		if (dt > 1.0f) {
			log->info("Skipping large time delta");
			continue; //must have hit a breakpoint or something to have a 1 second frame time!
		}

		w->SetTitle("Gametech frame time:" + std::to_string(1000.0f * dt));

		g->UpdateGame(dt);
	}

	Window::DestroyGameWindow();
}
