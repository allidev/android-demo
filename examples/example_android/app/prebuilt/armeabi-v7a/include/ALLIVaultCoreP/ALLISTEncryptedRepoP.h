#pragma once
#include "ALLISharingToP.h"

namespace ALLIVaultCore
{
	class ALLISTEncryptedRepoP :
		public ALLISharingToP
	{
	public:
		ALLIVaultCore::Engine::SimpleRepositoryP *encryptedRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *clientRepo;
		//System::Uri ^remoteEncryptedRepoURL;
		boost::filesystem::path encryptedURL;
		void(*sharing_key_folder_fn_ptr)();
		void(*root_git_ignore_file_fn_ptr)();

		ALLIVAULTCOREP_API ALLISTEncryptedRepoP(ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLIVAULTCOREP_API ~ALLISTEncryptedRepoP();

		ALLIVAULTCOREP_API bool createRemoteSharingEncryptedRepo(const std::string &groupName);
		ALLIVAULTCOREP_API bool updateRemoteSharingEncryptedRepo(const std::string &groupName, const std::string &guestUserName);
		ALLIVAULTCOREP_API bool createSharingEncryptedRepository(const boost::filesystem::path &sharingEncryptedURL);
		ALLIVAULTCOREP_API bool createSharingEncryptedWorkDir(const std::string &groupName);
		ALLIVAULTCOREP_API void monitorSharingEncryptedRepo(const std::string &groupName);
	};
}

