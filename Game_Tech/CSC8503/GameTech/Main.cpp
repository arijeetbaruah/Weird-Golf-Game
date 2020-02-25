#include "../../Common/Window.h"

#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/State.h"

#include "../CSC8503Common/GameServer.h"
#include "../CSC8503Common/GameClient.h"

#include "../CSC8503Common/NavigationGrid.h"

#include "../../Plugins/Logger/Logger.h"

#include "TutorialGame.h"
#include "NetworkedGame.h"

#include "PhysxController.h"

using namespace NCL;
using namespace CSC8503;
using namespace physx;

class TestPacketReceiver : public PacketReceiver {
public:
	TestPacketReceiver(string name) {
		this -> name = name;
	}

	void ReceivePacket(int type, GamePacket * payload, int source) {
		if (type == String_Message) {
			StringPacket * realPacket = (StringPacket*)payload;

			string msg = realPacket -> GetStringFromData();

			std::cout << name << " received message : " << msg << std::endl;
		}
	}
protected:
	string name;
};

void TestNetworking() {
	NetworkBase::Initialise();
	
	TestPacketReceiver serverReceiver("Server");
	TestPacketReceiver clientReceiver("Client");
	TestPacketReceiver clientReceiver2("Client2");
	
	int port = NetworkBase::GetDefaultPort();
	
	GameServer* server = new GameServer(port, 2);
	GameClient* client = new GameClient();
	GameClient* client2 = new GameClient();
	
	server -> RegisterPacketHandler(String_Message, &serverReceiver);
	client -> RegisterPacketHandler(String_Message, &clientReceiver);
	client2 -> RegisterPacketHandler(String_Message, &clientReceiver2);
	
	bool canConnect = client -> Connect(127, 0, 0, 1, port);
	bool canConnect2 = client2->Connect(127, 0, 0, 1, port);
	
	for (int i = 0; i < 100; ++i) {
		server -> SendGlobalPacket(
			StringPacket(" Server says hello ! " + std::to_string(i)));
		
		client -> SendPacket(
			StringPacket(" Client says hello ! " + std::to_string(i)));

		client2 -> SendPacket(
			StringPacket(" Client2 says hello ! " + std::to_string(i)));
		
		server -> UpdateServer();
		client -> UpdateClient();
		client2 -> UpdateClient();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
	}

	NetworkBase::Destroy();
}

vector<Vector3> testNodes;

void TestPathfinding() {
	NavigationGrid grid("TestGrid3.txt");
	
	NavigationPath outPath;
	
	Vector3 startPos(20, 0, 20);
	Vector3 endPos(250, 0, 280);

	/*Vector3 startPos(80, 0, 10);
	Vector3 endPos(80, 0, 80);*/
	
	bool found = grid.FindPath(startPos, endPos, outPath);
	
	Vector3 pos;
	while (outPath.PopWaypoint(pos)) {
		testNodes.push_back(pos);
		int i = 0;
	}
}

void DisplayPathfinding() {
	Vector3 offSet(5, 10, 5);
	//Vector3 offSet(0, 40, 0);
	for (int i = 1; i < testNodes.size(); ++i) {
		Vector3 a = testNodes[i - 1];

		a += offSet;

		Vector3 b = testNodes[i];

		b += offSet;
		
		Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
	}
}

/*

The main function should look pretty familar to you!
We make a window, and then go into a while loop that repeatedly
runs our 'game' until we press escape. Instead of making a 'renderer'
and updating it, we instead make a whole game, and repeatedly update that,
instead. 

This time, we've added some extra functionality to the window class - we can
hide or show the 

*/
int main() {
	Window*w = Window::CreateGameWindow("CSC8503 Game technology!", 1280, 720);
	Logger log("main");

	if (!w->HasInitialised()) {
		return -1;
	}	

	PhysxController c = PhysxController::getInstance();
	
	w->ShowOSPointer(false);
	w->LockMouseToWindow(true);

	NetworkedGame* g = new NetworkedGame();

	NetworkBase::Initialise();

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
		float dt = w->GetTimer()->GetTimeDeltaSeconds();

		if (dt > 1.0f) {
			log.info("Skipping large time delta");
			continue; //must have hit a breakpoint or something to have a 1 second frame time!
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NEXT)) {
			w->ShowConsole(false);
		}
		
		w->SetTitle("Gametech frame time:" + std::to_string(1000.0f * dt));

		DisplayPathfinding();

		w->SetTitle("Gametech frame time:" + std::to_string(1000.0f * dt));

		g->UpdateGame(dt);
		c.stepPhysics(true, dt);

	}
	Window::DestroyGameWindow();
}