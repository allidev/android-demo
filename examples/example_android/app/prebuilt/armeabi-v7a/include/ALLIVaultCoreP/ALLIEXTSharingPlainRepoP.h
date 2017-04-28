#pragma once
#include "ALLIEXTSharingRepoP.h"
namespace ALLIVaultCore
{
	namespace Helpers
	{
		class auto_reset_event;
	}
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
		ALLIVaultCore::Helpers::auto_reset_event *sharingPlainCondition;

		bool trackFolderImpl(const std::string &fullPath) override;
	};
}

