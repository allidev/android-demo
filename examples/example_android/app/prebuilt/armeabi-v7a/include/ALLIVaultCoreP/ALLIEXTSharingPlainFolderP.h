#pragma once
#include "ALLIEXTSharingFolderP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSharingPlainRepoP;
	class ALLIEXTSharingPlainFolderP :
		public ALLIEXTSharingFolderP
	{
	public:
		ALLIEXTSharingPlainFolderP(ALLIVaultCore::ALLIEXTSharingPlainRepoP *pRepo);
		~ALLIEXTSharingPlainFolderP();

		void monitorSharingPlainFolderAtURL(const boost::filesystem::path &sharingPlainFolderURL);

	private:
		ALLIVaultCore::ALLIEXTSharingPlainRepoP *sharingPlainRepo;
		ALLIVaultCore::Engine::SimpleFolder *sharingPlainFolder;

		void load_index_db_ex() override;
		bool downloadOneFileJsonImpl(const std::string &localPath) override;
	};
}

