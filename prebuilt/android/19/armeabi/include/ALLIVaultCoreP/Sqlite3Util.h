#pragma once
#include "alli_common.h"

#include "ALLIFolderIndex.h"
#include "sqlite3.h"

#include <unordered_map>
#include <string>

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIFolderIndex;
		namespace Sqlite3Util
		{
			ALLIVAULTCOREP_API void close_sqlite3_db(sqlite3 *db);
			ALLIVAULTCOREP_API int prepareDBTrans(const boost::filesystem::path &dbURL, std::string sqlstmt, sqlite3 **ppDb, sqlite3_stmt **ppStmt);
			ALLIVAULTCOREP_API int completeDBTrans(sqlite3 *pDb, sqlite3_stmt *pStmt);

			static int runSqliteDBTrans(const boost::filesystem::path &dbURL, 
				std::string tableName, 
				std::string sqlstmt, 
				int (*binding_callback) (sqlite3_stmt *, ALLIVaultCore::Engine::ALLIFolderIndex &),
				std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> &table);
		}
	}
}