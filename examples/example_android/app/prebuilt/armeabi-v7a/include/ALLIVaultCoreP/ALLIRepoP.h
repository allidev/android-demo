#pragma once
#include "alli_common.h"

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
		class SimpleRepositoryP;
	}

	class ALLIRepoP
	{
	public:
		ALLIRepoP();
		ALLIRepoP(const ALLIVaultCore::ALLIRepoP &src);
		~ALLIRepoP();
		ALLIVAULTCOREP_API void setRepo(ALLIVaultCore::Engine::SimpleRepositoryP &repo);
		ALLIVAULTCOREP_API boost::filesystem::path getWorkDirPath();
		ALLIVAULTCOREP_API void setUserName(const std::string &uname);
		ALLIVAULTCOREP_API std::string getUserName() const;

	protected:
		ALLIVaultCore::Engine::SimpleRepositoryP *repoP;
		std::string *userName;

		bool createIdentityFile(const std::string &username);
		virtual ALLIVAULTCOREP_API void setRepoEx(ALLIVaultCore::Engine::SimpleRepositoryP &repo);
	};
}

