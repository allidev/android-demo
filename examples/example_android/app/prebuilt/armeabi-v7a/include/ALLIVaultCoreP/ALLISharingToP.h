#pragma once
#include "ALLISharingP.h"
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	class ALLISharingToP :
		public ALLISharingP
	{
	public:
		bool hasSharing;
		std::string(*uri_fn_ptr)(const std::string &repo, const std::string &host);
		//void(*fav_fn_ptr)();
		//bool(*update_db_fn_ptr)(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName, const std::string &connStr);

		ALLISharingToP(ALLIVaultCore::Engine::NetworkStatus(*chkHost)());
		ALLISharingToP();
		~ALLISharingToP();

		ALLIVAULTCOREP_API void setupSharingRepo(const std::string &hostUserName, const std::string &guestUserName, const std::string &groupName);
		bool createRemoteSharingRepo(const std::string &groupName, const std::string &guestUserName, const std::string &repoType);
		bool updateRemoteSharingRepo(const std::string &groupName, const std::string &guestUserName);
		bool createSharingRepository(const boost::filesystem::path &sharingURL);
		bool openExistingSharingRepository(const boost::filesystem::path &sharingURL);
		bool createSharingWorkDir(const std::string &groupName, const std::string &repoType);
		void createGuestListDB(const std::string &guestUserName);
		bool addGuestUserNameToGuestListDB(const std::string &guestUserName);

	private:
		ALLIVaultCore::Engine::NetworkStatus(*chkHost)();

		boost::filesystem::path constructWorkDirPath(const std::string &groupName, const std::string &repoType);
	};
}

