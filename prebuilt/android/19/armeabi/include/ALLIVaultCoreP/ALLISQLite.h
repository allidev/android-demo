#pragma once

#include "alli_common.h"

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class ALLISQLite
		{
		public:
			ALLISQLite();
			~ALLISQLite();

			static ALLIVAULTCOREP_API std::string getMysqlPassword();
			/**
			** return true if db is created successfully, false if the op failed.
			** On failure, the db file will be automatically deleted.
			**/
			static ALLIVAULTCOREP_API bool createSqliteDB(const boost::filesystem::path &dbURL, const std::string &tableName, const std::string &colDef);
			static ALLIVAULTCOREP_API void close_sqlite3_db(sqlite3 *db);
			static int querySqliteDB(const boost::filesystem::path &dbURL,
				const std::string &tableName,
				const std::string &sqlstmt,
				const std::string *pragma,
				std::vector<void *> *params,
				int(*binding_callback) (sqlite3_stmt *, std::vector<void *> *params),
				int(*sqlite_query_cb) (sqlite3_stmt *));

		private:
			static std::string mysqlPassword;

			static int open_sqlite3_db(const boost::filesystem::path &dbURL, sqlite3 **db);
			static int drop_table(sqlite3 *db, const std::string &tableName);
			static int create_sqlite3_table(sqlite3 *db, const std::string &tableName, const std::string &colDef);
			static int robust_sqlite3_prepare_v2(sqlite3 *db, const std::string &stmt, int len, sqlite3_stmt **sqlstmt);
			static int robust_sqlite3_step(sqlite3_stmt *sqlstmt);
			static int robust_sqlite3_open(const char *db_cstr, sqlite3 **db);
			static int robust_sqlite3_key(sqlite3 *db);
			static int querySqliteDBEx(const boost::filesystem::path &dbURL,
				const std::string &tableName,
				const std::string &sqlstmt,
				const std::string *pragma,
				std::vector<void *> *params,
				int(*binding_callback) (sqlite3_stmt *, std::vector<void *> *params),
				int(*sqlite_query_cb) (sqlite3_stmt *));
		};
	}
}

