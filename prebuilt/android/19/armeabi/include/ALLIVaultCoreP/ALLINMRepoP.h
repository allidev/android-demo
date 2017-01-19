#pragma once
#include "ALLIRepoP.h"

#include <unordered_map>

#include "alli_common.h"
#include "ALLINetworkStatus.h"
#include "alli_event.h"

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
	class commit;
	class repository;
}

namespace ALLIVaultCore
{ 
	class ALLINMRepoP :
		public ALLIRepoP
	{
	public:
		void(*filePermPtr) (const boost::filesystem::path &);
		typedef ALLIVaultCore::Helpers::transfer_progress_event::slot_type transferSlotType;

		ALLINMRepoP();
		ALLINMRepoP(const ALLIVaultCore::ALLINMRepoP &src);
		~ALLINMRepoP();
		ALLIVAULTCOREP_API void openServerRepository(const std::string &remoteURL);
		ALLIVAULTCOREP_API std::unordered_map<std::string, git_status_t> *trackWorkingDirectoryChanges();
		ALLIVAULTCOREP_API bool cloneFromRemoteRepo(const boost::filesystem::path &localURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLIVAULTCOREP_API bool moveRepository(const boost::filesystem::path &localURL, bool checkRemoteRef);
		boost::signals2::connection connect(const transferSlotType &slot);

	protected:
		virtual bool cloneFromRemoteRepoEx(const boost::filesystem::path &localURL, ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		virtual bool moveRepositoryEx(const boost::filesystem::path &localURL, bool checkRemoteRef);
		void open_output_file(FILE **output, const boost::filesystem::path &dest);
		void validate_dest(const boost::filesystem::path &dest);
		void open_input_file(FILE **input, const boost::filesystem::path &src);
		FILE *open_private_key_file(char **priKeyPath, int _ShFlag);
		bool stageFileWithRelativePath(const std::string &fileName);
		bool stageRemovedFileToIndex(const std::string &fileName);
		std::string buildCommitMessage(const std::vector<std::string> &messages);
		std::vector<std::shared_ptr<libgit2cpp::commit>> createParentsVector(libgit2cpp::repository &repo);
		bool commitStagedFilesLocallyWithMessage(const std::vector<std::string> &messages);

	private:
		std::string *serverURL;
		ALLIVaultCore::Helpers::transfer_progress_event CloneTransferUpdate;

		bool createRepositoryOnNewMachine(const boost::filesystem::path &localURL, bool checkRemoteRef);
		void cloneTransferProgress(const git_transfer_progress *progress);
		void moveRepository_create_repo(const boost::filesystem::path &localURL, bool checkRemoteRef);
		void moveRepository_delete_old_git_dir(boost::filesystem::path &repo_path);
		void moveRepository_set_work_dir(boost::filesystem::path &workdir);
		void moveRepository_reset_repo();
	};
}
