#pragma once
#include "ALLIFolderP.h"

struct sqlite3_stmt;

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIMonitorP;
	}
	class ALLIEXTFolderP :
		public ALLIFolderP
	{
	public:
		ALLIEXTFolderP();
		ALLIEXTFolderP(const ALLIVaultCore::ALLIEXTFolderP &src);
		~ALLIEXTFolderP();

		void load_index_db();
		/**
		 * Get the list of files that are contained in the root folder.
		 *
		 * @return an unordered_map object of string and ALLIFolderIndex
		 */
		ALLIVAULTCOREP_API std::unordered_map<std::string, ALLIVaultCore::Engine::ALLIFolderIndex> getFolderContentList();
		ALLIVAULTCOREP_API std::string getFolderContentListJson();
		bool addUserToFriendListDB(const std::string &uname, const std::string &fname);
		void updateTotalBytesUsed();
		ALLIVAULTCOREP_API bool downloadOneFileJson(const std::string &localPath);

	protected:
		bool switching;
		std::string serverRootFolder;
		ALLIVaultCore::Engine::ALLIMonitorP *monitor;
		unsigned long long totalBytesUsed;

		virtual void load_index_db_ex();
		bool setDataVersion(int ver);
		bool isDataVersionSet(int ver);
		int verctrl_query_callback(sqlite3_stmt *sqlstmt, int ver);
		int updateDataVersion(int ver);
		virtual void updateTotalBytesUsedImpl();
		bool restoreFileAttributes(const std::string & localPath, const boost::filesystem::path &destURL);

	private:
		bool hasFriendUserName;

		bool containsUserInFriendList(const std::string &uname);
		int friend_query_callback(sqlite3_stmt *sqlstmt);
		virtual bool downloadOneFileJsonImpl(const std::string &localPath);
	};
}

