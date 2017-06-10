#pragma once
#include "ALLIEXTSharingRepoP.h"
namespace ALLIVaultCore
{
	namespace Engine
	{
		class SimpleRepositoryP;
	}
	namespace Helpers
	{
		class auto_reset_event;
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
		void expandAESKeysForNewGuestUser(const std::string &groupName, const std::string &guestUserName);
		void createSharingKeyFolder();

	private:
		friend class ALLIVaultCore::ALLIEXTSharingPlainRepoP;
		ALLIVaultCore::ALLIEXTSharingPlainRepoP *shPlainRepo;
		ALLIVaultCore::Engine::SimpleRepositoryP *sharingEncryptedRepoP;
		// init here and paired with secPlainRepo
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_encrypt_plain_repo;
		// this is a weak pointer, do not call constructor and destructor in this class
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_plain_repo;
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_sharing_encrypt_repo;
		boost::filesystem::path *sharingKeyFolder;
		ALLIVaultCore::Helpers::auto_reset_event *encryp_folder_are;

		void trackRemoteRepoImpl() override;
		bool saveBridgeDictionaryImpl(int *fd) override;
		bool trackFolderImpl(const std::string &fullPath) override;
		bool trackEncryptFolderImpl(const std::string &fullPath) override;
		bool indexContainsMinimumFilesImpl(libgit2cpp::index *idx) override;
		void localRepoCallbackEx_fire_updateImpl(bool git_op) override;
		void createCacheForLastCommitImpl(const std::string &lastCommitSha1) override;
	};
}

