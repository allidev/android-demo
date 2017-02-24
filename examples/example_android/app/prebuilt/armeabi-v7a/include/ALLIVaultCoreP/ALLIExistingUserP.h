#pragma once
#include "ALLIUserP.h"
#include "alli_hash.h"
#include <unordered_set>
#include <unordered_map>
#include <array>

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
	class ALLISSClientRepoP;
	class ALLISSEncryptedRepoP;
	class ALLISSPlainRepoP;
	class ALLISSClientFolderP;
	class ALLISSPlainFolderP;
	namespace Helpers
	{
		class ALLIGroupP;
		class alli_semaphore;
		class ALLISharingGroupSyncNMP;
	}
	namespace FrontEnd
	{
		class ALLIExistingUserP :
			public ALLIUserP
		{
		public:
			ALLIVAULTCOREP_API ALLIExistingUserP();
			ALLIExistingUserP(const ALLIVaultCore::FrontEnd::ALLIExistingUserP &src);
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
			ALLIVAULTCOREP_API std::vector<ALLIVaultCore::Helpers::ALLIGroupP> getSharingALLIGroupList() const;
			ALLIVAULTCOREP_API std::string getSharingALLIGroupListJson() const;
			ALLIVAULTCOREP_API std::unordered_set<running_sharing_group_t> getSharingGroups() const;
			ALLIVAULTCOREP_API unsigned long long getTotalBytesUsed() const;
			ALLIVAULTCOREP_API bool downloadOneFileForSyncFolder(const std::string &localPath);
			ALLIVAULTCOREP_API bool downloadOneFileForMailbox(const std::string &localPath);
			ALLIVAULTCOREP_API bool downloadOneFileForSharingGroup(const std::string &hostUserName, const std::string groupName, const std::string &localPath);

		private:
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
			boost::signals2::connection encrypt_conn;

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
			void secEncryptRepoUpdated(void *sender, ALLIVaultCore::repo_event_args &e);
			void EncryptRepoUpdatedEx(void *sender, ALLIVaultCore::repo_event_args &e);
		};
	}
}

