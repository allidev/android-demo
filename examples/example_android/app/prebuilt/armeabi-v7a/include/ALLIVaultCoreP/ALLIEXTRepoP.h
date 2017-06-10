#pragma once
#include "ALLIRepoP.h"
#include "alli_event.h"
#include "alli_hash.h"
#include <unordered_map>
#include <unordered_set>

struct sqlite3_stmt;

namespace boost
{
	namespace signals2
	{
		class connection;
	}
	namespace filesystem
	{
		class path;
	}
}

namespace libgit2cpp
{
	class repository;
	class commit;
	class index;
}

namespace ALLIVaultCore
{
	enum class ALLIChangeStatusP;
	class latest_update_event_args;
	class repo_event_args;
	namespace Engine
	{
		class ALLIMonitorP;
	}
	namespace Helpers
	{
		class alli_event_args;
		class alli_mutex;
	}
	class ALLIEXTRepoP :
		public ALLIRepoP
	{
	public:
		typedef ALLIVaultCore::Helpers::alli_event::slot_type RepoFatalErrorSlotType;
		typedef ALLIVaultCore::repo_updated_event::slot_type RepoUpdatedSlotType;
		typedef ALLIVaultCore::latest_update_event::slot_type LatestUpdateSlotType;
		typedef ALLIVaultCore::Helpers::alli_event::slot_type IndexDBDeletedSlotType;
		typedef ALLIVaultCore::Helpers::alli_event::slot_type ServerInventoryDBDeletedSlotType;

		ALLIEXTRepoP();
		ALLIEXTRepoP(const ALLIVaultCore::ALLIEXTRepoP &src);
		virtual ~ALLIEXTRepoP();

		void set_hasInitialCommit(bool status);
		std::unordered_set<group_t> checkSharingGroupsForNM();
		boost::signals2::connection connectFatalError(const RepoFatalErrorSlotType &slot);
		boost::signals2::connection connectRepoUpdated(const RepoUpdatedSlotType &slot);
		boost::signals2::connection connectLatestUpdate(const LatestUpdateSlotType &slot);
		void updateTotalBytesUsed();
		void setTotalBytesUsed(unsigned long long totbytes);
		unsigned long long getTotalBytesUsed() const;
		void OnRepoUpdated(ALLIVaultCore::repo_event_args &e);
		void createRootGitIgnoreFile();
		bool trackFolder(const std::string &fullPath);
		void createSharingGroupDB();
		ALLIVaultCore::Engine::ALLIMonitorP *getMonitor() const;
		bool shouldTrackRemoteRepo() const;
		void trackRemoteRepo();
		std::string getCacheType();
		std::string getRepoHeadCommitSha1();
		bool addNewGroupToSharingGroupDB(const std::string &groupName, const std::string &hostUserName, std::string &groupSHA1, bool &hasGroup);
		bool deleteGroupFromSharingGroupDB(const std::string &hostUserName, const std::string &groupName);

	protected:
		unsigned long long totalBytesUsed;
		bool hasInitialCommit;
		ALLIVaultCore::Engine::ALLIMonitorP *monitor;
		bool m_trackRemoteRepo;
		bool has_verification_done;
		bool localRepoInAction;
		ALLIVaultCore::Helpers::alli_mutex *commit_remote_mutex;
		ALLIVaultCore::Helpers::alli_mutex *reloadingLock;
		ALLIVaultCore::Helpers::alli_mutex *mutDelete;
		std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> changeSet;
		std::map<std::string, std::string> filesBridge;
		bool isEncryptRepoProcessingFiles;
		bool isFinishUploading;

		/**
		** Copy changed files to the encrypted repo.
		** Return true if the op is successful and false otherwise.
		**/
		bool copyChangedFilesWithCommitMessage(const std::unordered_map<std::string, git_status_t> &files,
			const std::unordered_map<std::string, std::string> &sha1s,
			std::vector<std::string> &messages,
			int *fd);
		/**
		** Track working directory changes for an existing repo.
		** Return changed files in a dictionary. If the count of
		** of dictionary is zero, it means there are no changes.
		**/
		std::unordered_map<std::string, git_status_t> *trackWorkingDirectoryChanges();
		void processChangedFilesWithCommitMessage(const std::unordered_map<std::string, git_status_t> &files, std::vector<std::string> &messages, bool(*indexContainsMinimumFiles) (libgit2cpp::index *), bool isFinishUploading, std::string &src);
		void checkEmptyFolderCreated(const boost::filesystem::path &baseDir);
		bool commitStagedFilesLocallyWithMessageEx(std::vector<std::string> &messages);
		bool stageFileWithRelativePath(const std::string &fileName);
		bool stageRemovedFileToIndex(const std::string &fileName);
		bool deleteEmptyParentDirectory(const boost::filesystem::path &srcPath);
		void open_input_file(FILE **input, const boost::filesystem::path &src);
		FILE *open_input_file(const boost::filesystem::path &src, int _ShFlag);
		void open_output_file(FILE **output, const boost::filesystem::path &dest);
		void validate_dest(const boost::filesystem::path &dest);
		void open_public_key_file(FILE **pubKeyFile, const std::string &uname);
		void open_public_key_file(FILE **pubKeyFile);
		FILE *open_public_key_file(const std::string &uname, int _ShFlag);
		FILE *open_private_key_file(char **priKeyPath, int _ShFlag);
		boost::filesystem::path generateAESKeyFileName(const boost::filesystem::path &fileName, std::string &username);
		void monitorRepositoryP(const boost::filesystem::path &repoURL);
		std::unordered_map<std::string, std::string> getSha1ForPlainRepogit_odbChangedFiles(const std::unordered_map<std::string, git_status_t> &files);
		std::string getShaFromFile(const std::string &filePath);
		std::string getShaFromIndex(const std::string &filePath);
		bool filesBridgeExists();
		bool getLockOnFilesBridge(int *fd);
		bool releaseLockOnFilesBridge(int *fd);
		bool isWorkingDirectoryClean();
		bool saveBridgeDictionary(int *fd);
		bool isTempFile(const std::string &filePath);
		bool deleteFileAtSecureEncryptedFolder(const std::string &fileName, const std::string &sha);
		bool trackPlainFolder();
		bool trackEncryptFolder(const std::string &fullPath);
		std::map<std::string, std::string> importFilesBridge(ALLIVaultCore::Engine::SimpleRepositoryP *theRepo);
		bool saveBridgeDictionaryImplEx(int *fd, std::map<std::string, std::string> &filesBridge);
		bool safe_runOnRemoteTimerEx();
		void attachToEventHandlerForRepoFatalError();
		void detachEventHandlerForRepoFatalError();
		void reset_native_index();
		bool setIndexFile();
		libgit2cpp::index *get_native_index();
		void createCacheForServer(const std::string &headSHA1);
		void OnIndexDBDeleted(ALLIVaultCore::Helpers::alli_event_args &e);
		void OnServerInventoryDBDeleted(ALLIVaultCore::Helpers::alli_event_args &e);
		bool trackRepoEx();
		void localRepoCallbackEx_fire_update(bool git_op);
		void OnRepoLatestUpdate(ALLIVaultCore::latest_update_event_args &e);
		void localRepoCallbackEx_remote_timer(std::string &src, bool push_non_fastforward);
		void attachToEventHandlerForHeartBeat();
		void detachEventHandlerForHeartBeat();
		bool fileExistsInFilesBridge(const std::string &fileName);
		bool insertFilePair(const boost::filesystem::path &srcFile, const boost::filesystem::path &destFile);
		bool fileExistsInFilesBridgeEx(const std::string &fileName, const boost::filesystem::path &baseDir,
			const boost::filesystem::path &destDir, boost::filesystem::path &repoPath);
		std::string findKeyShaForValueShaEx(const std::string &valueSha, const std::map<std::string, std::string> &fb);
		void addToFilesBridge(const std::string &key, const std::string &value);
		bool trackEncryptFolderImplEx(const std::string &fullPath, bool &git_op);
		bool isGitIgnoreInOtherRepo(const boost::filesystem::path &fileName, libgit2cpp::index &index);
		std::string findKeyShaForValueSha(const std::string &valueSha);
		std::vector<std::string> allKeysForObject(const std::string &value, const std::map<std::string, std::string> &bridge);
		bool createCacheForRepoHead();

	private:
		boost::filesystem::path *groupDBURL;
		bool switching;
		ALLIVaultCore::Helpers::alli_event RepoFatalError;
		ALLIVaultCore::Helpers::alli_event IndexDBDeleted;
		ALLIVaultCore::Helpers::alli_event ServerInventoryDBDeleted;
		ALLIVaultCore::repo_updated_event RepoUpdated;
		ALLIVaultCore::latest_update_event RepoLatestUpdate;
		std::unordered_set<group_t> sharingGroups;
		bool is_finish_uploading;
		libgit2cpp::index *native_index;
		ALLIVaultCore::Helpers::alli_mutex *repoWatchList_mutex;
		std::unordered_map<std::string, std::string> *repoWatchList;

		bool getLockForChangedFile(const boost::filesystem::path &fileName, int *fd);
		bool releaseLockForChangedFile(int *fd);
		std::string buildCommitMessage(std::vector<std::string> &messages);
		std::vector<std::shared_ptr<libgit2cpp::commit>> createParentsVector(libgit2cpp::repository &repo);
		void processRepoFatalError(void *sender, ALLIVaultCore::Helpers::alli_event_args &e);
		std::unordered_set<group_t> load_group_db(const boost::filesystem::path &groupDBURL);
		int extrepo_query_callback(sqlite3_stmt *sqlstmt);
		virtual void updateTotalBytesUsedImpl();
		virtual void OnRepoUpdatedImpl(ALLIVaultCore::repo_event_args &e);
		virtual bool trackPlainFolderImpl();
		virtual std::unordered_map<std::string, std::string> getSha1ForPlainRepogit_odbChangedFilesImpl(const std::unordered_map<std::string, git_status_t> &files);
		bool getlockOnFilesBridgeEx(const boost::filesystem::path &workdir, int *fd);
		virtual bool copyChangedFilesWithCommitMessageImpl(const std::unordered_map<std::string, git_status_t> &files,
			const std::unordered_map<std::string, std::string> &sha1s,
			std::vector<std::string> &messages,
			int *fd);
		virtual bool saveBridgeDictionaryImpl(int *fd);
		bool encryptFileToSecureEncryptFolder(const std::string &fileName);
		virtual bool encryptFileToSecureEncryptFolderImpl(const std::string &fileName);
		virtual bool trackFolderImpl(const std::string &fullPath);
		virtual bool trackEncryptFolderImpl(const std::string &fullPath);
		virtual void processChangedFilesWithCommitMessageImpl(const std::unordered_map<std::string, git_status_t> &files, std::vector<std::string> &messages, bool(*indexContainsMinimumFiles) (libgit2cpp::index *), bool isFinishUploading, std::string &src);
		bool commitStagedFilesWithMessage(std::vector<std::string> &messages, bool(*indexContainsMinimumFiles) (libgit2cpp::index *), bool isFinishUploading, std::string &src);
		bool commitStagedFilesWithMessageImpl(std::vector<std::string> &messages, bool(*indexContainsMinimumFiles) (libgit2cpp::index *), bool isFinishUploading, std::string &src);
		void createCacheForLastCommit(const std::string &lastCommitSha1);
		void safe_pushCommitToServer();
		bool pushCommitToServer();
		bool doRollback();
		virtual void trackRemoteRepoImpl();
		bool runOnRemoteTimerEx();
		bool runOnRemoteTimerEx_setJobStartFlag(bool &jobCounterSet, bool &aLoop);
		bool fetchFromServer();
		bool mergeFastForward();
		virtual bool mergeFastForwardImpl();
		bool runOnRemoteTimerEx_encryptRepoFailed(bool &isSecureFolderSuccessful);
		virtual bool runOnRemoteTimerEx_encryptRepoFailedImpl(bool &isSecureFolderSuccessful);
		bool runOnRemoteTimerEx_encryptRepoBridgeSuccess(bool &aLoop);
		virtual bool runOnRemoteTimerEx_encryptRepoBridgeSuccessImpl(bool &aLoop);
		virtual bool trackRepoExImpl();
		virtual void localRepoCallbackEx_fire_updateImpl(bool git_op);
		virtual void localRepoCallbackEx_remote_timerImpl(std::string &src, bool push_non_fastforward);
		virtual bool insertFilePairImpl(const boost::filesystem::path &srcFile, const boost::filesystem::path &destFile);
		virtual std::string findKeyShaForValueShaImpl(const std::string &valueSha);
		bool foundInRepoWatchList(const std::string &fullPath);
		void addToRepoWatchList(const std::string &fullPath);
		bool indexContainsMinimumFiles(libgit2cpp::index *idx);
		virtual bool indexContainsMinimumFilesImpl(libgit2cpp::index *idx);
		virtual void createCacheForLastCommitImpl(const std::string &lastCommitSha1);
		virtual std::string getCacheTypeImpl();
		virtual std::string getRepoHeadCommitSha1Impl();
		virtual void createCacheForServerImpl(const std::string &headSHA1);
		virtual bool fileExistsInFilesBridgeImpl(const std::string &fileName);
		bool groupExists(const std::string &hostUserName, const std::string &groupName);
		virtual bool createCacheForRepoHeadImpl();
	};
}

