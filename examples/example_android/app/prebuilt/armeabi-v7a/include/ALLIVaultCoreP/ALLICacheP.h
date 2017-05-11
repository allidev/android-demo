#pragma once
#include <stack>
#include <unordered_map>
#include <unordered_set>

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
		class ALLIFolderIndex;
	}
	enum class ALLIChangeStatusP;
	class ALLIFolderCommitP;
	class ALLIEXTRepoP;
	class ALLIEXTFolderP;
	class ALLICacheP
	{
	public:
		ALLICacheP();
		ALLICacheP(ALLIVaultCore::ALLIEXTFolderP &aFolder, ALLIVaultCore::ALLIEXTRepoP &aPlainRepo, ALLIVaultCore::ALLIEXTRepoP &anEncryptRepo);
		~ALLICacheP();

		size_t getCacheCount() const;
		ALLIVaultCore::ALLIFolderCommitP &peek();
		void push(ALLIVaultCore::ALLIFolderCommitP &&aCommit);
		void push(const ALLIVaultCore::ALLIFolderCommitP &aCommit);
		std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> diff_IdxTables(ALLIVaultCore::ALLIFolderCommitP &curCache);
		bool insertCacheToDB(const ALLIVaultCore::ALLIFolderCommitP &curCache);
		bool insertCacheToDB(ALLIVaultCore::ALLIFolderCommitP &&curCache);
		void initializeDB(ALLIVaultCore::ALLIEXTRepoP *repo);

	private:
		std::stack<ALLIVaultCore::ALLIFolderCommitP> *m_commitCache;
		// weak pointer, no need to release resources.
		ALLIVaultCore::ALLIFolderCommitP *m_tmpCache, *m_lastCache;
		ALLIVaultCore::ALLIEXTFolderP *m_plainFolder;
		ALLIVaultCore::ALLIEXTRepoP *m_plainRepo, *m_encryptRepo;
		boost::filesystem::path *m_cacheDBURL;

		void loadDB();
		void createDBCacheList();
		void createDBFileIndices();
		bool loadCacheListDB();
		virtual bool loadCacheListDBImpl();
		boost::filesystem::path getDBURL();
		virtual boost::filesystem::path getDBURLImpl();
		int load_cacheList_query_callback(sqlite3_stmt *sqlstmt);
		virtual int load_cacheList_query_callbackImpl(sqlite3_stmt *sqlstmt);
		void createFirstCache();
		virtual void createFirstCacheImpl();
		bool loadFileIndicesDB(int cID, ALLIVaultCore::ALLIFolderCommitP &aCache);
		bool loadIdxTableEx(int cID, ALLIVaultCore::ALLIFolderCommitP &aCache, int indexType);
		int load_idxTable_query_callback(sqlite3_stmt *sqlstmt);
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> getIdxTableDiff(ALLIVaultCore::ALLIFolderCommitP &curCache, std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> &changeSet);
		bool insertCacheListToDB(const ALLIVaultCore::ALLIFolderCommitP &curCache);
		virtual bool insertCacheListToDBImpl(const ALLIVaultCore::ALLIFolderCommitP &curCache);
		bool insertFileIndicesToDB(const ALLIVaultCore::ALLIFolderCommitP &curCache);
	};
}

