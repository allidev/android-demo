#pragma once
#include "ALLIEXTSharingRepoP.h"
namespace ALLIVaultCore
{
	namespace Helpers
	{
		class auto_reset_event;
	}
	class ALLISharingCacheP;
	class ALLIEXTSharingPlainFolderP;
	class ALLIEXTSharingEncryptRepoP;
	class ALLIEXTSharingPlainRepoP :
		public ALLIEXTSharingRepoP
	{
	public:
		ALLIEXTSharingPlainRepoP();
		ALLIEXTSharingPlainRepoP(const boost::filesystem::path &sharingPlainRepoURL);
		~ALLIEXTSharingPlainRepoP();

		void monitorSharingPlainRepository(const boost::filesystem::path &shPlainURL);
		void connectEncryptRepoP(ALLIVaultCore::ALLIEXTSharingEncryptRepoP *src);
		bool deleteGuestMember(const std::string &gUserName);
		bool deleteAllGuestMembers();

	private:
		friend class ALLIEXTSharingPlainFolderP;
		friend class ALLIEXTSharingEncryptRepoP;
		friend class ALLISharingCacheP;
		ALLIVaultCore::ALLIEXTSharingEncryptRepoP *shEncryptRepo;
		ALLIVaultCore::ALLIEXTSharingPlainFolderP *shPlainFolder;
		ALLIVaultCore::Helpers::auto_reset_event *sharingPlainCondition;
		// init'ed here and paired with ALLIEXTSharingPlainFolderP object
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_plain_repo;
		// not init here and paired from secEncryptRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_encrypt_plain_repo;
		// not init here and paired from secPlainFolder
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_sharing_plain_folder;
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingPlainRepoP;

		bool trackFolderImpl(const std::string &fullPath) override;
		bool trackPlainFolderImpl() override;
		bool encryptFileToSecureEncryptFolderImpl(const std::string &fileName) override;
		bool moveAESKeyFile(const std::string &src, const std::string &dest);
		bool insertFilePairImpl(const boost::filesystem::path &srcFile, const boost::filesystem::path &destFile) override;
		bool encryptAESKeyImpl(const std::string &keyUser, const boost::filesystem::path &filePath) override;
		bool saveBridgeDictionaryImpl(int *fd) override;
		void terminateThread();
		void populateSharingCache(ALLIVaultCore::ALLISharingCacheP *aCache);
		bool createCacheForRepoHeadImpl() override;
		void OnGuestListUpdated(ALLIVaultCore::Helpers::alli_event_args &e);
		bool fileExistsInFilesBridgeImpl(const std::string &fileName) override;
		std::string findKeyShaForValueShaImpl(const std::string &valueSha) override;
	};
}

