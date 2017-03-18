#pragma once
#include "ALLIEXTSharingRepoP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSharingEncryptRepoP;
	class ALLIEXTSharingPlainRepoP :
		public ALLIEXTSharingRepoP
	{
	public:
		ALLIEXTSharingPlainRepoP();
		ALLIEXTSharingPlainRepoP(const boost::filesystem::path &sharingPlainRepoURL);
		~ALLIEXTSharingPlainRepoP();

		void monitorSharingPlainRepository(const boost::filesystem::path &shPlainURL);
		void connectEncryptRepoP(ALLIVaultCore::ALLIEXTSharingEncryptRepoP *src);

	private:
		ALLIVaultCore::ALLIEXTSharingEncryptRepoP *shEncryptRepo;

		bool trackFolderImpl() override;
	};
}

