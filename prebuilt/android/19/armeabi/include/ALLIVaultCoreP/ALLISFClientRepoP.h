#pragma once
#include "ALLISharingFromP.h"

namespace ALLIVaultCore
{
	class ALLISFClientRepoP :
		public ALLISharingFromP
	{
	public:
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingClientRepo;

		ALLIVAULTCOREP_API ALLISFClientRepoP();
		ALLISFClientRepoP(const ALLIVaultCore::ALLISFClientRepoP &src);
		ALLIVAULTCOREP_API ~ALLISFClientRepoP();

		bool cloneFromRemoteClientRepoToURL(const boost::filesystem::path &localURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLIVAULTCOREP_API boost::filesystem::path extractSharingWorkDir();
		void monitorSharingFromClientRepo();

	private:
		std::string buildRepoString();
	};
}

