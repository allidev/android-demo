#pragma once
#include "ALLIFolderP.h"

namespace ALLIVaultCore
{
	class ALLINMFolderP :
		public ALLIFolderP
	{
	public:
		ALLINMFolderP();
		ALLINMFolderP(const ALLIVaultCore::ALLINMFolderP &src);
		~ALLINMFolderP();

	protected:
		void setRegistryKey(const std::string &rkey, int value);
	};
}

