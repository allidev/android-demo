#pragma once
#include "ALLISharingFolderToP.h"
namespace ALLIVaultCore
{
	class ALLISTPlainFolderP :
		public ALLISharingFolderToP
	{
	public:
		ALLIVaultCore::Engine::SimpleFolder *sharingPlainFolder;
		boost::filesystem::path sharingPlainFolderURL;

		ALLIVAULTCOREP_API ALLISTPlainFolderP();
		ALLIVAULTCOREP_API ~ALLISTPlainFolderP();

		ALLIVAULTCOREP_API bool createRemoteSharingEncryptedFolder(const std::string &hostUserName, const std::string &guestUserName, const std::string &groupName);
		bool updateRemoteSharingEncryptedFolder(const std::string &groupName, const std::string &guestUserName);
		ALLIVAULTCOREP_API bool createSharingPlainFolderAtURL(const boost::filesystem::path &sharingPlainFolderURL);
	};
}

