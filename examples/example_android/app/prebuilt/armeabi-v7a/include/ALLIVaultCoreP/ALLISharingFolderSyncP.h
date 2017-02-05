#pragma once
#include "ALLISharingFolderExtP.h"

namespace ALLIVaultCore
{
	class ALLISharingFolderSyncP :
		public ALLISharingFolderExtP
	{
	public:
		ALLISharingFolderSyncP();
		ALLISharingFolderSyncP(const ALLIVaultCore::ALLISharingFolderSyncP &src);
		~ALLISharingFolderSyncP();

		ALLIVAULTCOREP_API void setupSharingFolder(const std::string &hostUserName, const std::string &guestUserName, const std::string &groupName);
	};
}

