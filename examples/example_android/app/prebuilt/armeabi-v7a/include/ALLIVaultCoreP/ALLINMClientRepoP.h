#pragma once
#include "ALLINMRepoP.h"

namespace ALLIVaultCore
{
	class ALLINMClientRepoP :
		public ALLINMRepoP
	{
	public:
		boost::filesystem::path *clientURL;

		ALLIVAULTCOREP_API ALLINMClientRepoP();
		ALLIVAULTCOREP_API ~ALLINMClientRepoP();

	private:
		ALLIVaultCore::Engine::SimpleRepositoryP *clientRepoP;

		// keyword virtual is to declare the overriding of base member function
		virtual bool cloneFromRemoteRepoEx(const boost::filesystem::path &localURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)()) override;
		virtual bool moveRepositoryEx(const boost::filesystem::path &localURL, bool checkRemoteRef) override;
	};

}

