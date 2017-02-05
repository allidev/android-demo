#pragma once
#include "ALLISharingSyncP_external.h"

namespace ALLIVaultCore
{
	class ALLISSClientRepoP :
		public ALLISharingSyncP_external
	{
	public:
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingClientRepo;

		ALLIVAULTCOREP_API ALLISSClientRepoP();
		ALLIVAULTCOREP_API ALLISSClientRepoP(const ALLIVaultCore::ALLISSClientRepoP &src);
		ALLIVAULTCOREP_API ~ALLISSClientRepoP();

		bool cloneFromRemoteClientRepoToURL(const boost::filesystem::path &localURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLIVAULTCOREP_API boost::filesystem::path extractSharingWorkDir();
		void monitorSharingSyncClientRepo();

	private:
		std::string buildRepoString();
	};
}

