#pragma once
#include "ALLIEXTSecPlainFolderP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecMBPlainRepoP;
	class ALLIEXTSecMBPlainFolderP :
		public ALLIEXTSecPlainFolderP
	{
	public:
		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainRepoP &plainRepo);
		~ALLIEXTSecMBPlainFolderP();

	private:
		bool downloadOneFileJsonImpl(const std::string &localPath, std::string &dest) override;
	};
}

