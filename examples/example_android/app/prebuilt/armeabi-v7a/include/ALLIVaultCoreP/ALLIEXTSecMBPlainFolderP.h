#pragma once
#include "ALLIEXTSecPlainFolderP.h"
#include "alli_event.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class ALLIMailMessage;
	}
	class ALLIEXTSecMBPlainRepoP;
	class ALLIEXTSecMBPlainFolderP :
		public ALLIEXTSecPlainFolderP
	{
	public:
		typedef ALLIVaultCore::latest_update_event::slot_type MBLatestUpdateSlotType;

		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainRepoP &plainRepo);
		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainFolderP const &src) = delete;
		ALLIEXTSecMBPlainFolderP &operator=(ALLIVaultCore::ALLIEXTSecMBPlainFolderP const &src) = delete;
		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainFolderP &&src) = delete;
		ALLIEXTSecMBPlainFolderP &operator=(ALLIVaultCore::ALLIEXTSecMBPlainFolderP &&src) = delete;
		~ALLIEXTSecMBPlainFolderP();

		void sendFiles(const std::vector<std::string> &fList, const std::unordered_set<std::string> &recList);
		boost::signals2::connection connectMBLatestUpdate(const MBLatestUpdateSlotType &slot);

	private:
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
		bool isMailListDBFileMissing();
		void load_mail_list();
	};
}

