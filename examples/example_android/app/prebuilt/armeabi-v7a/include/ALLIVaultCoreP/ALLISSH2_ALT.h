#pragma once

#include "alli_common.h"
#include "ALLINetworkStatus.h"

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class auto_reset_event;
		class manual_reset_event;
	}
	namespace Engine
	{
		class ALLIPublicKey_ALT;
		class ALLISSH2_ALT
		{
		public:
			// use an autoresetevent to sync tunnel construction
			// at any point in time, only one tunneling can exist
			ALLIVAULTCOREP_API static ALLIVaultCore::Helpers::auto_reset_event *tunnel_are;

			ALLIVAULTCOREP_API ALLISSH2_ALT(std::string host, const ALLIVaultCore::Engine::ALLIPublicKey_ALT &publicKey);
			ALLIVAULTCOREP_API ALLISSH2_ALT(std::string host, const ALLIVaultCore::Engine::ALLIPublicKey_ALT &publicKey, NetworkStatus (*chkHost)());
			ALLIVAULTCOREP_API ALLISSH2_ALT(std::string host, const ALLIVaultCore::Engine::ALLIPublicKey_ALT &publicKey, bool nonblock);
			ALLIVAULTCOREP_API ~ALLISSH2_ALT();
			ALLIVAULTCOREP_API bool alli_connect();
			ALLIVAULTCOREP_API bool port_forwarding(bool *exitSignal);
			ALLIVAULTCOREP_API bool execute(std::string command);
			ALLIVAULTCOREP_API bool uploadFile(const boost::filesystem::path &filePath, const boost::filesystem::path &serverPath);
			ALLIVAULTCOREP_API bool downloadFile(const boost::filesystem::path &filePath, const boost::filesystem::path &localPath);
			ALLIVAULTCOREP_API void alli_shutdown();
			ALLIVAULTCOREP_API void port_forwarding_mre_set();
			ALLIVAULTCOREP_API void select_mre_set();
			ALLIVAULTCOREP_API static void tunnel_are_set();

		private:
			class ALLISSH2_ALT_impl;
			std::unique_ptr<ALLISSH2_ALT_impl> pimpl;

		public:
			ALLIVaultCore::Helpers::manual_reset_event *pf_mre;
			ALLIVaultCore::Helpers::manual_reset_event *sel_mre;
			// port forwarding end auto reset event object
			ALLIVaultCore::Helpers::auto_reset_event *pf_end_are;
			bool &pf_mre_set, &sel_mre_set;
		};
	}
}
