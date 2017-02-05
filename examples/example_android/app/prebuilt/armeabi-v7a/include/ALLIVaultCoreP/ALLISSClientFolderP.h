#pragma once
#include "ALLISharingFolderSyncP.h"

namespace ALLIVaultCore
{
	class ALLISSClientRepoP;
	class ALLISSClientFolderP :
		public ALLISharingFolderSyncP
	{
	public:
		ALLIVaultCore::Engine::SimpleFolder *sharingClientFolder;
		ALLIVaultCore::ALLISSClientRepoP *sharingClientRepo;

		ALLIVAULTCOREP_API ALLISSClientFolderP(ALLIVaultCore::ALLISSClientRepoP &scRepo);
		ALLIVAULTCOREP_API ALLISSClientFolderP(const ALLIVaultCore::ALLISSClientFolderP &src);
		ALLIVAULTCOREP_API ~ALLISSClientFolderP();

		void copyFileFromServerToSharingClientFolder(const boost::filesystem::path &sharingClientFolderURL);

	protected:
		virtual void load_index_db_ex() override;

	private:
		virtual std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBPImpl() override;
	};
}

