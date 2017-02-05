#pragma once
#include "alli_common.h"

// when using an enum class, declaration does not work
// one has to use #include directive
#include "ALLIFileStatusP.h"
#include "sqlite3.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>
#include <array>

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
		class ALLIFolderIndex;

		class IndexStore
		{
		public:
			ALLIVAULTCOREP_API IndexStore(const boost::filesystem::path &folderURL);
			ALLIVAULTCOREP_API ~IndexStore();

			ALLIVAULTCOREP_API bool init();
			ALLIVAULTCOREP_API bool load(std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> &table);
			ALLIVAULTCOREP_API bool deleteIndexes(std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> &table);
			ALLIVAULTCOREP_API bool updateIndexes(std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> &table);
			ALLIVAULTCOREP_API bool compact();

		private:
			static const std::string INDEX_TABLE;
			static const std::array<std::string, 4> DB_FILES;
			static const std::array<int, 4> DB_SIZES;

			boost::filesystem::path  const * dbRoot;
			ALLIVaultCore::Helpers::alli_mutex *lock;

			int readRowToRecord(sqlite3_stmt *sqlstmt, ALLIFolderIndex &item);
			int readDbToTable(const std::string &dbFileName, std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> &table);
			int writeTableToDb(const std::unordered_map<std::string, std::shared_ptr<ALLIVaultCore::Engine::ALLIFolderIndex>> &table, const std::string &dbFileName);
			int merge(const std::string &srcFileName, const std::string &dstFileName);
			int purgeDb(const std::string &dbFileName);
			int emptyDb(const std::string &dbFileName);
		};
	}
}