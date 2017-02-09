#pragma once
#include "ALLIEXTSecPlainFolderP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecMBPlainRepoP;
	class ALLIEXTSecMBPlainFolderP :
		public ALLIEXTSecPlainFolderP
	{
	public:
		ALLIEXTSecMBPlainFolderP(const ALLIVaultCore::ALLIEXTSecMBPlainRepoP &plainRepo);
		~ALLIEXTSecMBPlainFolderP();
	};
}

