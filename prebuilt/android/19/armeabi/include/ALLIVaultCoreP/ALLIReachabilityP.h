/*
* Copyright (C) ALLI Enterprises, Inc. ALL rights reserved.
*
* This file is part of ALLIVault. For full terms see the included
* COPYING file.
*/
#pragma once

#include "alli_common.h"
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	namespace Engine
	{
		/**
		* Class ALLIReachabilityP. It handles network connectability
		* issue.
		*/
		class ALLIReachabilityP
		{
		public:
			ALLIVAULTCOREP_API ALLIReachabilityP(void);
			ALLIVAULTCOREP_API ~ALLIReachabilityP(void);
			ALLIVAULTCOREP_API NetworkStatus currentReachabilityStatus();
			/**
			 * Static member function to check the network status to
			 * the servers
			 *
			 * @return NetworkStatus indicating if the host is reachable
			 */
			static ALLIVAULTCOREP_API NetworkStatus currentReachabilityStatusS();
			ALLIVAULTCOREP_API bool connectionRequired();
		};
	}
}
