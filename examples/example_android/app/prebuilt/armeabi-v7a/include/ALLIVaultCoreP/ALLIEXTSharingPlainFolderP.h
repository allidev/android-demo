#pragma once
#include "ALLIEXTSharingFolderP.h"
namespace ALLIVaultCore
{
	class ALLIEXTSharingPlainRepoP;
	class ALLIEXTSharingPlainFolderP :
		public ALLIEXTSharingFolderP
	{
	public:
		ALLIEXTSharingPlainFolderP(ALLIVaultCore::ALLIEXTSharingPlainRepoP *pRepo);
		~ALLIEXTSharingPlainFolderP();

		void monitorSharingPlainFolderAtURL(const boost::filesystem::path &sharingPlainFolderURL);
		void expandAESKeysForNewGuestUser(const std::string &groupName, const std::string &guestUserName);

	private:
		ALLIVaultCore::ALLIEXTSharingPlainRepoP *sharingPlainRepo;
		ALLIVaultCore::Engine::SimpleFolder *sharingPlainFolder;
		/*
		* when adding a user to a group, changes to the group
		* need to wait for processing.
		*/
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_to_folder;
		ALLIVaultCore::Helpers::alli_mutex *mutex_local_sharing_plain_folder;
		// this is a weak pointer, do not call constructor and destructor in this class
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_plain_repo;
		ALLIVaultCore::Helpers::alli_mutex *mutex_sharing_encrypt_plain_folder;

		void load_index_db_ex() override;
		bool downloadOneFileJsonImpl(const std::string &localPath, std::string &dest) override;
		bool trackFolderImpl(const std::string &fullPath) override;
		bool trackFolderImpl(const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &src, const std::pair<std::string, ALLIVaultCore::Engine::ALLIFileStatusP> &dest, bool isDirectory) override;
		bool commitStagedFilesManual(const std::unordered_map<std::string, std::pair<ALLIVaultCore::Engine::ALLIFileStatusP, std::string>> &files, std::vector<std::string> &messages, std::string &src) override;
		void commitStagedFileManual_impl(const std::string &relativePath, const boost::filesystem::path &filePath, const std::string &orig, std::unordered_map<std::string, std::string> &filesToUpload);
		void uploadFilesImpl(const std::unordered_map<std::string, std::string> &filesToUpload) override;
	};
}

