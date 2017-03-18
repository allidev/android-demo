#pragma once
#include "ALLIEXTRepoP.h"

namespace ALLIVaultCore
{ 
	class ALLIEXTSecPlainRepoP;
	class ALLIEXTSecEncryptRepoP :
		public ALLIVaultCore::ALLIEXTRepoP
	{
	public:
		ALLIEXTSecEncryptRepoP();
		ALLIEXTSecEncryptRepoP(const ALLIEXTSecEncryptRepoP &src);
		virtual ~ALLIEXTSecEncryptRepoP();

		void openEncryptedRepository(const boost::filesystem::path &encryptedURL);
		void initializeDBForSyncFolder();
		void linkSecPlainRepo(ALLIVaultCore::ALLIEXTSecPlainRepoP *src);

	private:
		friend class ALLIEXTSecPlainRepoP;
		ALLIVaultCore::ALLIEXTSecPlainRepoP *secPlainRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *encryptedRepoP;
		// init here and paired with secPlainRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_encrypt_plain_repo;
		// init here and used alone and unpaired
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_encrypt_repo;
		bool isFinishUploading;
		std::map<std::string, std::string> filesBridge;

		void updateTotalBytesUsedImpl() override;
		void openEncryptedRepositoryEx(const boost::filesystem::path &encryptedURL);
		bool trackFolderImpl() override;
		bool trackEncryptFolderImpl() override;
		bool saveBridgeDictionaryImpl(int *fd) override;
		void insertFilesBridge(const std::string &key, const std::string &val);
		ALLIVaultCore::Helpers::alli_mutex *getMutexEncryptPlainRepo() const;
	};
}

