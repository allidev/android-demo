#pragma once
#include "ALLISharingFolderP.h"
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	class ALLISharingFolderToP :
		public ALLISharingFolderP
	{
	public:
		boost::filesystem::path sharingFolderURL;
		std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host);
		ALLIVaultCore::Engine::NetworkStatus(*chkHost)();

		ALLISharingFolderToP();
		~ALLISharingFolderToP();

		ALLIVAULTCOREP_API void setupSharingFolder(const std::string &hostUserName, const std::string &guestUserName, const std::string &groupName);
		void downloadGuestPublicKey(const std::string &guestUserName);
		bool createRemoteSharingFolder(const std::string &hostUserName, const std::string &guestUserName, const std::string &groupName, const std::string &repoType);
		bool updateRemoteSharingFolder(const std::string &groupName, const std::string &guestUserName, const std::string &repoType);
		bool createSharingFolderAtURL(const boost::filesystem::path &sharingFolderURL);

	private:
		bool publicKeyExists(const std::string &userName);
	};
}

