#pragma once
#include "ALLIEXTRepoP.h"

namespace ALLIVaultCore
{
	class ALLISharingCacheP;
	class ALLIEXTSharingRepoP :
		public ALLIEXTRepoP
	{
	public:
		ALLIEXTSharingRepoP();
		~ALLIEXTSharingRepoP();

		void setHostUserName(const std::string &huname);
		std::string getHostUserName() const;
		void setGroupName(const std::string &gname);
		std::string getGroupName() const;
		void setGuestListURL(const boost::filesystem::path &glu);
		void setGuestList(const std::unordered_set<std::string> &src);
		std::unordered_set<std::string> getGuestList() const;
		void load_guest_list_db();

	protected:
		static ALLIVaultCore::Helpers::alli_mutex *trackSharingMutex;
		std::string hostUserName;
		std::string groupName;
		// not init here
		ALLIVaultCore::ALLISharingCacheP *sharingCache;
		boost::filesystem::path *guestListURL;

		void downloadGroupMemberPublicKeys();
		void copyAESKeyForGroupMembers(const boost::filesystem::path &aesKeyPath, const boost::filesystem::path &filePath);

	private:
		std::string guestUserName;
		std::unordered_set<std::string> guestList;
		bool deletedFromGroup;

		void downloadGuestPublicKey(const std::string &guestUserName);
		bool publicKeyExists(const std::string &userName);
		bool encryptAESKey(const std::string &keyUser, const boost::filesystem::path &filePath);
		virtual bool encryptAESKeyImpl(const std::string &keyUser, const boost::filesystem::path &filePath);
		int load_guest_list_db_ex(const boost::filesystem::path &guestListDBURL);
		int gldb_query_callback(sqlite3_stmt *sqlstmt);
	};
}

