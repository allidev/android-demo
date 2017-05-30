#pragma once
#include "ALLISharingGroupBaseP.h"
namespace ALLIVaultCore
{
	class ALLISTClientRepoP;
	class ALLISTEncryptedRepoP;
	class ALLISTPlainRepoP;
	class ALLISTClientFolderP;
	class ALLISTPlainFolderP;
	class ALLIGroupManagementP;
	namespace Helpers
	{
		class ALLISharingGroupToP :
			public ALLISharingGroupBaseP
		{
		public:
			ALLISharingGroupToP(ALLIVaultCore::FrontEnd::ALLIExistingUserP *eu, bool hasGroup);
			~ALLISharingGroupToP();

			void processSharingTo(const std::string &groupName, const std::string &hostUserName, std::string &groupSHA1, const std::string &guestUserName, const std::string &guestFullName);

		private:
			bool groupExists;
			ALLIVaultCore::ALLIGroupManagementP *groupManagement;
			/*
			* the list of group members corresponding to a certain group
			*/
			std::vector<std::string> *sgMemberList;
			/*
			* a collection of groups of which the user is a member
			*/
			std::vector<ALLIVaultCore::Helpers::ALLIGroupP> *sharingALLIGroupList;
			// represent the collection of the currently running sharing group instances
			std::unordered_set<running_sharing_group_t> *sharingGroups;
#ifdef TO_BE_IMPLEMENTED
			System::Runtime::InteropServices::GCHandle gch_shg_mon, gch_shg_mon_enc, gch_sharing_key, gch_root_git;
#endif

			ALLIVaultCore::ALLISTClientRepoP *stClientRepo;
			ALLIVaultCore::ALLISTEncryptedRepoP *stEncryptedRepo;
			ALLIVaultCore::ALLISTPlainRepoP *stPlainRepo;
			ALLIVaultCore::ALLISTClientFolderP *stClientFolder;
			ALLIVaultCore::ALLISTPlainFolderP *stPlainFolder;

			void setSharingHostUserName(const std::string &guestUserName, const std::string &guestFullName, const std::string &groupName);
			bool createRemoteSharingEncryptedRepo(const std::string &groupName);
			bool createRemoteSharingEncryptedFolder(const std::string &groupName);
			void batchActionsForSharingTo(const std::string &guestUserName, const std::string &groupName);
			bool updateRemoteSharingEncryptedRepo(const std::string &groupName, const std::string &guestUserName);
			void batchActionsToUpdateForSharingTo(const std::string &groupName, const std::string &guestUserName);
			void addGroupMemberToServer(const std::string &hostUserName, const std::string &groupName, const std::string &guestUserName);
			bool createSharingPlainRepository(const boost::filesystem::path &sharingPlainURL);
			bool createSharingPlainWorkDir(const std::string &groupName, const std::string &guestUserName);
			bool createSharingEncryptedRepository(const boost::filesystem::path &sharingEncryptedURL);
			bool createSharingEncryptedWorkDir(const std::string &groupName);
			bool createSharingPlainFolderAtURL(const boost::filesystem::path &sharingPlainFolderURL, const std::string &groupName);
			void openExistingSharingPlainRepository(const boost::filesystem::path &sharingPlainURL);
			void expandAESKeysForNewGuestUser(const std::string &groupName, const std::string &guestUserName);
			void updateGuestListForSharingPlainRepo(const std::string &groupName);
			bool createSharingPlainWorkDir(const std::string &groupName);
			void monitorSharingPlainRepo(const std::string &guestUserName);
			bool createSharingEncryptedWorkDirEx(const std::string &groupName);
			void monitorSharingEncryptedRepo(const std::string &groupName);
			bool createSharingPlainFolderAtURLEx(const boost::filesystem::path &sharingPlainFolderURL, const std::string &groupName);
			void monitorSharingPlainFolderAtURL(const boost::filesystem::path &sharingPlainFolderURL);
			bool openExistingSharingPlainRepositoryEx(const boost::filesystem::path &sharingPlainURL);
			running_sharing_group_t extractMatchingRunningGroupObject(const std::string &hostUserName, const std::string &groupName);
			void updateSharingObjectsForExpandingAESKeys(const running_sharing_group_t &matchSharingGroup);
			void expandAESKeysForNewGuestUserEx(const std::string &groupName, const std::string &guestUserName);
			void updateSharingObjectForGuestList(const running_sharing_group_t &matchSharingGroup);
			void updateGuestListForSharingPlainRepo();
			void createSharingKeyFolderForSharingEncryptedRepo();
			void createRootGitIgnoreFileForSharingPlainRepo();
		};
	}
}

