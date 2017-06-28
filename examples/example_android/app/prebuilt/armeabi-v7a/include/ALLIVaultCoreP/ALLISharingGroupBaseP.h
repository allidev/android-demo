#pragma once
#include "alli_hash.h"
#include "alli_event.h"
#include <unordered_map>
#include <unordered_set>
namespace ALLIVaultCore
{
	class ALLIEXTRepoP;
	class ALLIEXTSharingPlainRepoP;
	class ALLIEXTSharingEncryptRepoP;
	class ALLIEXTSharingPlainFolderP;
	class ALLIEXTSecPlainFolderP;
	namespace FrontEnd
	{
		class ALLIExistingUserP;
	}
	namespace Helpers
	{
		class ALLIStatusP;
		class ALLIGroupP;
		const int SHARING_PLAIN_REPO_POS = 0;
		const int SHARING_ENCRYPT_REPO_POS = 1;
		const int SHARING_PLAIN_FOLDER_POS = 2;
		class ALLISharingGroupBaseP
		{
		public:
			ALLISharingGroupBaseP(ALLIVaultCore::FrontEnd::ALLIExistingUserP &eu);
			~ALLISharingGroupBaseP();

			void setSharingGroupList(std::vector<std::string> &sgl);
			void setDictGroupMembers(std::unordered_map<std::string, std::unordered_set<std::string>> &dgm);
			void setSharingCurGroup(running_sharing_group_t &src);
			void copyFilesFromServerToSharingPlainFolder(void *obj);

		protected:
			/*
			* a collection of the names of groups created by the user
			*/
			std::vector<std::string> *sharingGroupList;
			ALLIVaultCore::FrontEnd::ALLIExistingUserP *existUser;
			ALLIVaultCore::ALLIEXTSecPlainFolderP *plainFolder;
			std::string username;
			ALLIVaultCore::ALLIEXTSharingPlainRepoP *sharingPlainRepo;
			ALLIVaultCore::ALLIEXTSharingEncryptRepoP *sharingEncryptRepo;
			ALLIVaultCore::ALLIEXTSharingPlainFolderP *sharingPlainFolder;
			// represent the instance of a currently running sharing group
			running_sharing_group_t *sharingCurGroup;
			std::unordered_map<std::string, std::unordered_set<std::string> > &dictGroupMembers;
			/*
			* a collection of groups of which the user is a member
			*/
			std::vector<ALLIVaultCore::Helpers::ALLIGroupP> *sharingALLIGroupList;

			bool addUserToFriendListDB(const std::string &uname, const std::string &fname);
			bool cloneFromRemoteSharingEncryptedRepo(const boost::filesystem::path &encryptedURL, const std::string &hostUserName, const std::string &groupName, ALLIVaultCore::Helpers::ALLIStatusP &alli_status);
			void addGroupName2ProgressFile(const std::string &groupName);
			void moveSharingPlainRepository(const boost::filesystem::path &plainURL);
			void moveSharingEncryptedRepository(const boost::filesystem::path &encryptedURL);
			boost::filesystem::path extractSharingEncryptedWorkDir();
			boost::filesystem::path extractSharingClientWorkDir();
			void populateGroupMemberList(ALLIVaultCore::Helpers::ALLIGroupP &aGroup, const std::string &hostUserName, const std::string &groupName);
			void copySharingEncryptedRepoToPlainRepo(const boost::filesystem::path &plainURL, ALLIVaultCore::Helpers::ALLIStatusP &alli_status);
			void monitorSharingPlainRepository(const boost::filesystem::path &sharingPlainRepoURL);
			void copyFilesFromServerToSharingPlainFolderImpl_1(void *obj);
			void copyFilesFromServerToSharingPlainFolderImpl_2(const std::string &hostUserName, const std::string &groupName);
			void copyFilesFromServerToSharingPlainFolderEx(const boost::filesystem::path &sharingPlainFolderURL);
			void monitorSharingEncryptedRepository(const boost::filesystem::path &sharingEncryptedURL, bool hasInitialCommit);
			void loadMemberList(const std::string &hostUserName, const std::string &groupName);
			boost::signals2::connection attachToEventHandlerForRepoUpdated(ALLIVaultCore::ALLIEXTRepoP *src);
			boost::signals2::connection attachToEventHandlerForLatestUpdate(ALLIVaultCore::ALLIEXTRepoP *src);
			void initializeDBForSharingFolder(const std::string &hostUserName, const std::string &groupName);

		private:
			virtual void moveSharingPlainRepositoryImpl(const boost::filesystem::path &plainURL);
			virtual void moveSharingEncryptedRepositoryImpl(const boost::filesystem::path &encryptedURL);
			virtual boost::filesystem::path extractSharingClientWorkDirImpl();
			virtual boost::filesystem::path extractSharingEncryptedWorkDirImpl();
			virtual void copyFilesFromServerToSharingPlainFolderImpl(void *obj);
			bool cloneFromRemoteEncryptedRepo(const boost::filesystem::path &encryptedURL);
			virtual bool cloneFromRemoteEncryptedRepoImpl(const boost::filesystem::path &encryptedURL);
			virtual void copySharingEncryptedRepoToPlainRepoImpl(const boost::filesystem::path &plainURL, ALLIVaultCore::Helpers::ALLIStatusP &alli_status);
			virtual void copyFilesFromServerToSharingPlainFolderExImpl(const boost::filesystem::path &sharingPlainFolderURL);
			void updateTotalBytesUsedForSharingPlainFolder(const std::string &hostUserName, const std::string &groupName);
		};
	}
}

