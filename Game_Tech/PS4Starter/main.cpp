#include <stdlib.h>
unsigned int sceLibcHeapExtendedAlloc = 1;			/* Switch to dynamic allocation */
size_t       sceLibcHeapSize = 256 * 1024 * 1024;	/* Set up heap area upper limit as 256 MiB */

#include "../Plugins/PlayStation4/PS4Window.h"
#include "../Plugins/PlayStation4/Ps4AudioSystem.h"
#include "../Plugins/PlayStation4/PS4Input.h"

#include <iostream>

#include "ExampleRenderer.h"

using namespace NCL;
using namespace NCL::PS4;

int main(void) {
	//512MB of each -> You'll probably want more of this as you start making your game!
	PS4MemoryAware::InitialiseMemory(512 << 20, 512 * 1024 * 1024); //2 ways of getting the same num!
	PS4Window*w = (PS4Window*)Window::CreateGameWindow("PS4 Example Code", 1920, 1080);
	// auto* w = new PS4::PS4Window("PS4 Example Code", sizeX, sizeY, fullScreen, offsetX, offsetY);

	// PS4Input		input		= PS4Input();

	ExampleRenderer renderer(w, new PS4Input());
	
	Ps4AudioSystem*	audioSystem = new Ps4AudioSystem(8);
	
	GameTimer t;

	while (w->UpdateWindow()) {
		float time = w->GetTimer()->GetTimeDeltaSeconds();

		renderer.Update(time);
		renderer.Render();
		//renderer.mainCamera.UpdateCamera
	}

	delete audioSystem;
	
	return 1;
}

