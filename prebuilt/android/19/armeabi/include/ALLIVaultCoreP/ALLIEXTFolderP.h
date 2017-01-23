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
		bool addUserToFriendListDB(const std::string &uname, const std::string &fname);
		void updateTotalBytesUsed();

	protected:
		bool switching;
		std::string serverRootFolder;
		ALLIVaultCore::Engine::ALLIMonitorP *monitor;

		virtual void load_index_db_ex();
		bool setDataVersion(int ver);
		bool isDataVersionSet(int ver);
		int verctrl_query_callback(sqlite3_stmt *sqlstmt, int ver);
		int updateDataVersion(int ver);

	private:
		bool hasFriendUserName;
		unsigned long long totalBytesUsed;

		bool containsUserInFriendList(const std::string &uname);
		int friend_query_callback(sqlite3_stmt *sqlstmt);
		virtual void updateTotalBytesUsedImpl();
	};
}

