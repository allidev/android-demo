#pragma once
#include "ALLISharingFromP.h"

namespace ALLIVaultCore
{
	class ALLISFEncryptedRepoP;
	class ALLISFPlainRepoP :
		public ALLISharingFromP
	{
	public:
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingPlainRepo;
		boost::filesystem::path *sharingPlainURL;

		ALLIVAULTCOREP_API ALLISFPlainRepoP();
		ALLIVAULTCOREP_API ALLISFPlainRepoP(const ALLIVaultCore::ALLISFPlainRepoP &src);
		ALLIVAULTCOREP_API ~ALLISFPlainRepoP();

		ALLIVAULTCOREP_API void monitorSharingFromPlainRepo(const std::string &hostUserName);

	protected:
		virtual void moveRepositoryToURLImpl(const boost::filesystem::path &localURL, bool checkRemoteRef) override;

	private:
		friend class ALLISFEncryptedRepoP;
	};
}

