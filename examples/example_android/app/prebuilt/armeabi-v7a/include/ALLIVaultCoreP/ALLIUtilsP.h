#pragma once

#include "alli_common.h"
#ifndef ALLI_HEADERS_ONLY
#include "../ALLIVaultCore/git2/types.h"
#include "../ALLIVaultCore/sqlite3.h"
#else
#include "git2/types.h"
#include "sqlite3/sqlite3.h"
#endif
#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <unordered_set>
#include <unordered_map>

typedef struct _FILETIME FILETIME;

namespace boost
{
	namespace filesystem
	{
		class path;
		class directory_entry;
	}
}

namespace libgit2cpp
{
	class tree;
	class repository;
}

namespace ALLIVaultCore
{
	enum class ALLIRepoTypeP;
	namespace Engine
	{
		class ALLIFolderIndex;
	}
	namespace Helpers
	{
		template<typename Source>
		boost::filesystem::path &appendBoostPath(boost::filesystem::path &lhs, const Source &rhs)
		{
#ifdef ALLI_WIN32
			return lhs /= rhs;
#else
			lhs += "/";
			return lhs += rhs;
#endif
		};
		class ALLIUtilsP
		{
		public:
			static ALLIVAULTCOREP_API bool userDefinedFolder;
			static ALLIVAULTCOREP_API bool are_git_threads_shutdown;
			static ALLIVAULTCOREP_API bool git_native_calls_enabled;
			static ALLIVAULTCOREP_API bool sync_new_machine_sharing_groups_finished;
			static ALLIVAULTCOREP_API bool isTesting;
			static ALLIVAULTCOREP_API bool corepTestingOnly;
			static ALLIVAULTCOREP_API boost::filesystem::path *ALLIHomeFolderPath;
			static ALLIVAULTCOREP_API boost::filesystem::path *ALLIMyDocumentsPath;
			static ALLIVAULTCOREP_API boost::filesystem::path *ALLITestingRootFolderPath;
#ifdef ALLI_WIN32
			static ALLIVAULTCOREP_API std::wstring ALLIRegistryName;
#endif
			static ALLIVAULTCOREP_API std::string alliUserName;
			static ALLIVAULTCOREP_API std::string alliVersion;
			static ALLIVAULTCOREP_API std::string ID_name;
			static ALLIVAULTCOREP_API std::string ALLIHOST;
			static ALLIVAULTCOREP_API void(*filePermPtr) (const boost::filesystem::path &);

			static ALLIVAULTCOREP_API bool deleteEmptyParentDirectory(const boost::filesystem::path &srcPath, const boost::filesystem::path &topFolder);
			static ALLIVAULTCOREP_API int convertBoostPathToChar(char **dest, const boost::filesystem::path &btPath);
			static ALLIVAULTCOREP_API std::string convertBoostPathToUTF8String(const boost::filesystem::path &fs_path);
			static ALLIVAULTCOREP_API std::unique_ptr<boost::filesystem::path> convertUTF8StringToBoostPath(const std::string &path_str);
			static ALLIVAULTCOREP_API boost::filesystem::path convertCharToBoostPath(const char *src);
			static ALLIVAULTCOREP_API void checkErrorRetries(const int &err_retry, const std::string &err_text, const std::string &err_title);
			static ALLIVAULTCOREP_API void checkErrorRetries(const int &err_retry, const std::string &err_text, const std::string &err_title, const char *file, const int line);
			static ALLIVAULTCOREP_API void checkErrorRetries(const int &err_retry, const std::string &err_text, const std::string &err_title, bool &networkFailed);
			static ALLIVAULTCOREP_API void checkErrorRetries(const int &err_retry, int max, const std::string &err_text, const std::string &err_title);
			static ALLIVAULTCOREP_API void checkErrorRetries(const int &err_retry, int max, const std::string &err_text, const std::string &err_title, const char *file, const int line);
			static ALLIVAULTCOREP_API void checkErrorRetries(const int &err_retry, int max, const std::string &err_text, const std::string &err_title, bool &networkFailed);
			static ALLIVAULTCOREP_API void checkErrorRetries(const int &err_retry, int max, const std::string &err_text, const std::string &err_title, bool &networkFailed, const char *file, const int line);
			static ALLIVAULTCOREP_API bool checkForGitIgnoreFile(const boost::filesystem::path &src, const boost::filesystem::path &dest);
			static ALLIVAULTCOREP_API bool checkForSymlinkFile(const boost::filesystem::path &src, const boost::filesystem::path &dest);
			static ALLIVAULTCOREP_API bool copyFileMode(const boost::filesystem::path &srcPath, const boost::filesystem::path &destPath);
			static ALLIVAULTCOREP_API boost::filesystem::path extractPublicRSAKeyFileForUser(const std::string &username);
			static ALLIVAULTCOREP_API boost::filesystem::path extractPrivateRSAKeyFile(const std::string &username);
			static ALLIVAULTCOREP_API std::string generateAESKeyFileTempName(const std::string &fileName, const std::string &username);
			static ALLIVAULTCOREP_API void get_real_private_key(char **priKeyPath, const std::string &uname);
			static ALLIVAULTCOREP_API void get_real_private_key(char **priKeyPath, const boost::filesystem::path &key_path);
			static ALLIVAULTCOREP_API const boost::filesystem::path *getALLITempPath_Portable();
			static ALLIVAULTCOREP_API std::vector<std::shared_ptr<boost::filesystem::path>> getDirectories(const boost::filesystem::path &curFolder);
			static ALLIVAULTCOREP_API std::vector<std::shared_ptr<boost::filesystem::path>> getFiles(const boost::filesystem::path &curFolder);
			static ALLIVAULTCOREP_API int tryLockFiles(const boost::filesystem::path &curFolder);
			static ALLIVAULTCOREP_API const boost::filesystem::path *getHomeFolderPath();
			static void setHomeFolderPath(const boost::filesystem::path &rootPath);
			static ALLIVAULTCOREP_API const boost::filesystem::path *getMyDocumentsPath();
			static ALLIVAULTCOREP_API const boost::filesystem::path *getAppFolderPath();
			static ALLIVAULTCOREP_API std::string getMysqlPassword();
			static ALLIVAULTCOREP_API git_repository *getNativeRepo(boost::filesystem::path *repo_path);
			/**
			** return true if db is created successfully, false if the op failed.
			** On failure, the db file will be automatically deleted.
			**/
			static ALLIVAULTCOREP_API bool createSqliteDB(const boost::filesystem::path &dbURL, const std::string &tableName, const std::string &colDef);
			static ALLIVAULTCOREP_API std::unique_ptr<std::string> getRelativePath(const boost::filesystem::path &filePath, const boost::filesystem::path &rootFolder);
			/// <summary>
			///   return value needs to be freed or otherwise wrapped in a unique_ptr object.
			/// </summary>
			static ALLIVAULTCOREP_API std::string *getShaFromFile(const boost::filesystem::path &filePath);
			static ALLIVAULTCOREP_API bool getShaFromFile(const boost::filesystem::path &filePath, std::string &sha1);
			static ALLIVAULTCOREP_API bool getShaFromUTF8String(const std::string &src, std::string &sha1);
			static std::string getShaFromUTF8String(const std::string &src);
			static ALLIVAULTCOREP_API bool getPasswordSha1(const std::string &uname, const std::string &password, std::string &sha1);
			static ALLIVAULTCOREP_API bool isWindowsXP();
			static ALLIVAULTCOREP_API std::string retrieveUserNameFromIdentityFile();
			static bool deleteIdentityFile();
			static ALLIVAULTCOREP_API void safeDeleteAFile(const boost::filesystem::path &aFile);
			static ALLIVAULTCOREP_API void safeDeleteAFileAsync(void *obj);
			static ALLIVAULTCOREP_API int safeDeleteDirectory(const boost::filesystem::path &dir);
			static ALLIVAULTCOREP_API int directoryHouseKeeping(const boost::filesystem::path &curURL);
			static boost::filesystem::path validateRootFolderForSharingGits();
			static ALLIVAULTCOREP_API int validateDestinationPath(const boost::filesystem::path &dest);
			static ALLIVAULTCOREP_API std::string getALLIVersion();
			static ALLIVAULTCOREP_API std::string getID_name();
			static ALLIVAULTCOREP_API void setRegistryKey(std::string key, int val);
			static ALLIVAULTCOREP_API bool str_starts_with(const std::string &src, const std::string &dest);
			static ALLIVAULTCOREP_API bool str_ends_with(const std::string &src, const std::string &dest);
			static ALLIVAULTCOREP_API bool boost_path_starts_with(const boost::filesystem::path &src, const std::string &dest);
			static ALLIVAULTCOREP_API bool boost_path_ends_with(const boost::filesystem::path &src, const std::string &dest);
			static ALLIVAULTCOREP_API std::unique_ptr<libgit2cpp::tree> writeTreeWithRepository(libgit2cpp::repository &repo);
			static ALLIVAULTCOREP_API bool restoreFileAttributes(const ALLIVaultCore::Engine::ALLIFolderIndex &aRow, const boost::filesystem::path &destURL);
			template <typename T>
			static std::string to_string(T t, unsigned int decimal)
			{
				std::string ret = std::to_string(t);
				size_t pos = ret.find('.');
				ret = ret.substr(0, pos + decimal + 1);
				return ret;
			};
			static std::string buildLogHeader(const boost::filesystem::path &srcFileName, int lineNumber);
			static ALLIVAULTCOREP_API int querySqliteDB(const boost::filesystem::path &dbURL,
				const std::string &tableName,
				const std::string &sqlstmt,
				const std::string *pragma,
				std::vector<void *> *params,
				int(*binding_callback) (sqlite3_stmt *, std::vector<void *> *params),
				int(*sqlite_query_cb) (sqlite3_stmt *));
			static ALLIVAULTCOREP_API std::string format_time_t(time_t src_time);
			static ALLIVAULTCOREP_API std::string format_time_point(const std::chrono::time_point<std::chrono::system_clock> &tp);
			static ALLIVAULTCOREP_API int convert_string_2_char(char **dest, const std::string &src);
			static ALLIVAULTCOREP_API bool isSourceFileReady(const boost::filesystem::path &srcPath);
			static boost::filesystem::path getFavoritesPath();
			static ALLIVAULTCOREP_API bool extractDate(const std::string& s, std::chrono::time_point<std::chrono::system_clock> &tp);
			static ALLIVAULTCOREP_API bool extractDateLong(const std::string& s, std::chrono::time_point<std::chrono::system_clock> &tp);
			static ALLIVAULTCOREP_API void setExecutionState();
			static ALLIVAULTCOREP_API void resetExecutionState();
			static ALLIVAULTCOREP_API void safe_create_directory(const boost::filesystem::path &dir);
			static void resetFolders();
			static ALLIVAULTCOREP_API std::string build_uri(const std::string &repo, const std::string &host);
			static std::string build_uri(const std::string &uname, ALLIVaultCore::ALLIRepoTypeP type, const std::string &groupName = "");
			static void updateSyncNewMachineSharingGroupsFlag(bool status);
			static boost::filesystem::path validateRootFolderForSharingWorkDirs();
			static void updateFilesPermissions(const boost::filesystem::path &dir);
			static bool isTempExcelFile(const boost::filesystem::path &filePath);
			static std::string getEncryptTempPath(const std::string &filePath);
			static bool readFileContentIntoUTF8String(const boost::filesystem::path &src, std::string &dest, int &size);
			static bool readFileContentIntoUTF8String(const boost::filesystem::path &src, std::string &dest);
			static std::string getALLIMailboxTempDBPath();
			static std::string generateAESKeyFileName(const std::string &fileName, const std::string &username);
			static std::unordered_set<std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> convertIdxTableUnorderedSet(const std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> &idxDictP);
			static std::string getALLITempPath(const std::string &subFolder);

		private:
			static std::string mysqlPassword;
			static boost::filesystem::path *appFolderPath;
			static int major, minor, platform;

			static int getShaForLargeFile(char **sha1, const char *src_file);
			static bool isNetworkFailure(bool &networkFailed);
			static boost::filesystem::path extractPrivateKeyForMySQL();
			static void updatePermissionsForFiles(const std::vector<std::shared_ptr<boost::filesystem::path>> &files);
			static void updatePermissionsForDirs(const std::vector<std::shared_ptr<boost::filesystem::path>> &dirs);
			static void safeUpdatePermissionsAsync(void *obj);
			static std::string buildRemoteGitFolderPath(const std::string &uname, ALLIVaultCore::ALLIRepoTypeP type, const std::string &groupName);
#ifdef ALLI_WIN32
			static ::FILETIME *convert_time_t_2_FILETIME(time_t src_time);
#endif
			static void addSharingFolderToFavorites();
		};
	}
}
