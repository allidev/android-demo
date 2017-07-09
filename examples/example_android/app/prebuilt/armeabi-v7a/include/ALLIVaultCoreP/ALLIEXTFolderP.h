#pragma once
#include "ALLIFolderP.h"
#include "alli_types.h"
#include "alli_event.h"
#include <unordered_map>
#include <unordered_set>

struct sqlite3_stmt;

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIMonitorP;
		enum class ALLIFileStatusP;
		class ALLIFolderIndexHistory;
	}
	class ALLICacheP;
	class ALLIEXTRepoP;
	enum class ALLIChangeStatusP;
	class ALLIEXTFolderP :
		public ALLIFolderP
	{
	public:
		typedef ALLIVaultCore::FrontEnd::app_status_update_event::slot_type AppStatusUpdatedSlotType;

		ALLIEXTFolderP();
		ALLIEXTFolderP(const ALLIVaultCore::ALLIEXTFolderP &src);
		ALLIEXTFolderP &operator=(ALLIVaultCore::ALLIEXTFolderP const &src) = delete;
		virtual ~ALLIEXTFolderP();

		/**
		 * Get the list of files that are contained in the root folder.
		 *
		 * @return an unordered_map object of string and ALLIFolderIndex
		 */
		ALLIVAULTCOREP_API std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFolderIndex> getFolderContentList();
		ALLIVAULTCOREP_API std::string getFolderContentListJson();
		bool addUserToFriendListDB(const std::string &uname, const std::string &fname);
		void updateTotalBytesUsed();
		ALLIVAULTCOREP_API bool downloadOneFileJson(const std::string &localPath, std::string &dest);
		bool trackFolder(const std::string &fullPath);
		bool trackFolder(const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &src, const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &dest, bool isDirectory = false);
		bool trackRepoEx();
		boost::signals2::connection connectAppStatusUpdated(const AppStatusUpdatedSlotType &slot);
		bool hasSimpleFolderObject() const;
		void load_index_db();
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> getIdxTable();
		void createCacheForServer(std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> &changeSet);
		const std::vector<std::string> *getFriendList();
		bool renameFile(const std::string & old_path, const std::string & new_path, bool isDirectory);
		bool copyFile(const std::string & src_path, const std::string & dest_path, bool isDirectory);
		void checkDataVersion();
		bool retrieveFileHistory(std::vector<ALLIVaultCore::Engine::ALLIFolderIndexHistory> &fileHistory, const boost::filesystem::path &filePath);
		std::string getShaFromIndex(const std::string &fileName);

	protected:
		bool switching;
		std::string serverRootFolder;
		ALLIVaultCore::Engine::ALLIMonitorP *monitor;
		unsigned long long totalBytesUsed;
		ALLIVaultCore::ALLIEXTRepoP *extRepo;
		bool hasSharingKeySet;
		ALLIVaultCore::Helpers::alli_mutex *folderWatchList_mutex;
		std::unordered_map<std::string, std::string> *folderWatchList;
		long long totalBytesSentOSS;
		std::unordered_map<std::string, long long> totalBytesSentGroup;
		// mutex to lock writing to the server inventory table
		ALLIVaultCore::Helpers::alli_mutex *server_inv_mutex;
		// mutex to lock decrement of upload counter
		ALLIVaultCore::Helpers::alli_mutex *ul_mutex;
		// shared resource: upload counter
		int ul_files_count;
		// semaphore to control current uploading
		ALLIVaultCore::Helpers::alli_semaphore *ul_pool;
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *sharing_key_set;
		// used to coordinate multi-thread download threads
		ALLIVaultCore::Helpers::alli_semaphore *mtdl_pool;
		ALLIVaultCore::Helpers::alli_mutex *mt_count_mutex;
		int mtdl_remaining;
		boost::filesystem::path *indexDBHistURL;

		bool setDataVersion(int ver);
		bool isDataVersionSet(int ver);
		int verctrl_query_callback(sqlite3_stmt *sqlstmt, int ver);
		int updateDataVersion(int ver);
		virtual void updateTotalBytesUsedImpl();
		bool restoreFileAttributes(const std::string & localPath, const boost::filesystem::path &destURL);
		void monitorSimpleFolderP(const boost::filesystem::path &repoURL, const std::string &folder_type, std::string *groupName = nullptr, std::string *hostUserName = nullptr);
		void uploadFiles(const std::unordered_map<std::string, std::string> &filesToUpload);
		// return true if filePath is a temp file, and false otherwise
		bool isTempFile(const std::string &filePath);
		bool containsLocalSHA(const std::string &localSHA1);
		std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> trackWorkingDirectoryChanges();
		std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> createWorkingDirectoryChanges(const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &src, const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &dest, bool isDirectory);
		bool processChangedFilesWithCommitMessage(const std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &files, std::vector<std::string> &messages, std::string &src);
		bool processChangedFilesWithCommitMessageManual(const std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> &files, std::vector<std::string> &messages, std::string &src);
		bool foundInFolderWatchList(const std::string &fullPath);
		void addToFolderWatchList(const std::string &fullPath);
		void checkAESKeysForALLMembers(const std::string &localSHA1);
		void displayFileHistory();
		void OnAppStatusUpdated(ALLIVaultCore::FrontEnd::exist_user_event_args &e);
		void partitionServerInventoryDB();
		std::string updateMessageWithBytesSentOSS();
		std::string uploadOneFile(const std::string &fileName);
		std::string getServerURL(const std::string &fileName);
		bool insertRowToServerInventory(const std::string &localSha1, const std::string &serverSha1, const std::string &serverURL);
		bool insertRowToKeySey(const std::string &serverSha1, const std::string &keyUser, const std::string &aesKeyURL);
		bool publicKeyExists(const std::string &userName);
		bool uploadAESKeys(const std::unordered_set<std::vector<std::string>> &aesKeys);
		void deleteAESKeys(const std::unordered_set<std::vector<std::string>> &aesKeys);
		std::string encryptAESKey(const std::string &keyUser, const std::string &aesKeyPath, const std::string &filePath);
		bool writeToSharingKeySet(std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> &payload);
		void open_output_file_warning(FILE **output, const boost::filesystem::path &dest);
		bool retrieveFileHistoryEx(std::vector<ALLIVaultCore::Engine::ALLIFolderIndexHistory> &fileHistory, const boost::filesystem::path &filePath);

	private:
		bool hasFriendUserName;
		std::unordered_set<std::string> server_inv_updated;
		bool hasLocalSHA;
		std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> idxTable;
		std::unordered_set<std::string> matchedIdxRows;
		ALLIVaultCore::FrontEnd::app_status_update_event appStatusUpdated;

		virtual void load_index_db_ex();
		bool containsUserInFriendList(const std::string &uname);
		int friend_query_callback(sqlite3_stmt *sqlstmt);
		virtual bool downloadOneFileJsonImpl(const std::string &localPath, std::string &dest);
		virtual bool trackFolderImpl(const std::string &fullPath);
		void partitionALLIIndexDB();
		bool stageChangedFiles(const std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &files, std::vector<std::string> &messages, void **deleteSet, void **insertSet);
		bool stageChangedFilesManual(const std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> &files, std::vector<std::string> &messages, void **deleteSet, void **insertSet);
		bool stageFileWithRelativePath(const std::string &fileName);
		bool stageFileWithRelativePath(const std::string &fileName, void *payload);
		bool stageFileWithRelativePath(const std::string &fileName, const std::string &orig, void *payload);
		bool stageFileWithRelativePath(const std::string &fileName, bool modified);
		bool stageRemovedFileToIndex(const std::string &fileName);
		bool stageRemovedFileToIndex(const std::string &fileName, void *payload);
		bool processChangedFiles_commitStagedFiles(const std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &files, std::vector<std::string> &messages, std::string &src, void *deleteSet, void *insertSet);
		bool processChangedFiles_commitStagedFilesManual(const std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> &files, std::vector<std::string> &messages, std::string &src, void *deleteSet, void *insertSet);
		int appendSQLiteDB(const boost::filesystem::path *src, const boost::filesystem::path &dest, const std::string &tableName);
		int appendSQLiteDBEx(const boost::filesystem::path *src, const boost::filesystem::path &dest, const std::string &tableName);
		int readFromSource(const boost::filesystem::path *src, const std::string &tableName, void *payload);
		int writeToDestination(const boost::filesystem::path &dest, const std::string &tableName, void *payload);
		int append_query_callback(sqlite3_stmt *sqlstmt, void *payload, const std::string &tableName);
		bool emptyFolderIndexDB(const boost::filesystem::path *origin);
		bool deleteFileFromIndex(const std::string &fileName);
		bool deleteFileFromIndexEx(const std::string &fileName, const boost::filesystem::path *dbURL);
		bool addFileToIndex(const std::string &fileName, const std::string &sha1, bool isEmptyFolder, alli_stat_t *fstat);
		bool writeToIndexDB(void *payload);
		bool writeToIndexDBInsert(void *payload);
		bool writeToIndexDBInsert(void *payload, const std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> &files);
		virtual bool commitStagedFiles(const std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &files, std::vector<std::string> &messages, std::string &src);
		virtual bool commitStagedFilesManual(const std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> &files, std::vector<std::string> &messages, std::string &src);
		bool expandInsertSet(void **payload);
		bool expandInsertSet(void **payload, const std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> &files);
		bool convertDeleteSet(void **payload);
		virtual bool containsLocalSHAImpl(const std::string &localSHA1);
		virtual void checkAESKeysForALLMembersImpl(const std::string &localSHA1);
		bool containsLocalSHAEx(const std::string &localSHA1, const boost::filesystem::path &dbURL);
		virtual void uploadFilesImpl(const std::unordered_map<std::string, std::string> &filesToUpload);
		int server_query_callback(sqlite3_stmt *sqlstmt);
		virtual bool trackFolderImpl(const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &src, const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &dest, bool isDirectory);
		bool walk_thru_folderEx(const boost::filesystem::path &curFolder);
		void walk_thru_index();
		// return 0 on success and -1 on error.
		int comp_wd_indexEx(const boost::filesystem::path &aFile);
		void comp_wd_indexEx_IndexIterator(bool &findMatch, bool &isModified, ALLIVaultCore::Engine::ALLIFolderIndex &aRow, std::string &idx_path, const std::string &relativePath, const boost::filesystem::path &aFile, bool isDirectory);
		bool matchFileLengthAndModifiedTime(const boost::filesystem::path &aFile, const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
		bool matchFileLengthAndModifiedTimeP(const boost::filesystem::path &aFile, const std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex> &aRow);
		int comp_wd_indexEx_processResults(bool findMatch, bool isModified, const std::string &idx_path, const ALLIVaultCore::Engine::ALLIFolderIndex &aRow, const std::string &relativePath, ALLIVaultCore::ALLICacheP &syncCache, const boost::filesystem::path &aFile, bool isDirectory);
		bool fileInLocalFolderIndex(const std::string &relativePath, ALLIVaultCore::ALLICacheP &syncCache);
		void updateOneRowExMT(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
		void updateOneRowExMTP(const std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex> &aRow);
		bool updateOneRowEx(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
		bool updateOneRowExP(const std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex> &aRow);
		std::string uploadOneFile(const std::string &fileName, bool &isUploaded);
		std::string uploadOneFile_oss(const std::string &fileName, bool &isUploaded);
		bool emptyServerInventoryDB(const boost::filesystem::path *origin);
		void uploadOneFileMT(const std::pair<std::string, std::string> &obj);
		bool insertRowToServerInventory(const std::string &localSha1, const std::string &serverSha1, const std::string &serverURL, const bool &isUploaded);
		virtual std::string updateMessageWithBytesSentOSSImpl();
		void uploadFilesImpl_fire_event();
		virtual void displayFileHistoryImpl();
		virtual void createCacheForServerImpl(std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> &changeSet);
		virtual bool retrieveFileHistoryImpl(std::vector<ALLIVaultCore::Engine::ALLIFolderIndexHistory> &fileHistory, const boost::filesystem::path &filePath);
		int fileHistory_query_cb(sqlite3_stmt *sqlstmt, std::vector<ALLIVaultCore::Engine::ALLIFolderIndexHistory> &fileHistory);
	};
}

