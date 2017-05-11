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
		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainFolderP const &src) = delete;
		ALLIEXTSecMBPlainFolderP &operator=(ALLIVaultCore::ALLIEXTSecMBPlainFolderP const &src) = delete;
		ALLIEXTSecMBPlainFolderP(ALLIVaultCore::ALLIEXTSecMBPlainFolderP &&src) = delete;
		ALLIEXTSecMBPlainFolderP &operator=(ALLIVaultCore::ALLIEXTSecMBPlainFolderP &&src) = delete;
		~ALLIEXTSecMBPlainFolderP();

	private:
		ALLIVaultCore::ALLIEXTSecMBPlainRepoP *mbPlainRepo;

		bool downloadOneFileJsonImpl(const std::string &localPath, std::string &dest) override;
		void monitorPlainFolderImpl(const boost::filesystem::path &plainURL) override;
        bool trackFolderImpl(const std::string &fullPath) override;
	};
}

