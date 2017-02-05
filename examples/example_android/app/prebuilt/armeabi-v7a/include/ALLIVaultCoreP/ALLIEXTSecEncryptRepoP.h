#pragma once
#include "ALLIEXTRepoP.h"

namespace ALLIVaultCore
{ 
	class ALLIEXTSecEncryptRepoP :
		public ALLIVaultCore::ALLIEXTRepoP
	{
	public:
		ALLIEXTSecEncryptRepoP();
		ALLIEXTSecEncryptRepoP(const ALLIEXTSecEncryptRepoP &src);
		~ALLIEXTSecEncryptRepoP();

		void openEncryptedRepository(const boost::filesystem::path &encryptedURL);
		void initializeDBForSyncFolder();
	};
}

