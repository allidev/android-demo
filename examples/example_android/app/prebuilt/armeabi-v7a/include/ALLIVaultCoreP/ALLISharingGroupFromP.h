#pragma once
#include "ALLISharingGroupBaseP.h"

namespace ALLIVaultCore
{
	class ALLISFClientRepoP;
	class ALLISFEncryptedRepoP;
	class ALLISFPlainRepoP;
	class ALLISFClientFolderP;
	class ALLISFPlainFolderP;
	namespace Helpers
	{
		class ALLISharingGroupFromP :
			public ALLISharingGroupBaseP
		{
		public:
			ALLISharingGroupFromP(ALLIVaultCore::FrontEnd::ALLIExistingUserP *eu);
			~ALLISharingGroupFromP();

			void processSharingFrom(const std::string &groupName, const std::string &hostUserName, const std::string &guestUserName, const std::string &hostFullName);

		private:
			ALLIVaultCore::ALLISFClientRepoP *sfClientRepo;
			ALLIVaultCore::ALLISFEncryptedRepoP *sfEncryptedRepo;
			ALLIVaultCore::ALLISFPlainRepoP *sfPlainRepo;
			ALLIVaultCore::ALLISFClientFolderP *sfClientFolder;
			ALLIVaultCore::ALLISFPlainFolderP *sfPlainFolder;

			void setSharingGuestUserName(const std::string &hostUserName, const std::string &hostFullName, const std::string &groupName);
			void batchActionsForSharingFrom(const std::string &hostUserName, const std::string &groupName);
			void batchActions_client_repo(const std::string &hostUserName, const std::string &groupName, boost::filesystem::path &rootSharingGits);
			void batchActions_clone_encrypted_repo(const std::string &hostUserName, const std::string &groupName);
			void batchActions_move_plain_repo(const std::string &hostUserName, const std::string &groupName, const boost::filesystem::path &rootSharingGits);
			void batchActions_move_encrypted_repo(const std::string &hostUserName, const std::string &groupName, const boost::filesystem::path &rootSharingGits);
			void batchActions_plain_folder(const std::string &hostUserName, const std::string &groupName);
			void batchActions_updateDB(const std::string &hostUserName, const std::string &groupName);
			void safe_create_directory(const boost::filesystem::path &sharingURL);
			bool updateServerGroupDB(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			void moveSharingPlainRepositoryImpl(const boost::filesystem::path &plainURL) override;
			void monitorSharingFromPlainRepo(const std::string &hostUserName);
			void moveSharingEncryptedRepositoryImpl(const boost::filesystem::path &encryptedURL) override;
			void copyFilesFromServerToSharingPlainFolderImpl(void *obj) override;
			bool hasSharingFromClientFolder();
			void monitorSharingFromReposAndFolder(const boost::filesystem::path &sharingPlainFolder, const std::string &hostUserName);
			void monitorSharingFromEncryptedRepo(const std::string &hostUserName);
			void monitorSharingFromPlainFolderAtURL(const boost::filesystem::path &sharingPlainFolderURL);
			boost::filesystem::path extractSharingEncryptedWorkDirImpl() override;
			bool cloneFromRemoteEncryptedRepoImpl(const boost::filesystem::path &encryptedURL) override;
			void copySharingEncryptedRepoToPlainRepoImpl(const boost::filesystem::path &plainURL, ALLIVaultCore::Helpers::ALLIStatusP &alli_status) override;
			boost::filesystem::path extractSharingClientWorkDirImpl() override;
			void copyFilesFromServerToSharingPlainFolderExImpl(const boost::filesystem::path &sharingPlainFolderURL) override;
		};
	}
}

