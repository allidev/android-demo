#pragma once
#include "ALLISharingGroupBaseP.h"
#include "alli_hash.h"
namespace ALLIVaultCore
{
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
			~ALLISharingGroupSyncP();

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
			ALLIVaultCore::Helpers::auto_reset_event *shSyncPlainFolder_are;

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
		};
	}
}

