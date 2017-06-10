#pragma once
#include "alli_hash.h"
#include <unordered_set>
#include <unordered_map>

namespace ALLIVaultCore
{
	enum class ALLIChangeStatusP;
	namespace Engine
	{
		class ALLIFolderIndex;
	}
	class ALLICacheP;
	class ALLISharingCacheP;
	class ALLIFolderCommitP
	{
	public:
		ALLIFolderCommitP();
		ALLIFolderCommitP(const ALLIFolderCommitP &src);
		ALLIFolderCommitP(ALLIFolderCommitP &&src);
		ALLIFolderCommitP &operator=(const ALLIFolderCommitP &src);
		ALLIFolderCommitP &operator=(ALLIFolderCommitP &&src);
		~ALLIFolderCommitP();

		void setEncryptRepoCommit(const std::string &commitSha1);
		void setPlainRepoCommit(const std::string &commitSha1);
		void setSourceRootURL(const boost::filesystem::path &src);
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *getCurrentIndexTable() const;
		void setPreIndexTable(const std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *src);
		void setCurrentIndexTable(const std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *src);
		void setIndexTableDiff(const std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *src);
		void processIdxTableDiff(const std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> &idxTablesDiff);
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> compareTwoCommits();
		std::unordered_map<std::string, ALLIVaultCore::ALLIChangeStatusP> createChangeSet();

	private:
		friend class ALLIVaultCore::ALLICacheP;
		friend class ALLIVaultCore::ALLISharingCacheP;
		std::string m_encryptRepoCommit;
		std::string m_plainRepoCommit;
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *m_idxTable_cur_commit;
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *m_idxTable_pre_commit;
		std::unordered_set<ALLIVaultCore::Engine::ALLIFolderIndex> *m_idxTablesDiff;
		boost::filesystem::path *m_srcRootURL;

		void compareTwoCommitsEx(void *payload);
		friend bool operator==(ALLIVaultCore::ALLIFolderCommitP const &lhs, ALLIVaultCore::ALLIFolderCommitP const &rhs);
	};
	bool operator==(ALLIVaultCore::ALLIFolderCommitP const &lhs, ALLIVaultCore::ALLIFolderCommitP const &rhs);
}

