#pragma once
#include "ALLISharingFolderP.h"
#include "alli_event.h"

namespace ALLIVaultCore
{
	class ALLISharingFolderExtP :
		public ALLISharingFolderP
	{
	public:
		ALLIVaultCore::Helpers::alli_event CopyFilesCompleted;
		ALLIVaultCore::FrontEnd::files_to_download_update_event FilesToDownloadUpdate;

		ALLISharingFolderExtP();
		ALLISharingFolderExtP(const ALLIVaultCore::ALLISharingFolderExtP &src);
		~ALLISharingFolderExtP();

		void copyFilesFromServerToSharingFolder(const boost::filesystem::path &sharingFolderURL);
		std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBP();

	private:
		ALLIVaultCore::Helpers::alli_mutex *dl_mutex;
		int dl_files_count;
		ALLIVaultCore::Helpers::alli_semaphore *dl_pool;
		ALLIVaultCore::Helpers::alli_mutex *server_path_mutex;

		void setupLocalSharingFolder(const boost::filesystem::path &sharingFolderURL);
		void downloadOneFileMT(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
		virtual std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBPImpl() = 0;
	};
}

