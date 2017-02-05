#pragma once
#include "ALLISharingFolderExtP.h"
#include "ALLINetworkStatus.h"

namespace ALLIVaultCore
{
	class ALLISharingFolderFromP :
		public ALLIVaultCore::ALLISharingFolderExtP
	{
	public:
		ALLIVaultCore::Engine::NetworkStatus(*chkHost)();

		ALLISharingFolderFromP(void);
		void downloadGroupMemberPublicKeys();

	private:
		void downloadHostPublicKey(const std::string &hostUserName);
	};
}
