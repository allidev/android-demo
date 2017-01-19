#pragma once
#include "ALLISharingFolderFromP.h"

namespace ALLIVaultCore
{
	class ALLISFClientRepoP;
	class ALLISFClientFolderP :
		public ALLISharingFolderFromP
	{
	public:
		ALLIVaultCore::Engine::SimpleFolder *sharingClientFolder;
		ALLIVaultCore::ALLISFClientRepoP *sharingClientRepo;

		ALLIVAULTCOREP_API ALLISFClientFolderP(ALLIVaultCore::ALLISFClientRepoP &sfRepo);
		ALLIVAULTCOREP_API ~ALLISFClientFolderP();

		void copyFileFromServerToSharingClientFolder(const boost::filesystem::path &sharingClientFolderURL);

	private:
		virtual std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBPImpl() override;
		virtual void load_index_db_ex() override;
	};
}

