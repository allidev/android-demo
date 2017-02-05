#pragma once
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLISSH2_ALT;
		class ALLISSHTunnelP
		{
		public:
			ALLIVaultCore::Engine::ALLISSH2_ALT *ssh2;
			bool exitSignal;
			ALLIVAULTCOREP_API static std::string *connStr;
			ALLIVAULTCOREP_API static std::string *cmdStr_utf8;

			ALLIVAULTCOREP_API explicit ALLISSHTunnelP(NetworkStatus(*chkHost)());
			ALLIVAULTCOREP_API ALLISSHTunnelP(const ALLIVaultCore::Engine::ALLISSHTunnelP &src);
			ALLIVAULTCOREP_API ~ALLISSHTunnelP();

			ALLIVAULTCOREP_API void initializeTunnel();
			ALLIVAULTCOREP_API void setupPortForwardingServer(void *payload);
			ALLIVAULTCOREP_API void closeTunnel();

		private:
			NetworkStatus(*chkHost)();
			static std::string mysqlPassword;
			static std::string setConnStr();

			void setupPortForwardingServerImpl();
		};
	}
}

