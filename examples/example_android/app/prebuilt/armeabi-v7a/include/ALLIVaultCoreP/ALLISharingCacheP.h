#pragma once
#include "ALLICacheP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSharingPlainFolderP;
	class ALLIEXTSharingPlainRepoP;
	class ALLIEXTSharingEncryptRepoP;
	class ALLISharingCacheP :
		public ALLICacheP
	{
	public:
		ALLISharingCacheP(ALLIVaultCore::ALLIEXTSharingPlainFolderP *aFolder, ALLIVaultCore::ALLIEXTSharingPlainRepoP *aPlainRepo, ALLIVaultCore::ALLIEXTSharingEncryptRepoP *anEncryptRepo);
		~ALLISharingCacheP();

		void initializeDB(const std::string &hostUserName, const std::string &groupName);

	private:
		std::string hostUserName;
		std::string groupName;
		ALLIVaultCore::ALLIEXTSharingPlainFolderP *shPlainFolder;
		ALLIVaultCore::ALLIEXTSharingPlainRepoP *shPlainRepo;
		ALLIVaultCore::ALLIEXTSharingEncryptRepoP *shEncryptRepo;

		void createSharingDBCacheList();
		void createSharingDBFileIndices();
		bool loadCacheListDBImpl() override;
		int load_cacheList_query_callbackImpl(sqlite3_stmt *sqlstmt) override;
		boost::filesystem::path getDBURLImpl() override;
		void createFirstCacheImpl() override;
		std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> diff_IdxTablesImpl(ALLIVaultCore::ALLIFolderCommitP &curCache) override;
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> getIdxTableDiffImpl(ALLIVaultCore::ALLIFolderCommitP &curCache, std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> &changeSet) override;
		bool insertCacheListToDBImpl(const ALLIVaultCore::ALLIFolderCommitP &curCache) override;
	};
}

