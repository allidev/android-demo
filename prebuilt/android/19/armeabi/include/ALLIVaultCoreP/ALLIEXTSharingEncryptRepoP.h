#pragma once
#include "ALLIEXTSharingRepoP.h"
namespace ALLIVaultCore
{
	namespace Engine
	{
		class SimpleRepositoryP;
	}
	class ALLIEXTSharingPlainRepoP;
	class ALLIEXTSharingEncryptRepoP :
		public ALLIEXTSharingRepoP
	{
	public:
		ALLIEXTSharingEncryptRepoP();
		~ALLIEXTSharingEncryptRepoP();

		void connectPlainRepoP(ALLIVaultCore::ALLIEXTSharingPlainRepoP *src);
		void initSimpleRepositoryP(const ALLIVaultCore::Engine::SimpleRepositoryP &src);
		void linkEncryptPlainMutex();
		void monitorSharingEncryptedRepository(const boost::filesystem::path &sharingEncryptedURL);

	private:
		ALLIVaultCore::ALLIEXTSharingPlainRepoP *shPlainRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingEncryptedRepoP;
	};
}

