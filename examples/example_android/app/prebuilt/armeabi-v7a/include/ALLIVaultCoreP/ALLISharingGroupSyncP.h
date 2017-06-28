#pragma once
#include "ALLISharingGroupBaseP.h"
#include "alli_hash.h"
namespace ALLIVaultCore
{
	class ALLIEXTSecEncryptRepoP;
	class ALLIEXTSecPlainRepoP;
	class ALLISSClientRepoP;
	class ALLISSEncryptedRepoP;
	class ALLISSPlainRepoP;
	class ALLISSClientFolderP;
	class ALLISSPlainFolderP;
	namespace Helpers
	{
		class auto_reset_event;
		class ALLISharingGroupSyncP :
			public ALLISharingGroupBaseP
		{
		public:
			ALLISharingGroupSyncP(ALLIVaultCore::FrontEnd::ALLIExistingUserP &eu);
			ALLISharingGroupSyncP(ALLIVaultCore::ALLIEXTSecPlainRepoP *pl_repo, ALLIVaultCore::FrontEnd::ALLIExistingUserP &eu);
			~ALLISharingGroupSyncP();

			void batchActionsForSharingSync(const std::string &hostUserName, const std::string &groupName);

		protected:
			ALLIVaultCore::ALLISSClientRepoP *ssClientRepoP;
			ALLIVaultCore::ALLISSEncryptedRepoP *ssEncryptedRepoP;
			ALLIVaultCore::ALLISSPlainRepoP *ssPlainRepoP;
			ALLIVaultCore::ALLISSClientFolderP *ssClientFolderP;
			ALLIVaultCore::ALLISSPlainFolderP *ssPlainFolderP;
			std::vector<ALLIVaultCore::Helpers::ALLIGroupP> *sharingALLIGroupList;

			void loadMemberListSync(const std::string &hostUserName, const std::string &groupName);
			bool hasSharingSyncClientFolder();
			void monitorSharingSyncReposAndFolder(const boost::filesystem::path &sharingPlainFolder, const std::string &hostUserName);
			virtual void monitorSharingSyncEncryptedRepoImpl(const std::string &hostUserName);
			void monitorSharingSyncPlainFolderAtURLEx(const boost::filesystem::path &sharingPlainFolder, const std::string &hostUserName);
			virtual void monitorSharingSyncPlainRepoImpl(const std::string &hostUserName);

		private:
			friend class ALLIVaultCore::ALLIEXTSecEncryptRepoP;
			ALLIVaultCore::Helpers::auto_reset_event *shSyncPlainFolder_are;
			ALLIVaultCore::Helpers::auto_reset_event *syncGroup_are;
			ALLIVaultCore::ALLIEXTSecPlainRepoP *plainRepo;

			void moveSharingPlainRepositoryImpl(const boost::filesystem::path &plainURL) override;
			void moveSharingEncryptedRepositoryImpl(const boost::filesystem::path &encryptedURL) override;
			boost::filesystem::path extractSharingClientWorkDirImpl() override;
			boost::filesystem::path extractSharingEncryptedWorkDirImpl() override;
			bool cloneFromRemoteEncryptedRepoImpl(const boost::filesystem::path &encryptedURL) override;
			void copySharingEncryptedRepoToPlainRepoImpl(const boost::filesystem::path &plainURL, ALLIVaultCore::Helpers::ALLIStatusP &alli_status) override;
			void monitorSharingSyncPlainRepo(const std::string &hostUserName);
			void monitorSharingSyncEncryptedRepo(const std::string &hostUserName);
			void monitorSharingSyncPlainFolderAtURL(const boost::filesystem::path &sharingPlainFolder, const std::string &hostUserName);
			virtual void monitorSharingSyncPlainFolderAtURLImpl(const boost::filesystem::path &sharingPlainFolder, const std::string &hostUserName);
			void setSharingHostUserName(const std::string &guestUserName, const std::string &groupName);
			void setSharingGuestUserName(const std::string &hostUserName, const std::string &groupName);
			void batchSetupSharingRepo(const std::string &hostUserName, const std::string &guestUserName, const std::string &groupName, const std::string &sharingType);
			void copyFilesFromServerToSharingPlainFolderImpl(void *obj) override;
			void copyFilesFromServerToSharingPlainFolderExImpl(const boost::filesystem::path &sharingPlainFolderURL) override;
		};
	}
}

