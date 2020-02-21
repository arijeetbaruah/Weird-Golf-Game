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

	ExampleRenderer renderer(w);
	//
	PS4Input		input		= PS4Input();
	
	Ps4AudioSystem*	audioSystem = new Ps4AudioSystem(8);
	
	GameTimer t;

	while (w->UpdateWindow()) {
		float time = w->GetTimer()->GetTimeDeltaSeconds();

		input.Poll();

		renderer.Update(time);
		renderer.Render();
	
		if (input.GetButton(0)) {
			std::cout << "LOL BUTTON" << std::endl;
		}
		auto axisL = input.GetAxis(0);
		auto currentPos = renderer.mainCamera.GetPosition();
		std::cout << axisL.x << std::endl;
		if (abs(axisL.y) < 0.1f)
		{
			axisL.y = 0;
		}
		if (abs(axisL.x) < 0.1f)
		{
			axisL.x = 0;
		}
		currentPos += renderer.mainCamera.BuildViewMatrix().GetTransposedRotation() *
			NCL::Vector3(0, 0, 1) * axisL.y * 0.2f;
		currentPos += renderer.mainCamera.BuildViewMatrix().GetTransposedRotation() * NCL::Vector3(1, 0, 0) * axisL.x * 0.2f;
		renderer.mainCamera.SetPosition(currentPos);

		auto axisR = input.GetAxis(1);
		if (abs(axisR.y) < 0.1f)
		{
			axisR.y = 0;
		}
		if (abs(axisR.x) < 0.1f)
		{
			axisR.x = 0;
		}
		auto pitch = renderer.mainCamera.GetPitch();
		auto yaw = renderer.mainCamera.GetYaw();
		pitch -= axisR.y;
		yaw -= axisR.x;
		renderer.mainCamera.SetPitch(pitch);
		renderer.mainCamera.SetYaw(yaw);
		//renderer.mainCamera.UpdateCamera
	}

	delete audioSystem;
	
	return 1;
}

