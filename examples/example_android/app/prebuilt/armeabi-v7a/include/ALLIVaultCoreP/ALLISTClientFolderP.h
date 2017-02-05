#pragma once
#include "ALLISharingFolderToP.h"
namespace ALLIVaultCore
{
	class ALLISTClientFolderP :
		public ALLISharingFolderToP
	{
	public:
		ALLIVaultCore::Engine::SimpleFolder *sharingClientFolder;
		boost::filesystem::path sharingClientFolderURL;

		ALLIVAULTCOREP_API ALLISTClientFolderP();
		ALLIVAULTCOREP_API ~ALLISTClientFolderP();

		bool createRemoteSharingClientFolder(const std::string &hostUserName, const std::string &guestUserName, const std::string &groupName);
		bool updateRemoteSharingClientFolder(const std::string &groupName, const std::string &guestUserName);
		bool createSharingClientFolderAtURL(const boost::filesystem::path &sharingClientFolderURL);
	};
}

