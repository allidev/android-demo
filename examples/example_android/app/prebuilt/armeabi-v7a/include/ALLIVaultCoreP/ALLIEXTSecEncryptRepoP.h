#pragma once
#include "ALLIEXTRepoP.h"

namespace ALLIVaultCore
{
	class ALLIEXTSecPlainFolderP;
	class ALLIEXTSecPlainRepoP;
	class ALLIEXTSecEncryptRepoP :
		public ALLIVaultCore::ALLIEXTRepoP
	{
	public:
		ALLIEXTSecEncryptRepoP();
		ALLIEXTSecEncryptRepoP(const ALLIEXTSecEncryptRepoP &src);
		virtual ~ALLIEXTSecEncryptRepoP();

		void openEncryptedRepository(const boost::filesystem::path &encryptedURL);
		void initializeDBForSyncFolder();
		void linkSecPlainRepo(ALLIVaultCore::ALLIEXTSecPlainRepoP *src);

	private:
		friend class ALLIEXTSecPlainFolderP;
		friend class ALLIEXTSecPlainRepoP;
		ALLIVaultCore::ALLIEXTSecPlainRepoP *secPlainRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *encryptedRepoP;
		// init here and paired with secPlainRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_encrypt_plain_repo;
		// init here and used alone and unpaired
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_encrypt_repo;
		// not init here
		ALLIVaultCore::Helpers::alli_mutex *mutex_encrypt_plain_folder;
		bool isFinishUploading;
		std::map<std::string, std::string> filesBridge;
		ALLIVaultCore::Helpers::alli_mutex *trackMutex;
		std::unordered_map<std::string, std::string> *repoWatchList;
		ALLIVaultCore::Helpers::alli_mutex *repoWatchList_mutex;
		bool isEncryptRepoProcessingFiles;

		void updateTotalBytesUsedImpl() override;
		void openEncryptedRepositoryEx(const boost::filesystem::path &encryptedURL);
		bool trackFolderImpl(const std::string &fullPath) override;
		bool trackEncryptFolderImpl(const std::string &fullPath) override;
		bool saveBridgeDictionaryImpl(int *fd) override;
		void insertFilesBridge(const std::string &key, const std::string &val);
		ALLIVaultCore::Helpers::alli_mutex *getMutexEncryptPlainRepo() const;
		void trackRemoteRepoImpl() override;
		bool runOnRemoteTimerEx_encryptRepoFailedImpl(bool &isSecureFolderSuccessful) override;
		/**
		** Track changes from remote server for sync repo.
		** Return true if succeeds and false otherwise.
		**/
		bool trackSecureEncryptFolder();
		bool trackSecureEncryptFolder(bool isVerify);
		void reloadEncryptedRepository(const boost::filesystem::path &encryptedRepo);
		void attachToEventHandlerForHeartBeat();
		void detachEventHandlerForHeartBeat();
		bool walkThroughPlainIndex(libgit2cpp::index &plainIndex, libgit2cpp::index &encryptIndex);
		bool walkThroughEncryptedIndex(libgit2cpp::index &encryptIndex, libgit2cpp::index &plainIndex);
		std::string getRepoHeadCommitSha1();
		bool updateFilesBridge();
		bool isEntrySymlinkInOtherRepo(const boost::filesystem::path &fileName, libgit2cpp::index &encryptIndex);
		bool isGitIgnoreInOtherRepo(const boost::filesystem::path &fileName, libgit2cpp::index &index);
		std::vector<std::string> allKeysForObject(const std::string &value, const std::map<std::string, std::string> &bridge);
		bool isEntryInOtherRepo(const std::string &sha, const boost::filesystem::path &fileName, libgit2cpp::index &index);
		bool copyFileToPlainFolder(const boost::filesystem::path &fileName);
		virtual bool copyFileToPlainFolderImpl(const boost::filesystem::path &fileName);
		bool copyFileToPlainFolderEx(const boost::filesystem::path &fileName);
		bool runOnRemoteTimerEx_encryptRepoBridgeSuccessImpl(bool &aLoop) override;
		bool trackPlainRepo();
		bool trackRepoExImpl() override;
		bool foundInRepoWatchList(const std::string &fullPath);
		void addToRepoWatchList(const std::string &fullPath);
		void localRepoCallbackEx_fire_updateImpl(bool git_op) override;
		void localRepoCallbackEx_remote_timerImpl(std::string &src, bool push_non_fastforward) override;
	};
}

