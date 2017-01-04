#pragma once

#include "alli_common.h"
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIReachabilityP
		{
		public:
			ALLIVAULTCOREP_API ALLIReachabilityP(void);
			ALLIVAULTCOREP_API ~ALLIReachabilityP(void);
			ALLIVAULTCOREP_API NetworkStatus currentReachabilityStatus();
			static ALLIVAULTCOREP_API NetworkStatus currentReachabilityStatusS();
			ALLIVAULTCOREP_API bool connectionRequired();
		};
	}
}
