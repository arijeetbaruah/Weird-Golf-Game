#pragma once
#include "GameObject.h"
#include "NetworkBase.h"
#include "NetworkState.h"
namespace NCL {
	namespace CSC8503 {

		struct PlayerPacket : public GamePacket {
			int		objectID = -1;
			NetworkState fullState[4];
			bool switchingLevel;

			PlayerPacket() {
				type = Received_State;
				size = sizeof(PlayerPacket) - sizeof(GamePacket);
			}
		};

		struct StarRemovedPacket : public GamePacket {
			int		objectID = -1;
			Vector3		position;
			Quaternion	orientation;
			bool toRemove;

			StarRemovedPacket() {
				type = Star_Removed;
				size = sizeof(StarRemovedPacket) - sizeof(GamePacket);
			}
		};

		struct SendPacket : public GamePacket {
			int playerID;
			NetworkState fullState;

			SendPacket(int p) {
				type = BasicNetworkMessages::Send_Packet;
				playerID = p;
				size = sizeof(SendPacket) - sizeof(GamePacket);
			}
		};

		struct FullPacket : public GamePacket {
			int		playerID = -1;
			Vector3 force = Vector3(0, 0, 0);
			NetworkPowerUps power;

			FullPacket() {
				type = Full_State;
				size = sizeof(FullPacket) - sizeof(GamePacket);
			}
		};

		struct DeltaPacket : public GamePacket {
			int		fullID		= -1;
			int		objectID	= -1;
			char	pos[3];
			char	orientation[4];

			DeltaPacket() {
				type = Delta_State;
				size = sizeof(DeltaPacket) - sizeof(GamePacket);
			}
		};

		struct ClientPacket : public GamePacket {
			int		objectID = -1;
			bool buttonstates[6];
			Quaternion	orientation;

			ClientPacket() {
				type = Received_State;
				size = sizeof(ClientPacket) - sizeof(GamePacket);
				
			}
		};

		struct CollectableCountPacket : public GamePacket {
			int count;

			CollectableCountPacket() {
				type = Collectable_Count;
				size = sizeof(CollectableCountPacket) - sizeof(GamePacket);

			}
		};

		class NetworkObject		{
		public:
			NetworkObject(GameObject& o, int id);
			virtual ~NetworkObject();

			//Called by clients
			virtual bool ReadPacket(GamePacket& p);
			//Called by servers
			virtual bool WritePacket(GamePacket** p, bool deltaFrame, int stateID);

			void UpdateStateHistory(int minID, int playerID);

			int GetID() { return networkID; };

			void increaseScore(int s) { 
				playerScore += s; 
				playerTotalScore += s;
			};

			void resetScore() { playerScore = 0; };

		protected:

			NetworkState& GetLatestNetworkState();

			bool GetNetworkState(int frameID, NetworkState& state, int playerID);

			virtual bool ReadDeltaPacket(DeltaPacket &p);
			virtual bool ReadFullPacket(FullPacket& p);
			virtual bool ReadPlayerPacket(PlayerPacket &p);

			virtual bool WriteDeltaPacket(GamePacket**p, int stateID);
			virtual bool WriteFullPacket(GamePacket**p);
			virtual bool WritePlayerPacket(GamePacket** p, int stateID);

			GameObject& object;

			NetworkState lastFullState;

			std::map<int, std::vector<NetworkState>> stateHistory;

			int deltaErrors;
			int fullErrors;

			int networkID;

			int playerScore;
			int playerTotalScore;
		};
	}
}

