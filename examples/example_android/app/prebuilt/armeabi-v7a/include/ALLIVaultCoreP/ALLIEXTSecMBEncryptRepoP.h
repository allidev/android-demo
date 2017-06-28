#pragma once
#include "ALLIEXTSecEncryptRepoP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecMBPlainRepoP;
	class ALLIEXTSecMBEncryptRepoP :
		public ALLIEXTSecEncryptRepoP
	{
	public:
		ALLIEXTSecMBEncryptRepoP();
		~ALLIEXTSecMBEncryptRepoP();

	private:
		friend class ALLIEXTSecMBPlainRepoP;
		// init here and paired with secPlainRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_encrypt_plain_repo;
		// not init here
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_plain_repo;
		// init here and used alone and unpaired
		ALLIVaultCore::Helpers::alli_mutex *mutex_mb_local_encrypt_repo;

		bool trackFolderImpl(const std::string &fullPath) override;
		bool trackEncryptFolderImpl(const std::string &fullPath) override;
		void linkSecPlainRepoImpl(ALLIVaultCore::ALLIEXTSecPlainRepoP *src) override;
		void trackRemoteRepoImpl() override;
		ALLIVaultCore::Helpers::alli_mutex *getMutexEncryptPlainRepoImpl() const override;
		void fire_latest_update_event_impl(ALLIVaultCore::ALLIActionDirectionP dir) override;
		void buildIndexDBHistoryImpl() override;
	};
}

