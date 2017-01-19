#pragma once
#include "ALLISharingExtP.h"

namespace ALLIVaultCore
{ 
	class ALLISharingSyncP :
		public ALLIVaultCore::ALLISharingExtP
	{
	public:
		//std::string(*resourceManagerGetString) (const std::string &key);
		//void(*monitor_fn_ptr)(const boost::filesystem::path &sharingURL);

		ALLISharingSyncP();
		ALLIVAULTCOREP_API ALLISharingSyncP(const ALLIVaultCore::ALLISharingSyncP &src);
		ALLIVAULTCOREP_API ~ALLISharingSyncP();

		ALLIVAULTCOREP_API void setupSharingRepo(std::string &hostUserName, std::string &guestUserName, std::string &groupName);
		ALLIVAULTCOREP_API void setSharingGuestUserName(std::string &hostUserName, std::string &groupName);

	//private:
	//	void addSharingFolderToFavorites();
	};
}

