#include "NetworkObject.h"

using namespace NCL;
using namespace CSC8503;

NetworkObject::NetworkObject(GameObject& o, int id) : object(o)	{
	deltaErrors = 0;
	fullErrors  = 0;
	networkID   = id;
	playerScore = 0;
	playerTotalScore = 0;
}

NetworkObject::~NetworkObject()	{
}

bool NetworkObject::ReadPacket(GamePacket& p) {
	if (p.type == Delta_State) {
		return ReadDeltaPacket((DeltaPacket&)p);
	}
	if (p.type == Full_State) {
		return ReadFullPacket((FullPacket&)p);
	}
	if (p.type == Received_State) {
		return ReadPlayerPacket((PlayerPacket&)p);
	}
	return false; //this isn't a packet we care about!
}

bool NetworkObject::WritePacket(GamePacket** p, bool deltaFrame, int stateID) {
	if (deltaFrame) {
		if (!WriteDeltaPacket(p, stateID)) {
			return WriteFullPacket(p);
		}
	}
	return WriteFullPacket(p);
}
//Client objects recieve these packets
bool NetworkObject::ReadDeltaPacket(DeltaPacket &p) {
	if (p.fullID != lastFullState.stateID) {
		deltaErrors++; //can't delta this frame
		return false;
	}

	UpdateStateHistory(p.fullID, 1);

	Vector3		fullPos			= lastFullState.position;
	Quaternion  fullOrientation = lastFullState.orientation;

	fullPos.x += p.pos[0];
	fullPos.y += p.pos[1];
	fullPos.z += p.pos[2];

	fullOrientation.x += ((float)p.orientation[0]) / 127.0f;
	fullOrientation.y += ((float)p.orientation[1]) / 127.0f;
	fullOrientation.z += ((float)p.orientation[2]) / 127.0f;
	fullOrientation.w += ((float)p.orientation[3]) / 127.0f;

	object.GetTransform().SetWorldPosition(fullPos);
	object.GetTransform().SetLocalOrientation(fullOrientation);

	return true;
}

bool NetworkObject::ReadPlayerPacket(PlayerPacket& p) {
	for (NetworkState& state : p.fullState) {
		if (state.stateID < lastFullState.stateID) {
			return false; // received an 'old' packet, ignore!
		}
		lastFullState = state;

		object.GetTransform().SetWorldPosition(lastFullState.position);
		object.GetTransform().SetLocalOrientation(lastFullState.orientation);

		stateHistory[lastFullState.playerID].emplace_back(lastFullState);
	}

	return true;
}

bool NetworkObject::WritePlayerPacket(GamePacket** p, int stateID) {
	DeltaPacket* dp = new DeltaPacket();

	dp->objectID = networkID;

	NetworkState state;
	if (!GetNetworkState(stateID, state, 1)) {
		return false; //can't delta!
	}

	dp->fullID = stateID;

	Vector3		currentPos = object.GetTransform().GetWorldPosition();
	Quaternion  currentOrientation = object.GetTransform().GetWorldOrientation();

	currentPos -= state.position;
	currentOrientation -= state.orientation;

	dp->pos[0] = (char)currentPos.x;
	dp->pos[1] = (char)currentPos.y;
	dp->pos[2] = (char)currentPos.z;

	dp->orientation[0] = (char)(currentOrientation.x * 127.0f);
	dp->orientation[1] = (char)(currentOrientation.y * 127.0f);
	dp->orientation[2] = (char)(currentOrientation.z * 127.0f);
	dp->orientation[3] = (char)(currentOrientation.w * 127.0f);

	*p = dp;
	return true;
}

bool NetworkObject::ReadFullPacket(FullPacket &p) {
	return true;
}

bool NetworkObject::WriteDeltaPacket(GamePacket**p, int stateID) {
	DeltaPacket* dp = new DeltaPacket();

	dp->objectID = networkID;

	NetworkState state;
	if (!GetNetworkState(stateID, state, 1)) {
		return false; //can't delta!
	}

	dp->fullID = stateID;

	Vector3		currentPos			= object.GetTransform().GetWorldPosition();
	Quaternion  currentOrientation  = object.GetTransform().GetWorldOrientation();

	currentPos			-= state.position;
	currentOrientation  -= state.orientation;

	dp->pos[0] = (char)currentPos.x;
	dp->pos[1] = (char)currentPos.y;
	dp->pos[2] = (char)currentPos.z;

	dp->orientation[0] = (char)(currentOrientation.x * 127.0f);
	dp->orientation[1] = (char)(currentOrientation.y * 127.0f);
	dp->orientation[2] = (char)(currentOrientation.z * 127.0f);
	dp->orientation[3] = (char)(currentOrientation.w * 127.0f);

	*p = dp;
	return true;
}

bool NetworkObject::WriteFullPacket(GamePacket**p) {
	return true;
}

NetworkState& NetworkObject::GetLatestNetworkState() {
	return lastFullState;
}

bool NetworkObject::GetNetworkState(int stateID, NetworkState& state, int playerID) {
	for (auto i = stateHistory[playerID].begin(); i < stateHistory[playerID].end(); ++i) {
		if ((*i).stateID == stateID) {
			state = (*i);
			return true;
		}
	}
	return false;
}

void NetworkObject::UpdateStateHistory(int minID, int playerID) {
	for (auto i = stateHistory[playerID].begin(); i < stateHistory[playerID].end(); ) {
		if ((*i).stateID < minID) {
			i = stateHistory[playerID].erase(i);
		}
		else {
			++i;
		}
	}
}