#pragma once
#include "alli_common.h"
#include "ALLINetworkStatus.h"
#include <unordered_map>

namespace sql
{
	class SQLString;
	class Driver;
	class Connection;
	class ResultSet;
	class SQLException;
}

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLISSHTunnelP;
	}
	namespace Helpers
	{
		class ALLIUserAccount;
		class ALLIGroupP;
		class ALLIMailMessage;
		class ALLIMySQL
		{
		public:
			ALLIVAULTCOREP_API explicit ALLIMySQL(ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
			ALLIVAULTCOREP_API ~ALLIMySQL();

			ALLIVAULTCOREP_API bool createUserAccount(const ALLIVaultCore::Helpers::ALLIUserAccount &uacct);
			ALLIVAULTCOREP_API int userNameOrEmailAddressExists(const std::string &username, const std::string &email);
			ALLIVAULTCOREP_API bool downloadContactPublicKey(const std::string &contactUserName, std::string &contactFullName, bool &dbTimeout);
			ALLIVAULTCOREP_API bool isAccountActive(const std::string &username, const std::chrono::time_point<std::chrono::system_clock> &today, unsigned long long totalBytes, bool &dbTimeout, bool &maxTries);
			ALLIVAULTCOREP_API bool retrieveAccountInfo(const std::string &username, unsigned long long &qsize, std::chrono::time_point<std::chrono::system_clock> &expdate, bool &dbTimeout);
			ALLIVAULTCOREP_API bool retrieveAccountInfoRegCode(const std::string &username, std::string &rcode, bool &dbTimeout);
			ALLIVAULTCOREP_API bool userNameExists(const std::string &username, std::string &fullname, bool &timedOut);
			ALLIVAULTCOREP_API bool validateRegistrationCode(const std::string &regcode, bool &timedOut);
			ALLIVAULTCOREP_API bool activateRegistrationCode(const std::string &regcode, const std::string &uname);
			ALLIVAULTCOREP_API bool checkGroupInvites(const std::string &guestUserName, std::vector<ALLIGroupP> &groupInvites, int &error_code);
			ALLIVAULTCOREP_API bool markAnInviteAsAccepted(const std::string &guestUserName, const ALLIVaultCore::Helpers::ALLIGroupP &src);
			ALLIVAULTCOREP_API bool addGroupMember(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			ALLIVAULTCOREP_API bool isUserGroupMember(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			ALLIVAULTCOREP_API bool setGuestAcceptance(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			ALLIVAULTCOREP_API bool deleteGroupMember(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			ALLIVAULTCOREP_API bool deleteAllGroupMembers(const std::string &hostUserName, const std::string &groupName);
			ALLIVAULTCOREP_API bool updateRemoteSharingRepo(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			ALLIVAULTCOREP_API bool insertAMessageToMailroomDB(const ALLIVaultCore::Helpers::ALLIMailMessage &mailMsg);
			ALLIVAULTCOREP_API bool updateAMessageToMailroomDB(const ALLIVaultCore::Helpers::ALLIMailMessage &mailMsg);
			ALLIVAULTCOREP_API bool checkMailboxStatus(const std::string &recipient, std::unordered_map<std::string, ALLIVaultCore::Helpers::ALLIMailMessage> &newMails, bool &dbTimeout);
			ALLIVAULTCOREP_API bool getMailboxLock(const std::string &username, const std::string &curUser, bool &dbTimedout);
			ALLIVAULTCOREP_API bool isMailboxDeadlock(const std::string &username, const std::string &curUser, std::chrono::time_point<std::chrono::system_clock> (*fn_ptr)(std::chrono::time_point<std::chrono::system_clock> &src), bool &dbTimedout);
			ALLIVAULTCOREP_API bool updateMailboxHeartBeat(const std::string &username, int hb_counter, const std::string &curUser, bool &dbTimedout);
			ALLIVAULTCOREP_API bool releaseMailboxLock(const std::string &username, bool &dbTimedout);
			ALLIVAULTCOREP_API bool isMaillistUpToDate(const std::string &username, bool(*fn_ptr)(const std::string &uname, std::chrono::time_point<std::chrono::system_clock> &sdate), bool &dbTimedout);
			ALLIVAULTCOREP_API bool userPasswordMatch(const std::string &username, const std::string &passwd, bool &dbTimeout);

		private:
			std::string connStr;
			static sql::SQLString *hostName, *userName, *passwd, *dbName;
			ALLIVaultCore::Engine::ALLISSHTunnelP *tunnel;
			sql::Driver *driver;
			sql::Connection *con;

			void initMySQLConnection();
			void closeMySQLConnection();
			void prepareMySQL();
			void cleanupMySQL();
			int userNameOrEmailAddressExists_parseResultSet(sql::ResultSet &res, const std::string &username);
			void downloadContactPublicKey_parseResultSet(sql::ResultSet &res, const std::string &contactUserName, std::string &contactFullName);
			bool isAccountActive_parseResultSet(sql::ResultSet &res, const std::chrono::time_point<std::chrono::system_clock> &today, unsigned long long totalBytes);
			bool retrieveAccountInfo_parseResultSet(sql::ResultSet &res, unsigned long long &qsize, std::chrono::time_point<std::chrono::system_clock> &expdate);
			bool retrieveAccountInfoRegCode_parseResultSet(sql::ResultSet &res, std::string &rcode);
			bool userNameExists_parseResultSet(sql::ResultSet &res, std::string &fullname);
			bool checkGroupInvites_parseResultSet(sql::ResultSet &res, std::vector<ALLIGroupP> &groupInvites);
			bool checkMailboxStatus_parseResultSet(sql::ResultSet &res, std::unordered_map<std::string, ALLIVaultCore::Helpers::ALLIMailMessage> &newMails);
			bool getMailboxLock_parseResultSet(sql::ResultSet &res, const std::string &username, const std::string &curUser);
			bool isMailboxDeadlock_parseResultSet(sql::ResultSet &res, const std::string &username, const std::string &curUser, std::chrono::time_point<std::chrono::system_clock> (*fn_ptr)(std::chrono::time_point<std::chrono::system_clock> &src));
			bool updateMailboxHeartBeat_parseResultSet(sql::ResultSet &res, const std::string &username, int hb_counter, const std::string &curUser);
			bool releaseMailboxLock_parseResultSet(sql::ResultSet &res, const std::string &username);
			bool isMaillistUpToDate_parseResultSet(sql::ResultSet &res, bool(*fn_ptr)(const std::string &uname, std::chrono::time_point<std::chrono::system_clock> &sdate));
			void constructTimeTarget(const std::string &src, std::chrono::time_point<std::chrono::system_clock> (*fn_ptr)(std::chrono::time_point<std::chrono::system_clock> &src), std::chrono::time_point<std::chrono::system_clock> &sdate_close, std::chrono::time_point<std::chrono::system_clock> &sdate_new);
			bool getMailboxLock_set_lock(const std::string &username, const std::string &curUser);
			bool updateMailboxHeartBeat_set_hb_counter(const std::string &username, int hb_counter, const std::string &curUser);
			bool releaseMailboxLock_release_lock(const std::string &username);
			void checkMailboxStatus_loadMessage(sql::ResultSet &res, ALLIVaultCore::Helpers::ALLIMailMessage &mail);
			void downloadContactPublicKey_saveToFile(const char *rawdata, const std::string &contactUserName);
			int userNameOrEmailAddressExists_transact(const std::string &username, const std::string &email);
			bool downloadContactPublicKey_transact(const std::string &contactUserName, std::string &contactFullName, bool &dbTimeout);
			bool isAccountActive_transact(const std::string &username, const std::chrono::time_point<std::chrono::system_clock> &today, unsigned long long totalBytes, bool &maxTries);
			bool retrieveAccountInfo_transact(const std::string &username, unsigned long long &qsize, std::chrono::time_point<std::chrono::system_clock> &expdate);
			bool retrieveAccountInfoRegCode_transact(const std::string &username, std::string &rcode);
			bool userNameExists_transact(const std::string &username, std::string &fullname);
			bool validateRegistrationCode_transact(const std::string &regcode);
			bool activateRegistrationCode_transact(const std::string &regcode, const std::string &uname);
			bool checkGroupInvites_transact(const std::string &guestUserName, std::vector<ALLIVaultCore::Helpers::ALLIGroupP> &groupInvites);
			bool markAnInviteAsAccepted_transact(const std::string &guestUserName, const ALLIVaultCore::Helpers::ALLIGroupP &src);
			bool addGroupMember_transact(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			bool isUserGroupMember_transact(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			bool setGuestAcceptance_transact(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			bool deleteGroupMember_transact(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			bool deleteAllGroupMembers_transact(const std::string &hostUserName, const std::string &groupName);
			bool updateRemoteSharingRepo_transact(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			bool insertAMessageToMailroomDB_transact(const ALLIVaultCore::Helpers::ALLIMailMessage &mailMsg);
			bool updateAMessageToMailroomDB_transact(const ALLIVaultCore::Helpers::ALLIMailMessage &mailMsg);
			bool checkMailboxStatus_transact(const std::string &recipient, std::unordered_map<std::string, ALLIVaultCore::Helpers::ALLIMailMessage> &newMails);
			bool getMailboxLock_transact(const std::string &username, const std::string &curUser);
			bool isMailboxDeadlock_transact(const std::string &username, const std::string &curUser, std::chrono::time_point<std::chrono::system_clock> (*fn_ptr)(std::chrono::time_point<std::chrono::system_clock> &src));
			bool updateMailboxHeartBeat_transact(const std::string &username, int hb_counter, const std::string &curUser);
			bool releaseMailboxLock_transact(const std::string &username);
			bool isMaillistUpToDate_transact(const std::string &username, bool(*fn_ptr)(const std::string &uname, std::chrono::time_point<std::chrono::system_clock> &sdate));
			bool userPasswordMatch_transact(const std::string &username, const std::string &passwd);
			bool isMailboxDeadlock_fix_deadlock(const std::string &username);
			bool createUserAccount_readPublicKey(const boost::filesystem::path &pubkey, std::string &dest, int &size);
			int createUserAccount_transact(const ALLIVaultCore::Helpers::ALLIUserAccount &uacct, const std::string &rawdata, int size);
			int exceptionHandler(const sql::SQLException &e);
		};
	}
}

