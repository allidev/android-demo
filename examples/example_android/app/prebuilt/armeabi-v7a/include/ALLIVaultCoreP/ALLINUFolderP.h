#pragma once
#include "ALLIFolderP.h"

namespace ALLIVaultCore
{
	class ALLINUFolderP :
		public ALLIFolderP
	{
	public:
		ALLINUFolderP();
		ALLINUFolderP(const ALLIVaultCore::ALLINUFolderP &src);
		~ALLINUFolderP();

	protected:
		bool createRemoteFolderEx(const std::string &userName, const std::string &folderName);
		bool createLocalFolderEx(const boost::filesystem::path &folderURL);

	private:
		boost::filesystem::path *folderURL;
	};
}

