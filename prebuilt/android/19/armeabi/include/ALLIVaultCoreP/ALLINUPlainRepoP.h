#pragma once
#include "ALLINURepoP.h"

namespace ALLIVaultCore
{
	class ALLINUPlainRepoP :
		public ALLINURepoP
	{
	public:
		ALLIVAULTCOREP_API ALLINUPlainRepoP();
		ALLIVAULTCOREP_API ALLINUPlainRepoP(const ALLIVaultCore::ALLINUPlainRepoP &src);
		ALLIVAULTCOREP_API ~ALLINUPlainRepoP();

		ALLIVAULTCOREP_API bool createPlainFolder();
		ALLIVAULTCOREP_API bool createPlainRepository(const boost::filesystem::path &plainURL);
		ALLIVAULTCOREP_API void setClientRepo(ALLIVaultCore::Engine::SimpleRepositoryP *clientRepo);
		ALLIVAULTCOREP_API boost::filesystem::path getPlainURL();

	protected:
		bool createPlainFolderEx(const std::string &repoType);

	private:
		ALLIVaultCore::Engine::SimpleRepositoryP *clientRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *plainRepo;
		boost::filesystem::path *plainURL;

		virtual bool createPlainFolderImpl();
	};
}

