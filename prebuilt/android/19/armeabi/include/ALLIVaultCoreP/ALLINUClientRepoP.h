#pragma once
#include "ALLINURepoP_external.h"

namespace boost
{
	namespace filesystem
	{
		class path;
	}
}

namespace ALLIVaultCore
{
	class ALLINUClientRepoP :
		public ALLINURepoP_external
	{
	public:
		ALLIVAULTCOREP_API ALLINUClientRepoP();
		ALLIVAULTCOREP_API ALLINUClientRepoP(const ALLIVaultCore::ALLINUClientRepoP &src);
		ALLIVAULTCOREP_API ~ALLINUClientRepoP();
		ALLIVAULTCOREP_API bool createRemoteRepo(std::string userName);
		ALLIVAULTCOREP_API bool createClientRepository(const boost::filesystem::path &localURL);
		ALLIVAULTCOREP_API bool setWorkingDirectory(const boost::filesystem::path &workdir);
		ALLIVAULTCOREP_API ALLIVaultCore::Engine::SimpleRepositoryP *getClientRepo();
		ALLIVAULTCOREP_API boost::filesystem::path getClientURL();

	private:
		ALLIVaultCore::Engine::SimpleRepositoryP *clientRepo;
		boost::filesystem::path *clientURL;
		std::string *remoteRepoURL;

		// convenience method
		std::string workingDirectory();
	};
}

