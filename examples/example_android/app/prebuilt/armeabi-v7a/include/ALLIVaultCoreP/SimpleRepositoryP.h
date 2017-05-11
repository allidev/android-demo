#pragma once
#include "alli_common.h"
#include "alli_event.h"
#include "ALLINetworkStatus.h"
#include "../libgit2cpp/repository.h"
#include "git2/types.h"
#include <unordered_map>
#include <queue>

namespace boost
{
	namespace signals2
	{
		class connection;
	}
	namespace filesystem
	{
		class path;
	}
}

namespace libgit2cpp
{
	class tree;
}

namespace ALLIVaultCore
{
	namespace Helpers
	{
		class alli_mutex;
	}
	namespace Engine
	{
		class ALLICloneOptions;
		class ALLIFetch;
		class ALLILock;
		class IndexDBFileEntry;
		class SimpleRepositoryP :
			public libgit2cpp::repository
		{
		public:
			static ALLIVAULTCOREP_API ALLIVaultCore::Helpers::alli_mutex *stageMutex;
			typedef ALLIVaultCore::Helpers::alli_event::slot_type RepoFatalErrorSlotType;
			typedef ALLIVaultCore::Helpers::alli_event::slot_type HeartBeatSlotType;
			ALLIVaultCore::Engine::NetworkStatus(*chkHost)();
			void(*missing_private_key_fn_ptr)();

			ALLIVAULTCOREP_API SimpleRepositoryP(const boost::filesystem::path &src_path);
			ALLIVAULTCOREP_API SimpleRepositoryP(const ALLIVaultCore::Engine::SimpleRepositoryP &src);
			SimpleRepositoryP &operator=(ALLIVaultCore::Engine::SimpleRepositoryP const &src) = delete;
			SimpleRepositoryP(ALLIVaultCore::Engine::SimpleRepositoryP &&src) = delete;
			SimpleRepositoryP &operator=(ALLIVaultCore::Engine::SimpleRepositoryP &&src) = delete;
			ALLIVAULTCOREP_API ~SimpleRepositoryP(void);

			ALLIVAULTCOREP_API bool fetchFromServer();
			ALLIVAULTCOREP_API bool mergeFastForward(bool isFinishUploading, bool finishDownloading = false);
			ALLIVAULTCOREP_API bool mergeFastForwardMB(bool finishDownloading = false);
			/**
			** Track a repo for any changes.
			** The set of changed files will be returned.
			** NULL will be returned if there is an error.
			**/
			ALLIVAULTCOREP_API std::unordered_map<std::string, git_status_t> *trackWorkingDirectoryChangesP();
			/**
			 * Check if the repo currently has any unstaged files. It is used as a guard prior to making
			 * a commit
			 *
			 * @return true if there are unstaged files and false otherwise
			 */
			ALLIVAULTCOREP_API bool hasUnstagedFiles();
			ALLIVAULTCOREP_API bool isWorkingDirectoryClean();
			ALLIVAULTCOREP_API int cleanupWorkingDirectory();
			ALLIVAULTCOREP_API SimpleRepositoryP *setWorkingDirectory(boost::filesystem::path *workdir);
			static ALLIVAULTCOREP_API ALLIVaultCore::Engine::SimpleRepositoryP *cloneWithOptions(const std::string &originURL, const boost::filesystem::path &workdirURL, const ALLIVaultCore::Engine::ALLICloneOptions &gtOpts, ALLIVaultCore::Engine::NetworkStatus (*chkHost)());
			static ALLIVAULTCOREP_API ALLIVaultCore::Engine::SimpleRepositoryP *initWithRespository(boost::filesystem::path &src_path, boost::filesystem::path *localFileURL, bool checkRemoteRef);
			ALLIVAULTCOREP_API void buildIndexDBHistory(const std::string *headCommitSHA1 = nullptr);
			ALLIVAULTCOREP_API std::vector<ALLIVaultCore::Engine::IndexDBFileEntry> *getHeadFromIndexDBHistory();
			ALLIVAULTCOREP_API boost::filesystem::path get_repo_path() const;
			ALLIVAULTCOREP_API boost::filesystem::path get_workdir_path() const;
			ALLIVAULTCOREP_API void resetIndexDBFileHistory();
			ALLIVAULTCOREP_API boost::signals2::connection connectFatalError(const RepoFatalErrorSlotType &slot);
			ALLIVAULTCOREP_API boost::signals2::connection connectHeartBeat(const HeartBeatSlotType &slot);

		private:
			boost::filesystem::path *repo_path;
			boost::filesystem::path *workdir_path;
			std::unordered_map<std::string, git_status_t> *repoFilesP;
			ALLIVaultCore::Engine::ALLIFetch *fetch;
			ALLIVaultCore::Engine::ALLILock *aLock;
			// contains a vector of tree entries pointing to
			// all the index files from a single commit
			std::vector<ALLIVaultCore::Engine::IndexDBFileEntry> curIndexDBFEntry;
			// contains a list of commits that comprise the history
			// all indices
			std::queue<std::vector<ALLIVaultCore::Engine::IndexDBFileEntry>> idxDBFHist;
			ALLIVaultCore::Helpers::alli_event RepoFatalError;
			ALLIVaultCore::Helpers::alli_event HeartBeat;
			friend int copyConfigurationFn(const boost::filesystem::path &src_path, const boost::filesystem::path &dest_path, SimpleRepositoryP *destRepo);
			friend int copyObjDatabaseFn(const boost::filesystem::path &src_path, const boost::filesystem::path &dest_path, SimpleRepositoryP *dest);

			std::vector<std::shared_ptr<git_oid>> getObjectIdsFromObjectDatabase(const boost::filesystem::path &repoSrc);
			std::unordered_map<std::string, git_status_t> *trackWDChanges_libgit2_fnP();
			std::unique_ptr<boost::filesystem::path> get_workdir(const boost::filesystem::path &rpath);
			void index_unstage(const std::string &fname);
			void delete_a_file(const std::string &fname);
			void walk_thru_tree_entries(libgit2cpp::tree &curTree, ALLIVaultCore::Engine::IndexDBFileEntry &srcIdxFEntry);
			void buildIndexDBHistoryEx(const std::string *headCommitSHA1 = nullptr);
			bool copyConfiguration(const git_config *src, git_config *dest);
			bool copyObjectDatabase(const boost::filesystem::path &repoSrc, const boost::filesystem::path &repoDest);
		};
		int copyConfigurationFn(const boost::filesystem::path &src_path, const boost::filesystem::path &dest_path, ALLIVaultCore::Engine::SimpleRepositoryP *destRepo);
		int copyObjDatabaseFn(const boost::filesystem::path &src_path, const boost::filesystem::path &dest_path, ALLIVaultCore::Engine::SimpleRepositoryP *dest);
	}
}
