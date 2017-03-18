#pragma once
#include "ALLISharingSyncP.h"

namespace ALLIVaultCore
{
	class ALLISSEncryptedRepoP;
	class ALLISSPlainRepoP :
		public ALLISharingSyncP
	{
	public:
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingPlainRepo;
		boost::filesystem::path *sharingPlainURL;

		ALLIVAULTCOREP_API ALLISSPlainRepoP();
		ALLIVAULTCOREP_API ALLISSPlainRepoP(const ALLIVaultCore::ALLISSPlainRepoP &src);
		ALLIVAULTCOREP_API ~ALLISSPlainRepoP();

		ALLIVAULTCOREP_API void monitorSharingSyncPlainRepo();

	protected:
		virtual void moveRepositoryToURLImpl(const boost::filesystem::path &localURL, bool checkRemoteRef) override;

	private:
		friend class ALLISSEncryptedRepoP;
	};
}

