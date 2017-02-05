#pragma once
#include "ALLISharingToP.h"

namespace ALLIVaultCore
{
	class ALLISTPlainRepoP :
		public ALLISharingToP
	{
	public:
		ALLIVaultCore::Engine::SimpleRepositoryP *plainRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *clientRepo;
		boost::filesystem::path plainURL;

		ALLIVAULTCOREP_API ALLISTPlainRepoP();
		ALLIVAULTCOREP_API ~ALLISTPlainRepoP();

		ALLIVAULTCOREP_API bool createSharingPlainRepository(const boost::filesystem::path &plainURL);
		ALLIVAULTCOREP_API bool openExistingSharingPlainRepository(const boost::filesystem::path &plainURL);
		ALLIVAULTCOREP_API bool createSharingPlainWorkDir(const std::string &groupName);
		void addGuestUserNameToPlainGuestListDB(const std::string &groupName, const std::string &guestUserName);
		ALLIVAULTCOREP_API void monitorSharingPlainRepo(const std::string &guestUserName);
	};
}

