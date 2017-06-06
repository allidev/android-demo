#pragma once
#include "ALLIEXTSecPlainRepoP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecMBEncryptRepoP;
	class ALLIEXTSecMBPlainFolderP;
	class ALLIEXTSecMBPlainRepoP :
		public ALLIEXTSecPlainRepoP
	{
	public:
		ALLIEXTSecMBPlainRepoP();
		~ALLIEXTSecMBPlainRepoP();

	private:
		friend class ALLIEXTSecMBEncryptRepoP;
		friend class ALLIEXTSecMBPlainFolderP;
		// not init here and paired from secEncryptRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_encrypt_plain_repo;
		// not init here
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_local_plain_folder;
		// init here and used for remote repo monitoring
		// paired with secEncryptRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_plain_repo;

		bool trackFolderImpl(const std::string &fullPath) override;
		void setEncryptRepoImpl(ALLIVaultCore::ALLIEXTSecEncryptRepoP *src) override;
	};
}

