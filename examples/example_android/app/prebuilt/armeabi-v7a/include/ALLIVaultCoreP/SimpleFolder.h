#pragma once
#include "alli_common.h"
#include "sqlite3.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>
#include <utility>

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_mutex;
	}
	namespace Engine
	{
		enum class ALLIFileStatusP;
		class ALLIFolderIndex;
		class SimpleFolder
		{
		public:
			ALLIVaultCore::Helpers::alli_mutex *idx_mutex;
			std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> *idxDictP;
			ALLIVaultCore::Helpers::alli_mutex *servPathMutex;

			ALLIVAULTCOREP_API SimpleFolder(const boost::filesystem::path &folderURL, bool shouldCreateDB = false);
			ALLIVAULTCOREP_API SimpleFolder(bool isMailbox, const boost::filesystem::path &folderURL, bool shouldCreateDB = false);
			ALLIVAULTCOREP_API SimpleFolder(const boost::filesystem::path &folderURL, bool isSharing, const std::string &groupName, const std::string &hostUserName, bool shouldCreateDB = false);
			ALLIVAULTCOREP_API SimpleFolder(const boost::filesystem::path &folderURL, bool isMailbox, bool isSharing, const std::string &groupName, const std::string &hostUserName, bool shouldCreateDB = false);
			ALLIVAULTCOREP_API SimpleFolder(const ALLIVaultCore::Engine::SimpleFolder &src);
			ALLIVAULTCOREP_API ~SimpleFolder();
			ALLIVAULTCOREP_API std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> *trackWorkingDirectoryChanges(void);
			/**
			 ** load the folder index into memory.
			 ** return 0 if the sqlite db op is successful, and -1 otherwise.
			 **/
			ALLIVAULTCOREP_API int load_index_db(void);
			/**
			 ** return true if the sqlite db op is successful, and false otherwise.
			 ** The out param svrPath contains server path if it exists, and null if
			 ** it does not exist.
			 **/
			ALLIVAULTCOREP_API bool retrieveServerPathForFile(const std::string &localSha1, std::string &svrPath);
			ALLIVAULTCOREP_API bool retrieveServerPathForFileUsingFilePath(const std::string &localPath, std::string &svrPath);
			ALLIVaultCore::Engine::ALLIFolderIndex retrieveFolderIndexRow(const std::string &localPath);
			/**
			 ** return true if the sqlite db op is successful, and false otherwise.
			 ** The out param anAESKeyPath contains the aes key path if it exists, and
			 ** null if it does not exist.
			 **/
			ALLIVAULTCOREP_API bool retrieveAESKeypathForServerFile(const std::string &serverSha1, const std::string &keyUser, std::string &anAESKeyPath);
			ALLIVAULTCOREP_API unsigned long long updateTotalBytesUsed();
			ALLIVAULTCOREP_API const std::vector<std::string> *getFriendList();
			ALLIVAULTCOREP_API bool createVersionControlDB_class(const boost::filesystem::path &vcURL);
			ALLIVAULTCOREP_API bool isIndexDBFileMissing();
			ALLIVAULTCOREP_API bool isMailListDBFileMissing();
			ALLIVAULTCOREP_API void reset_index_sha_map();
			ALLIVAULTCOREP_API boost::filesystem::path getFileURL() const;
			ALLIVAULTCOREP_API boost::filesystem::path getIndexURL() const;
			ALLIVAULTCOREP_API void setIndexURL(const boost::filesystem::path &src);
			ALLIVAULTCOREP_API boost::filesystem::path getServerInventoryURL() const;
			ALLIVAULTCOREP_API boost::filesystem::path getFriendListURL() const;
			ALLIVAULTCOREP_API boost::filesystem::path getMailListURL() const;
			ALLIVAULTCOREP_API boost::filesystem::path getVersionControlURL() const;
			ALLIVAULTCOREP_API void init_serv_inv_sha();
			ALLIVAULTCOREP_API bool serv_inv_sha_up_to_date();
			ALLIVAULTCOREP_API void reset_serv_inv_sha();
			ALLIVAULTCOREP_API bool search_serv_inv_sha(const std::string &dbURL, int &err_retry);
			ALLIVAULTCOREP_API void serv_inv_sha_emplace(std::string &dbURL, std::string &sha1);
			ALLIVAULTCOREP_API void destruct_aes_key_path_dictP();
			ALLIVAULTCOREP_API bool search_serv_inv_dictP(const std::string &localSHA1);
			ALLIVAULTCOREP_API void destruct_serv_inv_dictP();
			ALLIVAULTCOREP_API void init_serv_inv_dictP();
			ALLIVAULTCOREP_API void serv_inv_dictP_emplace(const std::string &key, const std::tuple<std::string, std::string, std::string> &oneValue);

		private:
			boost::filesystem::path *fileURL;
			boost::filesystem::path *indexURL;
			boost::filesystem::path *serverInventoryURL;
			boost::filesystem::path *friendListURL;
			boost::filesystem::path *mailListURL;
			boost::filesystem::path *versionControlURL;
			std::vector<std::string> *friendList;
			unsigned long long totalBytesUsed;
			bool isALLIIndexEmpty;
			std::unordered_map<std::string, std::string> *serv_inv_sha;
			// there is no default hash function for tuple, use string instead
			std::unordered_map<std::string, std::string> *aes_key_path_dictP;
			ALLIVaultCore::Helpers::alli_mutex *aesKeyMutex;
			std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> *serv_inv_dictP;
			// temp server path from sqlite query
			std::string *serverPath;
			// temp aes key path from sqlite query
			std::string *aesKeyPath;
			std::unordered_map<std::string, std::string> *index_sha;

			void init_part1(const std::string &folderType, bool isSharing, const std::string &groupName, const std::string &hostUserName, bool &dbExists, boost::filesystem::path &folderIndexURL, boost::filesystem::path &serverInventoryURL, boost::filesystem::path &storeDir, bool shouldCreateDB);
			void init_part2(const std::string &folderType, const std::string &storeDir, const boost::filesystem::path &folderIndexURL, const boost::filesystem::path &serverInventoryURL, bool shouldCreateDB);
			void folder_init(const boost::filesystem::path &folderURL, bool isMailbox, bool isSharing, const std::string &groupName, const std::string &hostUserName, bool shouldCreateDB);
			std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> *alli_diff_p();
			void walk_thru_folder(const boost::filesystem::path &curFolder, std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> **files, std::unordered_set<std::string> *matchedFiles);
			void walk_thru_index(const boost::filesystem::path &curFolder, std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> *files, std::unordered_set<std::string> *matchedFiles);
			int comp_wd_index(const boost::filesystem::path &aFile, std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> *files, std::unordered_set<std::string> *matchedFiles);
			int comp_entry_workdir(const ALLIVaultCore::Engine::ALLIFolderIndex *aRow, const boost::filesystem::path &curFolder, std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> *files);
			int sf_query_callback(sqlite3_stmt *sqlstmt);
			int fl_query_callback(sqlite3_stmt *sqlstmt);
			int load_index_db_ex(const boost::filesystem::path &dbURL);
			int check_index_file_changes();
			std::unique_ptr<std::string> safe_check_index_sha_entry(std::pair<const std::string, std::string> &item);
			bool matchFileLengthAndModifiedTime(const boost::filesystem::path &aFile, const ALLIVaultCore::Engine::ALLIFolderIndex *aRow);
			bool retrieveServerPathForFileEx(const std::string &localSha1, const boost::filesystem::path &dbURL, std::string &svrPath);
			int load_friend_list(const boost::filesystem::path &dbURL);
			bool retrieveAESKeypathForServerFileEx(const std::string &serverSha1, const std::string &keyUser, std::string &anAESKeyPath, const boost::filesystem::path &dbURL);
			int query_aes_key_cb(sqlite3_stmt *sqlstmt);
			bool load_serv_inv_dictP_from_disk(const std::string &localSha1, std::string &svrPath);
			void search_serv_inv_dictP(const std::string &localSha1, std::string &svrPath);
		};
	}
}
