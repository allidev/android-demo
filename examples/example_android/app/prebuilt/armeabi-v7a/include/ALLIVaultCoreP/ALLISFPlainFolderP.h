#pragma once
#include "ALLISharingFolderFromP.h"

namespace ALLIVaultCore
{
	class ALLISFPlainRepoP;
	class ALLISFPlainFolderP :
		public ALLISharingFolderFromP
	{
	public:
		ALLIVaultCore::Engine::SimpleFolder *sharingPlainFolder;
		ALLIVaultCore::ALLISFPlainRepoP *sharingPlainRepo;

		ALLIVAULTCOREP_API ALLISFPlainFolderP(ALLIVaultCore::ALLISFPlainRepoP &sfRepo);
		ALLIVAULTCOREP_API ~ALLISFPlainFolderP();

		ALLIVAULTCOREP_API void copyFilesFromServerToSharingPlainFolder(const boost::filesystem::path &sharingPlainFolderURL);

	private:
		virtual std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBPImpl() override;
		virtual void load_index_db_ex() override;
		virtual bool downloadOneFileEx(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow) override;
	};
}

