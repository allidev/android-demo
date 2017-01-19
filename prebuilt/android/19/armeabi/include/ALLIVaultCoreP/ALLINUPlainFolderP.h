#pragma once
#include "ALLINUFolderP.h"

namespace ALLIVaultCore
{
	class ALLINUPlainFolderP :
		public ALLINUFolderP
	{
	public:
		ALLIVAULTCOREP_API ALLINUPlainFolderP();
		ALLINUPlainFolderP(const ALLIVaultCore::ALLINUPlainFolderP &src);
		ALLIVAULTCOREP_API ~ALLINUPlainFolderP();

		ALLIVAULTCOREP_API bool createRemoteEncryptedFolder(const std::string &userName);
		ALLIVAULTCOREP_API bool createPlainFolder(const boost::filesystem::path &plainURL);
		ALLIVAULTCOREP_API boost::filesystem::path *getPlainFolderURL();

	private:
		ALLIVaultCore::Engine::SimpleFolder *plainFolder;
		boost::filesystem::path *plainFolderURL;
	};
}

