#pragma once
#include "ALLINMFolderP.h"
#include "alli_event.h"

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIFolderIndex;
	}
	class ALLINMPlainFolderExP :
		public ALLINMFolderP
	{
	public:
		ALLIVaultCore::FrontEnd::files_to_download_update_event FilesToDownloadUpdate;

		ALLINMPlainFolderExP();
		ALLINMPlainFolderExP(const ALLIVaultCore::ALLINMPlainFolderExP &src);
		~ALLINMPlainFolderExP();
		ALLIVAULTCOREP_API void copyFilesFromServerToPlainFolder(const boost::filesystem::path &plainFolderURL);

	protected:
		ALLIVaultCore::Engine::SimpleFolder *plainFolder;
		// mutex to lock decrement of download counter
		ALLIVaultCore::Helpers::alli_mutex *dl_mutex;
		// shared resource: download counter
		int dl_files_count;
		// semaphore to control current downloading
		ALLIVaultCore::Helpers::alli_semaphore *dl_pool;
		ALLIVaultCore::Helpers::alli_mutex *server_path_mutex;

		virtual std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBP() = 0;
		virtual void downloadOneFileMT(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow) = 0;
		std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *extractIndexDBPEx(const boost::filesystem::path &baseDir);
		virtual void copyFilesFromServerToPlainFolderEx(const boost::filesystem::path &plainFolderURL);

	private:
		void setupLocalPlainFolder(const boost::filesystem::path &plainFolderURL);
	};
}

