#pragma once
#include "ALLIEXTSharingRepoP.h"
namespace ALLIVaultCore
{
	namespace Engine
	{
		class SimpleRepositoryP;
	}
	class ALLIEXTSharingPlainRepoP;
	class ALLIEXTSharingEncryptRepoP :
		public ALLIEXTSharingRepoP
	{
	public:
		ALLIEXTSharingEncryptRepoP();
		~ALLIEXTSharingEncryptRepoP();

		void connectPlainRepoP(ALLIVaultCore::ALLIEXTSharingPlainRepoP *src);
		void initSimpleRepositoryP(const ALLIVaultCore::Engine::SimpleRepositoryP &src);
		void linkEncryptPlainMutex();
		void monitorSharingEncryptedRepository(const boost::filesystem::path &sharingEncryptedURL);

	private:
		friend class ALLIVaultCore::ALLIEXTSharingPlainRepoP;
		ALLIVaultCore::ALLIEXTSharingPlainRepoP *shPlainRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingEncryptedRepoP;
		// init here and paired with secPlainRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_encrypt_plain_repo;
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_sharing_encrypt_repo;

		void trackRemoteRepoImpl() override;
		bool saveBridgeDictionaryImpl(int *fd) override;
		bool trackFolderImpl(const std::string &fullPath) override;
		bool trackEncryptFolderImpl(const std::string &fullPath) override;
		bool indexContainsMinimumFilesImpl(libgit2cpp::index *idx) override;
	};
}

