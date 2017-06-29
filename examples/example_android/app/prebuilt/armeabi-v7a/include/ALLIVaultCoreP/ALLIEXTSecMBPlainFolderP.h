#pragma once
#include "ALLIEXTSecPlainFolderP.h"
#include "alli_event.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class ALLIMailMessage;
	}
	class ALLIMailP;
	class ALLIEXTSecMBPlainRepoP;
	void mailbox_timer_wrapper(void *obj);
	void mb_heart_beat_timer_wrapper(void *obj);
	class ALLIEXTSecMBPlainFolderP :
		public ALLIEXTSecPlainFolderP
	{
	public:
		typedef ALLIVaultCore::latest_update_event::slot_type MBLatestUpdateSlotType;
		typedef ALLIVaultCore::Helpers::alli_event::slot_type MailListDBUpdatedSlotType;

		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainRepoP &plainRepo);
		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainFolderP const &src) = delete;
		ALLIEXTSecMBPlainFolderP &operator=(ALLIVaultCore::ALLIEXTSecMBPlainFolderP const &src) = delete;
		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainFolderP &&src) = delete;
		ALLIEXTSecMBPlainFolderP &operator=(ALLIVaultCore::ALLIEXTSecMBPlainFolderP &&src) = delete;
		~ALLIEXTSecMBPlainFolderP();

		void sendFiles(const std::vector<std::string> &fList, const std::unordered_set<std::string> &recList);
		boost::signals2::connection connectMBLatestUpdate(const MBLatestUpdateSlotType &slot);
		void connectPlainFolder(ALLIVaultCore::ALLIEXTSecPlainFolderP *src);
		std::unordered_set<std::string> convertRecipientList(const std::unordered_set<std::string> &src);

	private:
		friend void mailbox_timer_wrapper(void *obj);
		friend void mb_heart_beat_timer_wrapper(void *obj);
		typedef std::tuple<ALLIVaultCore::Engine::ALLIFolderIndex, std::string, std::chrono::time_point<std::chrono::system_clock>> temp_index_download_t;
		ALLIVaultCore::ALLIEXTSecMBPlainRepoP *mbPlainRepo;
		boost::filesystem::path *outboxURL;
		ALLIVaultCore::latest_update_event m_mbLatestUpdate;
		boost::filesystem::path *tempOutboxIndexDBURL;
		boost::filesystem::path *tempOutboxServerDBURL;
		// mutex to lock decrement of upload counter
		ALLIVaultCore::Helpers::alli_mutex *mb_ul_mutex;
		// shared resource: upload counter
		int mb_ul_files_count;
		// semaphore to control current uploading
		ALLIVaultCore::Helpers::alli_semaphore *mb_ul_pool;
		std::unordered_set<std::vector<std::string>> *tempIdxDBAESKeys, *tempServerDBAESKeys;
		std::string tempIdxDBSeverURL, tempInventoryDBServerURL;
		// init here and paired with plainRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_local_plain_folder;
		// not init here
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_plain_repo;
		// init here
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_encrypt_plain_folder;
		void *mailboxTimer, *mbLockTimer;
		int mb_sentinel_count, mb_lock_sentinel_count, mb_heart_beat_counter;
		ALLIVaultCore::Helpers::alli_mutex *mb_sentinel_mutex;
		boost::filesystem::path *inboxURL;
		ALLIVaultCore::ALLIEXTSecPlainFolderP *extPlainFolder;
		std::unique_ptr<boost::filesystem::path> tempInboxIndexDBURL;
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *tmpIdxTable;
		std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFolderIndex> *tmpIdxDict;
		std::unique_ptr<boost::filesystem::path> tempInboxServerDBURL;
		std::vector<ALLIVaultCore::ALLIMailP> mailList;
		ALLIVaultCore::Helpers::alli_mutex *mb_lock_sentinel_mutex;
		ALLIVaultCore::Helpers::alli_event m_MailListDBUpdated;
		bool isCheckingMailbox;

		bool downloadOneFileJsonImpl(const std::string &localPath, std::string &dest) override;
		void monitorPlainFolderImpl(const boost::filesystem::path &plainURL) override;
        bool trackFolderImpl(const std::string &fullPath) override;
		void ONMBLatestUpdate(ALLIVaultCore::latest_update_event_args &e);
		bool createTempFileIndex(const std::vector<std::string> &fList, const std::unordered_set<std::string> &recList);
		void copyFilesToOutbox(const std::vector<std::string> &fList);
		void uploadTempDBFiles(const std::unordered_set<std::string> &recList);
		int createFolderIndexDB(const boost::filesystem::path &folderIndexURL);
		int createServerInventoryDB(const boost::filesystem::path &serverInventoryURL);
		int createSharingKeySetDB(const boost::filesystem::path &serverInventoryURL);
		bool addFileToTempIndex(const std::string &fileName, const std::string &sha1, bool isEmptyFolder, alli_stat_t *fstat);
		bool mailOutFiles(const std::vector<std::string> &fList, const std::unordered_set<std::string> &recList);
		void uploadTempDBFilesEx(const std::map<std::string, std::string> &filesToUpload, const std::unordered_set<std::string> &recList);
		void deleteTempDBFiles(const std::map<std::string, std::string> &filesToUpload);
		bool sendTempDBInfoToRemoteServer(const std::unordered_set<std::string> &recList);
		void checkAESKeysForRecipients(const std::string &localSHA1, const std::string &filePath, std::unordered_map<std::string, std::string> &filesToUpload, const std::unordered_set<std::string> &recList);
		void uploadFilesToMailroom(const std::unordered_map<std::string, std::string> &filesToUpload, const std::unordered_set<std::string> &recList);
		void uploadOneTempDBFileSetMT(std::string &&localSHA1, std::string &&localURL, const std::unordered_set<std::string> &recList);
		bool sendTempDBInfoToRemoteServerEx(const std::unordered_map<std::string, std::vector<std::string>> &messages);
		bool insertRowToServerInventoryTemp(const std::string &localSha1, const std::string &serverSha1, const std::string &serverURL);
		void addAESKeyForOneFile(const std::string &serverSHA1, std::string &aesKeyPath, const std::string &recUserName, std::unordered_set<std::vector<std::string>> &aesKeys);
		void uploadOneFileSetMT(std::unique_ptr<std::tuple<std::string, std::string, std::unordered_set<std::string> const &>> &&payload);
		boost::filesystem::path encryptTempDBFile(const std::string &fileName, const std::unordered_set<std::string> &recList, std::unordered_set<std::vector<std::string>> &aesKeys);
		bool uploadAESKeys(const std::unordered_set<std::vector<std::string>> &aesKeys);
		std::unordered_set<std::vector<std::string>> convertToServerAESKeys(const std::unordered_set<std::vector<std::string>> &aesKeys);
		void deleteAESKeys(const std::unordered_set<std::vector<std::string>> &aesKeys);
		bool encryptMessageForRemoteServer(const std::string &recUserName, std::string &aMessage);
		void addAESKeyForOneFile_oss(const std::string &serverSHA1, std::string &aesKeyPath, const std::string &recUserName, std::unordered_set<std::vector<std::string>> &aesKeys);
		boost::filesystem::path encryptFileToSecureEncryptFolder(const std::string &fileName, const std::unordered_set<std::string> &recList, std::unordered_set<std::vector<std::string>> &aesKeys);
		bool insertAESKeysToMailboxKeySet(const std::string &serverSha1, const std::unordered_set<std::vector<std::string>> &aesKeys);
		void copyAESKeyForRecipients(const std::string &aesKeyPath, const std::string &filePath, const std::unordered_set<std::string> &recList, std::unordered_set<std::vector<std::string>> &aesKeys);
		bool insertAMessageToRemoteMailroomDB(const std::tuple<std::string, std::string, std::vector<unsigned char>, int> &aRecord);
		std::string copyAESKeyViaExpansion(const std::string &keyUser, const std::string &aesKeyPath, const std::string &serverSHA1);
		bool insertRowToKeySetTemp(const std::string &serverSha1, const std::string &keyUser, const std::string &aesKeyURL);
		std::string encryptAESKey(const std::string &keyUser, const std::string &aesKeyPath, const std::string &filePath);
		ALLIVaultCore::Helpers::ALLIMailMessage convertMailMessageForInsert(const std::tuple<std::string, std::string, std::vector<unsigned char>, int> &aRecord);
		void setupMailboxSentinel();
		void setupMailboxSentinelImpl();
		bool isMailListDBFileMissing();
		void load_mail_list();
		void checkMailboxStatus(void *obj);
		void increaseMBSentinelCount();
		void decreaseMBSentinelCount();
		bool checkMailboxStatusEx(std::unordered_map<std::string, ALLIVaultCore::Helpers::ALLIMailMessage> &newMails, bool &dbTimeout);
		void setupMailboxLockHeartBeatSentinel();
		void setupMailboxLockHeartBeatSentinelImpl();
		void processNewMails(const std::unordered_map<std::string, ALLIVaultCore::Helpers::ALLIMailMessage> &newMails);
		void processNewMailsEx(const std::unordered_map<std::string, ALLIVaultCore::Helpers::ALLIMailMessage> &newMails);
		void deleteTempInboxFolder();
		void closeMailboxLockHeartBeatSentinel();
		void OnMailReceived(ALLIVaultCore::Helpers::alli_event_args &e);
		bool isMaillistUpToDate(bool &dbTimedout);
		bool getMailboxLock(bool &dbTimedout);
		void mbLockHeartBeat(void *obj);
		bool decryptMessage(const std::string &suname, const std::string rawData, int msize, std::string &originalMessage);
		bool downloadTempDBFiles(const std::string &originalMessage, const std::string &suname, const std::chrono::time_point<std::chrono::system_clock> &sdate);
		bool updateAMessageToRemoteMailroomDB(const ALLIVaultCore::Helpers::ALLIMailMessage &aRecord);
		void processNewMails_safeUpdateLocalMaillistDB(const ALLIVaultCore::Helpers::ALLIMailMessage &aRecord);
		bool releaseMailboxLock(bool &dbTimedout);
		bool isRecordInMaillist(const std::string &suname, std::chrono::time_point<std::chrono::system_clock> &sdate);
		bool isMailboxDeadlock(bool &dbTimedout);
		void increaseMBLockSentinelCount();
		void decreaseMBLockSentinelCount();
		bool mbLockHeartBeatEx(bool &dbTimedout);
		bool decryptMailboxFile(const boost::filesystem::path &src, const boost::filesystem::path &aesFile, const boost::filesystem::path &dest);
		int load_tmp_index_db(const std::string &suname, const std::chrono::time_point<std::chrono::system_clock> &sdate);
		bool addRecordToMailListDB(const ALLIVaultCore::Helpers::ALLIMailMessage &aRecord);
		void OnMailListDBUpdated(ALLIVaultCore::Helpers::alli_event_args &e);
		int load_tmp_index_db_ex(const boost::filesystem::path &dbURL);
		void downloadOneFileTempMT(std::unique_ptr<temp_index_download_t> &&obj);
		int sf_query_callback(sqlite3_stmt *sqlstmt);
		bool downloadOneFileTemp(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow, const std::string &suname, const std::chrono::time_point<std::chrono::system_clock> &sdate);
		bool downloadOneFileTemp_oss(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow, const std::string &suname, const std::chrono::time_point<std::chrono::system_clock> &sdate);
		bool extractServerPathForFileTemp(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow, std::string &svrPath);
		void listServerPathDBTemp(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow);
		bool createEmptyFolder(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow, const std::string &suname, const std::chrono::time_point<std::chrono::system_clock> &sdate);
		bool retrieveAESKeypathForServerFileTemp(const std::string &serverSha1, const std::string &keyUser, std::string &anAESKeyPath);
		bool retrieveServerPathForFileEx(const std::string &localSha1, std::string &svrPath, const boost::filesystem::path &dbURL);
		bool retrieveAESKeypathForServerFileTempEx(const std::string &serverSha1, const std::string &keyUser, std::string &anAESKeyPath);
		bool insertAESKeysToLocalKeySetEx(const std::string &serverSha1, const std::unordered_set<std::vector<std::string>> &aesKeys, bool isServerPath);
		int load_mail_list_ex(const boost::filesystem::path *dbURL);
		int ml_query_callback(sqlite3_stmt *sqlstmt);
		bool commitStagedFiles(const std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &files, std::vector<std::string> &messages, std::string &src) override;
		void checkAESKeysForUser(const std::string &localSHA1, const std::string &filePath, std::unordered_map<std::string, std::string> &filesToUpload);
	};
}

