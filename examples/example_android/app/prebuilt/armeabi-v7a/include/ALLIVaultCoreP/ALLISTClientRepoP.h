#pragma once
#include "ALLISharingToP.h"
namespace ALLIVaultCore
{
	class ALLISTClientRepoP :
		public ALLISharingToP
	{
	public:
		ALLIVAULTCOREP_API ALLISTClientRepoP(ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLIVAULTCOREP_API ~ALLISTClientRepoP();

		bool createRemoteSharingClientRepo(const std::string &groupName);
		bool updateRemoteSharingClientRepo(const std::string &groupName, const std::string &guestUserName);
		bool createSharingClientRepository(const boost::filesystem::path &sharingURL);
		bool openExistingSharingClientRepository(const boost::filesystem::path &sharingClientURL);
		bool createSharingClientWorkDir(const std::string &groupName);
		void addGuestUserToClientGuestListDB(const std::string &groupName, const std::string &guestUserName);
		void monitorSharingClientRepo();
	};
}

