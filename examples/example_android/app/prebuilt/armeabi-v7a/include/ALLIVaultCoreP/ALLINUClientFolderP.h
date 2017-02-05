#pragma once
#include "ALLINUFolderP.h"

namespace ALLIVaultCore
{
	class ALLINUClientFolderP :
		public ALLINUFolderP
	{
	public:
		ALLIVAULTCOREP_API ALLINUClientFolderP();
		ALLINUClientFolderP(const ALLIVaultCore::ALLINUClientFolderP &src);
		ALLIVAULTCOREP_API ~ALLINUClientFolderP();

		ALLIVAULTCOREP_API bool createRemoteFolder(const std::string &userName);
		ALLIVAULTCOREP_API bool createClientFolder(const boost::filesystem::path &clientFolderURL);
		ALLIVAULTCOREP_API boost::filesystem::path *getClientFolderURL();

	private:
		ALLIVaultCore::Engine::SimpleFolder *clientFolder;
		boost::filesystem::path *clientFolderURL;
	};
}

