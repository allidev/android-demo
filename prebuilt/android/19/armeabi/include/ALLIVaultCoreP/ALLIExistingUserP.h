#pragma once
#include "ALLIUserP.h"

namespace ALLIVaultCore
{
	class ALLIEXTSecEncryptRepoP;
	class ALLIEXTSecPlainRepoP;
	class ALLIEXTSecPlainFolderP;
	namespace FrontEnd
	{
		class ALLIExistingUserP :
			public ALLIUserP
		{
		public:
			ALLIVAULTCOREP_API ALLIExistingUserP();
			ALLIExistingUserP(const ALLIVaultCore::FrontEnd::ALLIExistingUserP &src);
			ALLIVAULTCOREP_API ~ALLIExistingUserP();

			void openEncryptedRepository(const boost::filesystem::path &encryptedURL, bool hasInitialCommit);
			void monitorPlainFolder(const boost::filesystem::path &plainFolderURL);
			ALLIVAULTCOREP_API ALLIVaultCore::ALLIEXTSecPlainFolderP *getPlainFolder();

		private:
			ALLIVaultCore::ALLIEXTSecEncryptRepoP *encryptedRepo;
			ALLIVaultCore::ALLIEXTSecPlainRepoP *plainRepo;
			ALLIVaultCore::ALLIEXTSecPlainFolderP *plainFolder;
		};
	}
}

