#pragma once
#include "ALLIEXTRepoP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecPlainFolderP;
	class ALLIEXTSecEncryptRepoP;
	class ALLIEXTSecPlainRepoP :
		public ALLIEXTRepoP
	{
	public:
		ALLIEXTSecPlainRepoP();
		virtual ~ALLIEXTSecPlainRepoP();

		void openPlainRepository(const boost::filesystem::path &plainURL);
		void setEncryptRepo(ALLIVaultCore::ALLIEXTSecEncryptRepoP *src);

	private:
		friend class ALLIEXTSecPlainFolderP;
		friend class ALLIEXTSecEncryptRepoP;
		ALLIVaultCore::Engine::SimpleRepositoryP *plainRepoP;
		ALLIVaultCore::ALLIEXTSecEncryptRepoP *secEncryptRepo;
		ALLIVaultCore::ALLIEXTSecPlainFolderP *secPlainFolder;
		// not init here and paired from secEncryptRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_encrypt_plain_repo;
		// not init here
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_plain_folder;
		// init here and used for remote repo monitoring
		// paired with secEncryptRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_plain_repo;
		ALLIVaultCore::Helpers::alli_mutex *checkSharingLock;
		ALLIVaultCore::Helpers::alli_mutex *trackMutex;

		bool trackPlainFolderImpl() override;
		std::unordered_map<std::string, std::string> getSha1ForPlainRepogit_odbChangedFilesImpl(const std::unordered_map<std::string, git_status_t> &files) override;
		bool saveBridgeDictionaryImpl(int *fd) override;
		bool encryptFileToSecureEncryptFolderImpl(const std::string &fileName) override;
		bool trackFolderImpl(const std::string &fullPath) override;
		bool fileExistsInFilesBridge(const std::string &fileName);
		bool insertFilePair(const boost::filesystem::path &srcFile, const boost::filesystem::path &destFile);
		virtual bool insertFilePairImpl(const boost::filesystem::path &srcFile, const boost::filesystem::path &destFile);
		void terminateThread();
		void deleteFile(const boost::filesystem::path &fileName);
		virtual void deleteFileImpl(const boost::filesystem::path &fileName);
	};
}

