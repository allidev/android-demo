#pragma once
#include "ALLIEXTFolderP.h"
#include <unordered_set>

namespace ALLIVaultCore
{
	class ALLISharingFolderP :
		public ALLIEXTFolderP
	{
	public:
		ALLIVaultCore::Engine::SimpleFolder *sharingFolder;
		std::string hostUserName;
		std::string guestUserName;
		std::string groupName;
		std::unordered_set<std::string> guestList;
		std::string remoteSharingFolderURL;

		ALLISharingFolderP();
		ALLISharingFolderP(const ALLIVaultCore::ALLISharingFolderP &src);
		~ALLISharingFolderP();

	protected:
		bool publicKeyExists(const std::string &userName);
	};
}

