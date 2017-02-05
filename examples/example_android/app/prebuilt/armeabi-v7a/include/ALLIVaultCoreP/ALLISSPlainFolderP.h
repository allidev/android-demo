#pragma once
#include "ALLISharingFolderSyncP.h"

namespace ALLIVaultCore
{
	class ALLISSPlainRepoP;
	class ALLISSPlainFolderP :
		public ALLISharingFolderSyncP
	{
	public:
		ALLIVaultCore::Engine::SimpleFolder *sharingPlainFolder;
		ALLIVaultCore::ALLISSPlainRepoP *sharingPlainRepo;

		ALLIVAULTCOREP_API ALLISSPlainFolderP(ALLIVaultCore::ALLISSPlainRepoP &spRepo);
		ALLISSPlainFolderP(const ALLIVaultCore::ALLISSPlainFolderP &src);
		ALLIVAULTCOREP_API ~ALLISSPlainFolderP();

		ALLIVAULTCOREP_API void copyFilesFromServerToSharingPlainFolder(const boost::filesystem::path &sharingPlainFolderURL);

	protected:
		virtual void load_index_db_ex() override;

	private:
		virtual bool downloadOneFileEx(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow) override;
		virtual std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBPImpl() override;
	};
}

