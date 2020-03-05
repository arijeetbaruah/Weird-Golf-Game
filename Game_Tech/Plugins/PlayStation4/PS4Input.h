#pragma once
#ifdef _ORBIS
#include "pad.h"
#include "InputBase.h"
#include <move.h>
#include <user_service.h>

namespace NCL {
	namespace PS4 {
		class PS4Input : public InputBase
		{
		public:
			PS4Input();
			~PS4Input();

			void Poll();

			auto GetPadHandle()
			{
				return padHandle;
			}
		protected:
			void InitController();

			int32_t padHandle;
			int32_t motionHandle;
			ScePadControllerInformation padInfo;
		};
	}
}
#endif
