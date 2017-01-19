#pragma once
#include "ALLINMEncryptedRepoPEx.h"

namespace ALLIVaultCore
{
	class ALLINMMBPlainRepoP;
	class ALLINMMBEncryptedRepoP :
		public ALLINMEncryptedRepoPEx
	{
	public:
		ALLIVAULTCOREP_API ALLINMMBEncryptedRepoP();
		ALLIVAULTCOREP_API ~ALLINMMBEncryptedRepoP();
		ALLIVAULTCOREP_API ALLIVaultCore::ALLINMMBPlainRepoP *copyToPainRepo(const boost::filesystem::path &plainURL);

	private:
		virtual bool cloneFromRemoteRepoEx(const boost::filesystem::path &localURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)()) override;
	};
}

