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
		ALLIVaultCore::ALLIEXTSecMBPlainRepoP *mbPlainRepo;

		bool downloadOneFileJsonImpl(const std::string &localPath, std::string &dest) override;
		void monitorPlainFolderImpl(const boost::filesystem::path &plainURL) override;
        bool trackFolderImpl() override;
	};
}

