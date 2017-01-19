#pragma once

namespace ALLIVaultCore
{
	namespace Engine
	{
		typedef enum NetworkStatus {
			NotReachable = 0,
			ReachableViaWiFi,
			ReachableViaWWAN
		} NetworkStatus;
	}
}
