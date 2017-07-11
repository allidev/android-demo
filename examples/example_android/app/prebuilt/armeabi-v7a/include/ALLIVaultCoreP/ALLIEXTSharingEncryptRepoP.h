#pragma once
#include "ALLIEXTSharingRepoP.h"
namespace ALLIVaultCore
{
	namespace Engine
	{
		class SimpleRepositoryP;
	}
	namespace Helpers
	{
		class auto_reset_event;
	}
	class ALLIEXTSharingPlainRepoP;
	class ALLIEXTSharingPlainFolderP;
	class ALLIEXTSharingEncryptRepoP :
		public ALLIEXTSharingRepoP
	{
	public:
		ALLIEXTSharingEncryptRepoP();
		~ALLIEXTSharingEncryptRepoP();

		void connectPlainRepoP(ALLIVaultCore::ALLIEXTSharingPlainRepoP *src);
		void initSimpleRepositoryP(const ALLIVaultCore::Engine::SimpleRepositoryP &src);
		void linkEncryptPlainMutex();
		void monitorSharingEncryptedRepository(const boost::filesystem::path &sharingEncryptedURL);
		void expandAESKeysForNewGuestUser(const std::string &groupName, const std::string &guestUserName);
		void createSharingKeyFolder();
		void initializeDBForSharingFolder(const std::string &hostUserName, const std::string &groupName);

	private:
		friend class ALLIVaultCore::ALLIEXTSharingPlainRepoP;
		friend class ALLIVaultCore::ALLIEXTSharingPlainFolderP;
		ALLIVaultCore::ALLIEXTSharingPlainRepoP *shPlainRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingEncryptedRepoP;
		// init here and paired with secPlainRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_encrypt_plain_repo;
		// this is a weak pointer, do not call constructor and destructor in this class
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_plain_repo;
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_sharing_encrypt_repo;
		boost::filesystem::path *sharingKeyFolder;
		ALLIVaultCore::Helpers::auto_reset_event *encryp_folder_are;
		bool membershipRevoked;
		// not inited here
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_encrypt_plain_folder;
		bool sharingGroupDeleted;

		void trackRemoteRepoImpl() override;
		bool saveBridgeDictionaryImpl(int *fd) override;
		bool trackFolderImpl(const std::string &fullPath) override;
		bool trackEncryptFolderImpl(const std::string &fullPath) override;
		bool indexContainsMinimumFilesImpl(libgit2cpp::index *idx) override;
		void localRepoCallbackEx_fire_updateImpl(bool git_op) override;
		void createCacheForLastCommitImpl(const std::string &lastCommitSha1) override;
		bool runOnRemoteTimerEx_encryptRepoFailedImpl(bool &isSecureFolderSuccessful) override;
		/**
		** Track changes from remote server for a sharing repo.
		** Return true if succeeds and false otherwise.
		** @param memberDeleted is used to check if the memebership
		** for the current user has been revoked.
		**/
		bool trackSharingEncryptFolder(bool &memberDeleted);
		bool trackSharingEncryptFolder(bool &memberDeleted, bool isVerify);
		bool trackSharingEncryptFolderImpl(bool &memberDeleted, bool isVerify);
		void reloadSharingEncryptedRepository(const boost::filesystem::path &sharingEncryptedURL);
		bool walkThroughSharingPlainIndex(libgit2cpp::index *plainIndex, libgit2cpp::index *encryptIndex);
		bool walkThroughSharingEncryptedIndex(libgit2cpp::index &encryptIndex, libgit2cpp::index &plainIndex, bool &memberDeleted);
		void reloadSharingEncryptedRepositoryImpl(const boost::filesystem::path &sharingEncryptedURL);
		bool walkThroughSharingPlainIndexImpl(libgit2cpp::index *plainIndex, libgit2cpp::index *encryptIndex);
		bool walkThroughSharingEncryptedIndexImpl(libgit2cpp::index &encryptIndex, libgit2cpp::index &plainIndex, bool &memberDeleted);
		bool copyFileToPlainFolder(const boost::filesystem::path &fileName, bool &memberDeleted);
		bool open_aes_key_file(const boost::filesystem::path &aesKeyPath, FILE **aesKeyFile, bool &membershipRevoked, bool &memberDeleted);
		void OnGroupMembershipRevoked(ALLIVaultCore::Helpers::alli_event_args &e);
		void OnDeleteUserStarted(ALLIVaultCore::Helpers::alli_event_args &e);
		bool runOnRemoteTimerEx_encryptRepoBridgeSuccessImpl(bool &aLoop) override;
		bool trackSharingPlainRepo();
		bool trackRepoExImpl() override;
		void fire_latest_update_event_impl(ALLIVaultCore::ALLIActionDirectionP dir) override;
		void createCacheForServerImpl(std::string const &headSHA1) override;
		bool writeIndexDBEntriesToDiskImpl(int insertType) override;
		bool initIndexDBHistURLImpl() override;
		void processOneIndexDBRevisionImpl(std::vector<ALLIVaultCore::Engine::IndexDBFileEntry> &curIdxDBFEntry, std::unordered_set<std::string> &processedEntries) override;
		bool decryptIndexDBFileImpl(const boost::filesystem::path &src, boost::filesystem::path &dest) override;
		bool importIndexDBImpl(libgit2cpp::signature &cmtter, const boost::filesystem::path &dbFile) override;
		bool copyAESKeyForGuestUser(const boost::filesystem::path &filePath, const std::string &guestUserName);
	};
}

