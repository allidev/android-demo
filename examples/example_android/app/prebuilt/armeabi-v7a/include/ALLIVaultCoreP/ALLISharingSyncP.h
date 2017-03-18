#pragma once
#include "ALLISharingExtP.h"

namespace ALLIVaultCore
{ 
	class ALLISharingSyncP :
		public ALLIVaultCore::ALLISharingExtP
	{
	public:
		ALLISharingSyncP();
		ALLIVAULTCOREP_API ALLISharingSyncP(const ALLIVaultCore::ALLISharingSyncP &src);
		virtual ALLIVAULTCOREP_API ~ALLISharingSyncP();

		ALLIVAULTCOREP_API void setupSharingRepo(std::string &hostUserName, std::string &guestUserName, std::string &groupName);
		ALLIVAULTCOREP_API void setSharingGuestUserName(std::string &hostUserName, std::string &groupName);
	};
}

