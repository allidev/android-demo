#pragma once
#include "alli_common.h"

namespace boost
{
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
	namespace Engine
	{
		class SimpleRepositoryP;
	}

	class ALLIRepoP
	{
	public:
		ALLIRepoP();
		ALLIRepoP(const ALLIVaultCore::ALLIRepoP &src);
		ALLIRepoP &operator=(ALLIVaultCore::ALLIRepoP const &src) = delete;
		ALLIRepoP(ALLIVaultCore::ALLIRepoP &&src) = delete;
		ALLIRepoP &operator=(ALLIVaultCore::ALLIRepoP &&src) = delete;
		virtual ~ALLIRepoP();
		ALLIVAULTCOREP_API void setRepo(ALLIVaultCore::Engine::SimpleRepositoryP &repo);
		ALLIVAULTCOREP_API boost::filesystem::path getWorkDirPath();
		ALLIVAULTCOREP_API void setUserName(const std::string &uname);
		ALLIVAULTCOREP_API std::string getUserName() const;

	protected:
		ALLIVaultCore::Engine::SimpleRepositoryP *repoP;
		std::string *userName;

		bool createIdentityFile(const std::string &username);
		virtual ALLIVAULTCOREP_API void setRepoEx(ALLIVaultCore::Engine::SimpleRepositoryP &repo);
		bool commitStagedFilesLocallyWithMessage(const std::vector<std::string> &messages);
		std::string buildCommitMessage(const std::vector<std::string> &messages);
		std::vector<std::shared_ptr<libgit2cpp::commit>> createParentsVector(libgit2cpp::repository &repo);
	};
}

