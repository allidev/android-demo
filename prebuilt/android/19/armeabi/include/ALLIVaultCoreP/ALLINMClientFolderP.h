#pragma once
#include "ALLINMFolderP.h"

namespace ALLIVaultCore
{
	class ALLINMClientRepoP;
	class ALLINMClientFolderP :
		public ALLINMFolderP
	{
	public:
		ALLIVaultCore::ALLINMClientRepoP *clientRepo;

		ALLIVAULTCOREP_API ALLINMClientFolderP();
		ALLIVAULTCOREP_API ALLINMClientFolderP(ALLIVaultCore::ALLINMClientRepoP *clientRepo);
		ALLINMClientFolderP(const ALLIVaultCore::ALLINMClientFolderP &src);
		ALLIVAULTCOREP_API ~ALLINMClientFolderP();
		ALLIVAULTCOREP_API void copyFilesFromServer(const boost::filesystem::path &clientFolderURL);

	private:
		ALLIVaultCore::Engine::SimpleFolder *clientFolder;

		void setupLocalClientFolder(const boost::filesystem::path &clientFolderURL);
		std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBP();
		std::string extractServerPathForFile(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
	};
}

