#pragma once
#include "ALLIRepoP.h"
#include <unordered_map>

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace libgit2cpp
{
	class repository;
	class commit;
}

namespace ALLIVaultCore
{
	namespace Engine
	{
		class ALLIMonitorP;
	}
	namespace Helpers
	{
		class alli_event_args;
	}
	class ALLIEXTRepoP :
		public ALLIRepoP
	{
	public:
		ALLIEXTRepoP();
		ALLIEXTRepoP(const ALLIVaultCore::ALLIEXTRepoP &src);
		~ALLIEXTRepoP();

		/**
		** Track working directory changes for an existing repo.
		** Return changed files in a dictionary. If the count of
		** of dictionary is zero, it means there are no changes.
		**/
		std::unordered_map<std::string, git_status_t> *trackWorkingDirectoryChanges();
		void set_hasInitialCommit(bool status);

	protected:
		bool commitStagedFilesLocallyWithMessageEx(std::vector<std::string> &messages);
		bool stageFileWithRelativePath(const std::string &fileName);
		bool stageRemovedFileToIndex(const std::string &fileName);
		bool deleteEmptyParentDirectory(const boost::filesystem::path &srcPath);
		void open_input_file(FILE **input, const boost::filesystem::path &src);
		void open_output_file(FILE **output, const boost::filesystem::path &dest);
		void validate_dest(const boost::filesystem::path &dest);
		FILE *open_private_key_file(char **priKeyPath, int _ShFlag);
		boost::filesystem::path generateAESKeyFileName(const boost::filesystem::path &fileName, std::string &username);
		void monitorRepositoryP(const boost::filesystem::path &repoURL);

	private:
		boost::filesystem::path *groupDBURL;
		bool hasInitialCommit;
		bool switching;
		ALLIVaultCore::Engine::ALLIMonitorP *monitor;

		bool getLockForChangedFile(const boost::filesystem::path &fileName, int *fd);
		bool releaseLockForChangedFile(int *fd);
		std::string buildCommitMessage(std::vector<std::string> &messages);
		std::vector<std::shared_ptr<libgit2cpp::commit>> createParentsVector(libgit2cpp::repository &repo);
		void attachToEventHandlerForRepoFatalError();
		void processRepoFatalError(void *sender, ALLIVaultCore::Helpers::alli_event_args &e);
	};
}

