#pragma once
#include "ALLINMEncryptedRepoPEx.h"

namespace ALLIVaultCore
{
	class ALLINMPlainRepoP;
	class ALLINMEncryptedRepoP :
		public ALLINMEncryptedRepoPEx
	{
	public:
		ALLIVAULTCOREP_API ALLINMEncryptedRepoP();
		ALLINMEncryptedRepoP(const ALLIVaultCore::ALLINMEncryptedRepoP &src);
		ALLIVAULTCOREP_API ~ALLINMEncryptedRepoP();
		ALLIVAULTCOREP_API ALLIVaultCore::ALLINMPlainRepoP *copyToPainRepo(const boost::filesystem::path &plainURL);

	private:
		virtual bool cloneFromRemoteRepoEx(const boost::filesystem::path &localURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)()) override;
	};

}

