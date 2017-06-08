#pragma once
#include "ALLIUserP.h"
#include "alli_hash.h"
#include <unordered_set>
#include <unordered_map>
#include <array>

class ALLINewUserPTest;

namespace ALLIVaultCore
{
	class ALLIEXTSecEncryptRepoP;
	class ALLIEXTSecPlainRepoP;
	class ALLIEXTSecPlainFolderP;
	class ALLIEXTSecMBEncryptRepoP;
	class ALLIEXTSecMBPlainRepoP;
	class ALLIEXTSecMBPlainFolderP;
	class ALLIEXTSharingPlainRepoP;
	class ALLIEXTRepoP;
	class ALLIEXTFolderP;
	class ALLISSClientRepoP;
	class ALLISSEncryptedRepoP;
	class ALLISSPlainRepoP;
	class ALLISSClientFolderP;
	class ALLISSPlainFolderP;
	class ALLIGroupInvitesP;
	namespace Helpers
	{
		class ALLIGroupP;
		class alli_semaphore;
		class ALLISharingGroupSyncNMP;
		class ALLISharingGroupToP;
		class ALLISharingGroupBaseP;
		class ALLIStatusP;
	}
	namespace FrontEnd
	{
		void group_invites_timer_wrapper(void *payload);
		class ALLIExistingUserP :
			public ALLIUserP
		{
		public:
			typedef ALLIVaultCore::FrontEnd::app_status_update_event::slot_type AppStatusUpdatedSlotType;
			typedef ALLIVaultCore::latest_update_event::slot_type RepoLatestUpdateSlotType;
			typedef ALLIVaultCore::group_invites_downloaded_event::slot_type GroupInvitesDownloadedSlotType;

			ALLIVAULTCOREP_API ALLIExistingUserP();
			ALLIExistingUserP(const ALLIVaultCore::FrontEnd::ALLIExistingUserP &src);
			ALLIExistingUserP &operator=(ALLIVaultCore::FrontEnd::ALLIExistingUserP const &src) = delete;
			ALLIVAULTCOREP_API ~ALLIExistingUserP();

			ALLIVAULTCOREP_API void openEncryptedRepository(const boost::filesystem::path &encryptedURL, bool hasInitialCommit);
			ALLIVAULTCOREP_API void openMBEncryptedRepository(const boost::filesystem::path &mbEncryptedURL, bool hasInitialCommit);
			ALLIVAULTCOREP_API void monitorPlainFolder(const boost::filesystem::path &plainFolderURL);
			ALLIVAULTCOREP_API void monitorMBPlainFolder(const boost::filesystem::path &plainFolderURL);
			ALLIVAULTCOREP_API ALLIVaultCore::ALLIEXTSecPlainFolderP *getPlainFolder();
			ALLIVAULTCOREP_API ALLIVaultCore::ALLIEXTSecMBPlainFolderP *getMBPlainFolder();
			ALLIVAULTCOREP_API void checkSharingGroupsSync();
			ALLIVAULTCOREP_API void openPlainRepository(const boost::filesystem::path &plainURL);
			ALLIVAULTCOREP_API void openMBPlainRepository(const boost::filesystem::path &mbPlainURL);
			ALLIVAULTCOREP_API void initializeDBForSyncFolder();
			ALLIVAULTCOREP_API void updateTotalBytesUsedForSecPlainFolder();
			ALLIVAULTCOREP_API void updateTotalBytesUsedForSecMBPlainFolder();
			std::unordered_map<std::string, std::unordered_set<std::string> > &getDictGroupMembers();
			ALLIVAULTCOREP_API std::string getDictGroupMembersJson() const;
			ALLIVAULTCOREP_API bool groupNameExists(const std::string &gname) const;
			ALLIVAULTCOREP_API std::vector<ALLIVaultCore::Helpers::ALLIGroupP> getSharingALLIGroupList() const;
			ALLIVAULTCOREP_API std::string getSharingALLIGroupListJson() const;
			ALLIVAULTCOREP_API std::unordered_set<running_sharing_group_t> getSharingGroups() const;
			ALLIVAULTCOREP_API running_sharing_group_t getRunningSharingGroup(const std::string &huname, const std::string &gname) const;
			ALLIVAULTCOREP_API unsigned long long getTotalBytesUsed() const;
			ALLIVAULTCOREP_API bool downloadOneFileForSyncFolder(const std::string &localPath, std::string &dest);
			ALLIVAULTCOREP_API bool downloadOneFileForMailbox(const std::string &localPath, std::string &dest);
			ALLIVAULTCOREP_API bool downloadOneFileForSharingGroup(const std::string &hostUserName, const std::string groupName, const std::string &localPath, std::string &dest);
            void createRootGitIgnoreFileForPlainRepo();
			void createRootGitIgnoreFileForMBPlainRepo();
			void createSharingGroupDBForPlainRepo();
			void passUserName(const std::string &userName);
			ALLIVAULTCOREP_API bool deleteFileForSyncFolder(const std::string &filePath, bool isDirectory = false);
			bool deleteFileForMailbox(const std::string &filePath, bool isDirectory = false);
			ALLIVAULTCOREP_API bool deleteFileForSharingGroup(const std::string &hostUserName, const std::string &groupName, const std::string &filePath, bool isDirectory = false);
			ALLIVAULTCOREP_API bool renameFileForSyncFolder(const std::string &old_path, const std::string &new_path, bool isDirectory = false);
			ALLIVAULTCOREP_API bool renameFileForSharingGroup(const std::string &hostUserName, const std::string &groupName, const std::string &old_path, const std::string &new_path, bool isDirectory = false);
			boost::signals2::connection connectAppStatusUpdated(const AppStatusUpdatedSlotType &slot);
			ALLIVAULTCOREP_API boost::signals2::connection connectRepoLatestUpdate(RepoLatestUpdateSlotType const &slot);
			ALLIVAULTCOREP_API std::string SyncFolderGetRootURL();
			ALLIVAULTCOREP_API std::string SharingGroupGetRootURL(const std::string &huname, const std::string &gname);
			ALLIVAULTCOREP_API void processSharingToWrapper(const std::string &groupName, const std::string &hostUserName, const std::string &guestUserName, const std::string &guestFullName);
			void processSharingFromWrapper(const std::string &groupName, const std::string &hostUserName, const std::string &guestUserName, const std::string &hostFullName);
			void transitionToExistUser();
			ALLIVAULTCOREP_API boost::signals2::connection connectGroupInvitesDownloaded(GroupInvitesDownloadedSlotType const &slot);
			ALLIVAULTCOREP_API void MBSendFiles(const std::vector<std::string> &fList, const std::unordered_set<std::string> &recList);
			ALLIVAULTCOREP_API bool addUserToFriendListDB(const std::string &uname, const std::string &fname);
			std::vector<std::string> getFriendList();
			ALLIVAULTCOREP_API std::string getFriendListJson();

		private:
			friend class ::ALLINewUserPTest;
			friend class ALLIVaultCore::Helpers::ALLISharingGroupToP;
			friend class ALLIVaultCore::Helpers::ALLISharingGroupBaseP;
			friend void group_invites_timer_wrapper(void *payload);
			int shSyncCounter;
			int shSyncTotal;
			typedef std::vector<void *> current_group_t;
			//typedef std::array<void *, 3> running_sharing_group_t;
			//typedef std::tuple<int, std::string, std::string> group_t;
			// represent the instance of a currently running sharing group
			running_sharing_group_t sharingCurGroup;
			// represent the collection of the currently running sharing group instances
			std::unordered_set<running_sharing_group_t> sharingGroups;
			/*
			* a collection of the names of groups created by the user
			*/
			std::vector<std::string> sharingGroupList;
			/*
			* a collection of groups of which the user is a member
			*/
			std::vector<ALLIVaultCore::Helpers::ALLIGroupP> sharingALLIGroupList;
			/*
			* the list of group members corresponding to a certain group
			*/
			std::vector<std::string> sgMemberList;
			std::unordered_map<std::string, std::unordered_set<std::string> > dictGroupMembers;
			ALLIVaultCore::ALLIEXTSecEncryptRepoP *encryptedRepo;
			ALLIVaultCore::ALLIEXTSecPlainRepoP *plainRepo;
			ALLIVaultCore::ALLIEXTSecPlainFolderP *plainFolder;
			ALLIVaultCore::ALLIEXTSecMBEncryptRepoP *mbEncryptedRepo;
			ALLIVaultCore::ALLIEXTSecMBPlainRepoP *mbPlainRepo;
			ALLIVaultCore::ALLIEXTSecMBPlainFolderP *mbPlainFolder;
			ALLIVaultCore::ALLISSClientRepoP *ssClientRepoP;
			ALLIVaultCore::ALLISSEncryptedRepoP *ssEncryptedRepoP;
			ALLIVaultCore::ALLISSPlainRepoP *ssPlainRepoP;
			ALLIVaultCore::ALLISSClientFolderP *ssClientFolderP;
			ALLIVaultCore::ALLISSPlainFolderP *ssPlainFolderP;
			// this semaphore is used to sync for new machine and sharing groups
			// when the user is a guest user.
			ALLIVaultCore::Helpers::alli_semaphore *sharingCurSemap;
			bool resetNewMachineState;
			ALLIVaultCore::ALLIEXTSharingPlainRepoP *sharingPlainRepo;
			std::unordered_map<std::string, unsigned long long> totalBytesUsedSet;
			unsigned long long totalBytesUsed;
			boost::signals2::connection encrypt_conn, enc_latest_conn, sync_folder_status;
			ALLIVaultCore::FrontEnd::app_status_update_event appStatusUpdated;
			ALLIVaultCore::latest_update_event repoLatestUpdate;
			ALLIVaultCore::ALLIGroupInvitesP *groupInvites;
			void *groupInvites_timer;
			ALLIVaultCore::group_invites_downloaded_event groupInvitesDownloaded;

			std::unordered_set<group_t> checkSharingGroups();
			bool createSharingGroupProgressFile();
			bool groupInProgressFile(const std::string &groupName);
			bool deleteProgressFile();
			void releaseSharingSyncResources();
			void addNewGroupToSharingGroupDBSync(const std::string &groupName, const std::string &hostUserName);
			void batchActionsForExistingSharing(const std::string &hostUserName, const std::string &groupName, const std::string &username);
			void monitorExistingSharingPlainRepo(const std::string &hostUserName, const std::string &groupName, const boost::filesystem::path &sharingPlainURL);
			void monitorExistingSharingEncryptedRepo(const std::string &hostUserName, const std::string &groupName, const boost::filesystem::path &sharingEncryptURL);
			void monitorExistingSharingPlainFolder(const boost::filesystem::path &sharingPlainFolder);
			void updateTotalBytesUsedForSharingPlainFolder(const std::string &hostUserName, const std::string &groupName);
			void loadMemberListSync(const std::string &hostUserName, const std::string &groupName);
			void populateGroupMemberList(const ALLIVaultCore::Helpers::ALLIGroupP &aGroup, const std::string &hostUserName, const std::string &groupName);
			void initializeDBForSharingFolder(const std::string &hostUserName, const std::string &groupName);
			void verifySharingFolder(const std::string &hostuname, const std::string &gname);
			void assignNotifyIcon();
			void addSharingFolderToFavorites();
			void attachToEventHandlerForMachNewStatusUpdated(ALLIVaultCore::Helpers::ALLISharingGroupSyncNMP *src);
			boost::signals2::connection attachToEventHandlerForRepoUpdated(ALLIVaultCore::ALLIEXTRepoP *src);
			boost::signals2::connection attachToEventHandlerForLatestUpdate(ALLIVaultCore::ALLIEXTRepoP *src);
			boost::signals2::connection attachToEventHandlerForAppStatusUpdated(ALLIVaultCore::ALLIEXTFolderP *src);
			boost::signals2::connection attachToEventHandlerForGroupInvitesReceived();
			void secEncryptRepoUpdated(void *sender, ALLIVaultCore::repo_event_args &e);
			void sharingEncryptRepoUpdated(void *sender, ALLIVaultCore::repo_event_args &e);
			void EncryptRepoUpdatedEx(void *sender, ALLIVaultCore::repo_event_args &e);
			ALLIVAULTCOREP_API boost::filesystem::path getPlainFolderRootFolder() const;
			void processAppStatusUpdates(void *sender, ALLIVaultCore::FrontEnd::exist_user_event_args &e);
			void OnAppStatusUpdated(ALLIVaultCore::FrontEnd::exist_user_event_args &e);
			void processLatestUpdate(void *sender, ALLIVaultCore::latest_update_event_args &e);
			void OnRepoLatestUpdate(ALLIVaultCore::latest_update_event_args &e);
			void releaseResourcesForSharingGroups();
			std::string addNewGroupToSharingGroupDB(const std::string &groupName, const std::string &hostUserName, bool &hasGroup);
			std::string addNewGroupToSharingGroupDB(const std::string &groupName, const std::string &hostUserName, ALLIVaultCore::Helpers::ALLIStatusP &alli_status);
			bool deleteGroupFromSharingGroupDB(const std::string &hostUserName, const std::string &groupName);
			void setupGroupInvitesSentinel(const std::string &guestUserName);
			void processGroupInvitesReceived(void *sender, ALLIVaultCore::Helpers::alli_event_args &e);
			bool isInviteAlreadyACurrentGroup(const ALLIVaultCore::Helpers::ALLIGroupP &src);
			void OnGroupInvitesDownloaded(ALLIVaultCore::group_event_args &e);
			void dlMailroomContactPublicKey(const std::string &contactUserName);
			ALLIVaultCore::ALLIEXTSharingPlainFolderP *getSharingPlainFolder(const std::string &huname, const std::string &gname);
		};
	}
}

